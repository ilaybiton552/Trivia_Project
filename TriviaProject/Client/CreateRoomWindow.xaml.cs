using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

namespace Client
{
    /// <summary>
    /// Interaction logic for CreateRoomWindow.xaml
    /// </summary>
    public partial class CreateRoomWindow : Window
    {
        private CreateRoomRequest request;
        private Communicator communicator;
        private string username;
        private const int CreateRoomRequestCode = 109;
        private const int CreateRoomResponseCode = 207;
        private const int ErrorResponseCode = 200;

        public CreateRoomWindow(ref Communicator communicator, string username)
        {
            InitializeComponent();
            this.communicator = communicator;
            this.username = username;
            trivia.Text = username + ", " + trivia.Text;
            request = new CreateRoomRequest();
            this.DataContext = request;
        }

        /// <summary>
        /// Sends a create room request to the server
        /// </summary>
        private void SendClick(object sender, RoutedEventArgs e)
        {
            bool check = true;

            if (tbRoomName.Text.Length != 0 && tbRoomName.Text.Length <= 25)
            {
                tbRoomName.BorderBrush = Brushes.Green;
            }
            else
            {
                tbRoomName.BorderBrush = Brushes.Red;
                check = false;
            }
            if (int.TryParse(tbMaxUsers.Text, out _) && 2 <= int.Parse(tbMaxUsers.Text) && int.Parse(tbMaxUsers.Text) <= 10)
            {
                tbMaxUsers.BorderBrush = Brushes.Green;
            }
            else
            {
                tbMaxUsers.BorderBrush = Brushes.Red; 
                check = false;
            }
            if (int.TryParse(tbQuestionCount.Text, out _) && 2 <= int.Parse(tbQuestionCount.Text) && int.Parse(tbQuestionCount.Text) <= 10)
            {
                tbQuestionCount.BorderBrush = Brushes.Green;
            }
            else
            {
                tbQuestionCount.BorderBrush = Brushes.Red;
                check = false;
            }
            if (int.TryParse(tbAnswerTimeout.Text, out _) && 5 <= int.Parse(tbAnswerTimeout.Text) && int.Parse(tbAnswerTimeout.Text) <= 15)
            {
                tbAnswerTimeout.BorderBrush = Brushes.Green;
            }
            else
            {
                tbAnswerTimeout.BorderBrush = Brushes.Red;
                check = false;
            }

            if (check) // check if all of the needed information is correct
            {
                string json = JsonConvert.SerializeObject(request);
                PacketInfo packetToSend = new PacketInfo() { code = CreateRoomRequestCode, data = json };
                communicator.SendPacket(packetToSend);

                PacketInfo receivedPacket = this.communicator.GetMessageFromServer();
                CreateRoomResponse response = JsonConvert.DeserializeObject<CreateRoomResponse>(receivedPacket.data);
                if (receivedPacket.code == CreateRoomResponseCode)
                {
                    RoomData roomData = new RoomData() { admin = username, isActive = 1, players = username,
                        name = tbRoomName.Text, maxPlayers = int.Parse(tbMaxUsers.Text), id = response.roomId,
                        numOfQuestions = int.Parse(tbQuestionCount.Text), timePerQuestion = int.Parse(tbAnswerTimeout.Text)};
                    RoomWindow roomWindow = new RoomWindow(ref communicator, username, roomData);
                    roomWindow.WindowStartupLocation = WindowStartupLocation.Manual;
                    roomWindow.Left = this.Left;
                    roomWindow.Top = this.Top;
                    Close();
                    roomWindow.ShowDialog();
                }
                else
                {
                    MessageBox.Show(receivedPacket.data, "Error", MessageBoxButton.OK);
                    request = new CreateRoomRequest();
                    this.DataContext = request;
                }
            }


        }

        /// <summary>
        /// Clears the data of all the text boxes
        /// </summary>
        private void ClearClick(object sender, RoutedEventArgs e)
        {
            request = new CreateRoomRequest();
            this.DataContext = request;
            tbRoomName.BorderBrush = Brushes.Gray;
            tbMaxUsers.BorderBrush = Brushes.Gray;
            tbQuestionCount.BorderBrush = Brushes.Gray;
            tbAnswerTimeout.BorderBrush = Brushes.Gray;
        }

        /// <summary>
        /// Goes a window back (menu window)
        /// </summary>
        private void BackClick(object sender, RoutedEventArgs e)
        {
            MenuWindow menuWindow = new MenuWindow(ref communicator, username);
            menuWindow.WindowStartupLocation = WindowStartupLocation.Manual;
            menuWindow.Left = this.Left;
            menuWindow.Top = this.Top;
            Close();
            menuWindow.ShowDialog();
        }
    }
}
