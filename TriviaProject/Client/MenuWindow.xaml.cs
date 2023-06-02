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
    /// Interaction logic for MenuWindow.xaml
    /// </summary>
    public partial class MenuWindow : Window
    {
        private Communicator communicator;
        private string connectedUser;
        private const int logoutCode = 103;
        private const int logoutCodeResponse = 203;
        private const int statusSuccess = 1;
        public MenuWindow(ref Communicator communicator, string username)
        {
            InitializeComponent();
            WindowStartupLocation = System.Windows.WindowStartupLocation.CenterScreen;
            this.communicator = communicator;
            connectedUser = username;
            usernameTextBlock.Text += connectedUser;
        }

        /// <summary>
        /// Gets to create room window
        /// </summary>
        private void CreateRoomClick(object sender, RoutedEventArgs e)
        {
            CreateRoomWindow createRoomWindow = new CreateRoomWindow(ref communicator, connectedUser);
            Close();
            createRoomWindow.ShowDialog();
        }

        /// <summary>
        /// Gets to join room window
        /// </summary>
        private void JoinRoomClick(object sender, RoutedEventArgs e)
        {
            JoinRoomWindow joinRoomWindow = new JoinRoomWindow(ref communicator, connectedUser);
            Close();
            joinRoomWindow.ShowDialog();
        }

        /// <summary>
        /// Gets to statistics window
        /// </summary>
        private void StatisticsClick(object sender, RoutedEventArgs e)
        {
            StatisticsWindow statisticsWindow = new StatisticsWindow(ref communicator, connectedUser);
            Close();
            statisticsWindow.ShowDialog();
        }

        /// <summary>
        /// Exits the client
        /// </summary>
        private void ExitClick(object sender, RoutedEventArgs e)
        {
            communicator.Close();
            Close();
        }

        /// <summary>
        /// Logout from the user and gets login window
        /// </summary>
        private void LogoutClick(object sender, RoutedEventArgs e)
        {
            PacketInfo packetInfo = new PacketInfo() { code=logoutCode, data=""};
            communicator.SendPacket(packetInfo);

            PacketInfo serverMessage = communicator.GetMessageFromServer();
            if (serverMessage.code != logoutCodeResponse)
            {
                MessageBox.Show("An error has occured", "Error", 
                    MessageBoxButton.OK, MessageBoxImage.Error);
                return;
            }
            StatusPacket statusPacket = JsonConvert.DeserializeObject<StatusPacket>(serverMessage.data);
            if (statusPacket.status != statusSuccess) 
            {
                MessageBox.Show("User doesn't logged", "Error",
                    MessageBoxButton.OK, MessageBoxImage.Error);
                return;
            }

            LoginWindow loginWindow = new LoginWindow(ref communicator);
            Close();
            loginWindow.Show();
        }

    }
}
