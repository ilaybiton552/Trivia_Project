using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
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
using System.Windows.Navigation;
using System.Windows.Shapes;
using Newtonsoft.Json;

namespace Client
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class LoginWindow : Window
    {
        private LoginRequest loginRequest;
        private Communicator communicator;
        private const int loginRequestCode = 101;
        private const int loginResponseCode = 201;

        enum Codes { Success = 1, UserDoesNotExist, WrongPassword = 4, UserIsLogged};

        public LoginWindow()
        {
            InitializeComponent();
            WindowStartupLocation = System.Windows.WindowStartupLocation.CenterScreen;
            communicator = new Communicator();
            loginRequest = new LoginRequest();
            this.DataContext = loginRequest;
        }

        public LoginWindow(ref Communicator communicator)
        {
            InitializeComponent();
            WindowStartupLocation = System.Windows.WindowStartupLocation.CenterScreen;
            this.communicator = communicator;
            loginRequest = new LoginRequest();
            this.DataContext = loginRequest;
        }

        /// <summary>
        /// Sends a login request to the server
        /// </summary>
        private void LoginClick(object sender, RoutedEventArgs e)
        {
            string json = JsonConvert.SerializeObject(loginRequest);
            PacketInfo packetToSend = new PacketInfo() { code=loginRequestCode, data=json };
            communicator.SendPacket(packetToSend);

            PacketInfo receivedPacket = communicator.GetMessageFromServer();
            if (receivedPacket.code == loginResponseCode)
            {
                StatusPacket statusPacket = JsonConvert.DeserializeObject<StatusPacket>(receivedPacket.data);
                switch ((Codes)statusPacket.status)
                {
                    case Codes.Success:
                        MenuWindow menuWindow = new MenuWindow(ref communicator);
                        Close();
                        menuWindow.ShowDialog();
                        break;
                    case Codes.UserDoesNotExist:
                        MessageBox.Show("The user doesn't exist", "Error", 
                            MessageBoxButton.OK, MessageBoxImage.Error);
                        break;
                    case Codes.WrongPassword:
                        MessageBox.Show("Wrong password", "Error", 
                            MessageBoxButton.OK, MessageBoxImage.Error);
                        break;
                    case Codes.UserIsLogged:
                        MessageBox.Show("The user is already logged", "Error", 
                            MessageBoxButton.OK, MessageBoxImage.Error);
                        break;
                }
            }
            else
            {
                MessageBox.Show("An error occured", "Error",
                    MessageBoxButton.OK, MessageBoxImage.Error);
            }
        }

        /// <summary>
        /// Clears the data of the text boxes of username and password
        /// </summary>
        private void ClearClick(object sender, RoutedEventArgs e)
        {
            usernameTextBox.Text = "";
            passwordTextBox.Text = "";
        }

        /// <summary>
        /// Opens sign up window and closes login window
        /// </summary>
        private void SignUpClick(object sender, RoutedEventArgs e)
        {
            SignupWindow signupWindow = new SignupWindow(ref communicator);
            Close();
            signupWindow.ShowDialog();
        }

    }
}
