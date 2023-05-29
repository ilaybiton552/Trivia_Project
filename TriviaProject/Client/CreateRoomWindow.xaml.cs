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
            WindowStartupLocation = System.Windows.WindowStartupLocation.CenterScreen;
            this.communicator = communicator;
            this.username = username;
            request = new CreateRoomRequest();
            this.DataContext = request;
        }

        /// <summary>
        /// Sends a create room request to the server
        /// </summary>
        private void SendClick(object sender, RoutedEventArgs e)
        {
            bool check = true;

            if (tbRoomName.Text.Length != 0)
            {
                tbRoomName.BorderBrush = Brushes.Green;
            }
            else
            {
                tbRoomName.BorderBrush = Brushes.Red;
                check = false;
            }
            if (int.TryParse(tbMaxUsers.Text, out _) && tbMaxUsers.Text.Length != 0)
            {
                tbMaxUsers.BorderBrush = Brushes.Green;
            }
            else
            {
                tbMaxUsers.BorderBrush = Brushes.Red; 
                check = false;
            }
            if (int.TryParse(tbQuestionCount.Text, out _) && tbQuestionCount.Text.Length != 0)
            {
                tbQuestionCount.BorderBrush = Brushes.Green;
            }
            else
            {
                tbQuestionCount.BorderBrush = Brushes.Red;
                check = false;
            }
            if (int.TryParse(tbAnswerTimeout.Text, out _) && tbAnswerTimeout.Text.Length != 0)
            {
                tbAnswerTimeout.BorderBrush = Brushes.Green;
            }
            else
            {
                tbAnswerTimeout.BorderBrush = Brushes.Red;
                check = false;
            }

            if (check)
            {
                MessageBox.Show("Ok");
                string json = JsonConvert.SerializeObject(request);
                PacketInfo packetToSend = new PacketInfo() { code = CreateRoomRequestCode, data = json };
                communicator.SendPacket(packetToSend);

                PacketInfo receivedPacket = this.communicator.GetMessageFromServer();

                if (receivedPacket.code == CreateRoomResponseCode)
                {
                    MessageBox.Show("The room created successfully...", "success", MessageBoxButton.OK);
                    MenuWindow menuWindow = new MenuWindow(ref communicator, username);
                    Close();
                    menuWindow.ShowDialog();
                }
                else //if (receivedPacket.code == ErrorResponseCode)
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
        /// Opens menu window and closes create room window
        /// </summary>
        private void MenuClick(object sender, MouseButtonEventArgs e)
        {
            MenuWindow menuWindow = new MenuWindow(ref communicator, username);
            Close();
            menuWindow.ShowDialog();
        }
    }
}
