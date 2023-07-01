using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Net;
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
    /// Interaction logic for AddQuestionWindow.xaml
    /// </summary>
    public partial class AddQuestionWindow : Window
    {
        private Communicator communicator;
        private string username;
        private AddQuestion question;
        private const int AddQuestionRequestCode = 118;
        private const int AddQuestionResponseCode = 218;

        public AddQuestionWindow(ref Communicator communicator, string username)
        {
            InitializeComponent();
            WindowStartupLocation = System.Windows.WindowStartupLocation.CenterScreen;
            this.communicator = communicator;
            this.username = username;
            question = new AddQuestion();
            this.DataContext = question;
        }

        /// <summary>
        /// Clears the data of all the text boxes
        /// </summary>
        private void ClearClick(object sender, RoutedEventArgs e)
        {
            question = new AddQuestion();
            this.DataContext = question;

            tbQuestion.BorderBrush = Brushes.Gray;
            tbCorrectAnswer.BorderBrush = Brushes.Gray;
            tbIncorrectAnswer1.BorderBrush = Brushes.Gray;
            tbIncorrectAnswer2.BorderBrush = Brushes.Gray;
            tbIncorrectAnswer3.BorderBrush = Brushes.Gray;
        }

        /// <summary>
        /// Sends the question to the server
        /// </summary>
        private void SendClick(object sender, RoutedEventArgs e)
        {
            tbQuestion.BorderBrush = tbQuestion.Text.Length == 0 ? Brushes.Red : Brushes.Green;
            tbCorrectAnswer.BorderBrush = tbCorrectAnswer.Text.Length == 0 ? Brushes.Red : Brushes.Green;
            tbIncorrectAnswer1.BorderBrush = tbIncorrectAnswer1.Text.Length == 0 ? Brushes.Red : Brushes.Green;
            tbIncorrectAnswer2.BorderBrush = tbIncorrectAnswer2.Text.Length == 0 ? Brushes.Red : Brushes.Green;
            tbIncorrectAnswer3.BorderBrush = tbIncorrectAnswer3.Text.Length == 0 ? Brushes.Red : Brushes.Green;

            if (tbQuestion.BorderBrush == Brushes.Red || tbCorrectAnswer.BorderBrush == Brushes.Red || tbIncorrectAnswer1.BorderBrush == Brushes.Red || 
                tbIncorrectAnswer2.BorderBrush == Brushes.Red || tbIncorrectAnswer3.BorderBrush == Brushes.Red)
            {
                MessageBox.Show("Empty field", "Error", MessageBoxButton.OK);
            }
            else
            {
                // send the question to server
                string json = JsonConvert.SerializeObject(question);
                PacketInfo packetToSend = new PacketInfo() { code = AddQuestionRequestCode, data = json };
                communicator.SendPacket(packetToSend);

                PacketInfo receivedPacket = this.communicator.GetMessageFromServer();
                if(receivedPacket.code == AddQuestionResponseCode)
                {
                    MessageBox.Show("Added the question");
                    MenuWindow menuWindow = new MenuWindow(ref communicator, username);
                    Close();
                    menuWindow.ShowDialog();                           
                }
                else
                {
                    MessageBox.Show(receivedPacket.code.ToString(), "Error",
                        MessageBoxButton.OK, MessageBoxImage.Error);
                }
            }

        }

        /// <summary>
        /// Goes a window back (menu window)
        /// </summary>
        private void BackClick(object sender, RoutedEventArgs e)
        {
            MenuWindow menuWindow = new MenuWindow(ref communicator, username);
            Close();
            menuWindow.ShowDialog();
        }
    }
}
