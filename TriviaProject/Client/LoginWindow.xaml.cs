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
        public LoginWindow()
        {
            InitializeComponent();
            WindowStartupLocation = System.Windows.WindowStartupLocation.CenterScreen;
            communicator = new Communicator();
            loginRequest = new LoginRequest();
            this.DataContext = loginRequest;
        }

        /// <summary>
        /// Sends a login request to the server
        /// </summary>
        private void LoginClick(object sender, RoutedEventArgs e)
        {
            string json = JsonConvert.SerializeObject(loginRequest);
            PacketInfo packetInfo = new PacketInfo() { code=loginRequestCode, data=json };
            communicator.SendPacket(packetInfo);

            //buffer = new byte[4096];
            //int bytesRead = clientStream.Read(buffer, 0, 4096);
            //string message = Encoding.Default.GetString(buffer);
            //MessageBox.Show(message);
        }

        /// <summary>
        /// Clears the data of the text boxes of username and password
        /// </summary>
        private void ClearClick(object sender, RoutedEventArgs e)
        {
            usernameTextBox.Text = "";
            passwordTextBox.Text = "";
        }
    }
}
