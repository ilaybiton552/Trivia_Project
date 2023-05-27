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
        public LoginWindow()
        {
            InitializeComponent();
            WindowStartupLocation = System.Windows.WindowStartupLocation.CenterScreen;
            loginRequest = new LoginRequest();
            this.DataContext = loginRequest;
        }

        /// <summary>
        /// Sends a login request to the server
        /// </summary>
        private void LoginClick(object sender, RoutedEventArgs e)
        {
            TcpClient client = new TcpClient();
            IPEndPoint serverEndPoint = new IPEndPoint(IPAddress.Parse("127.0.0.1"), 8826);
            client.Connect(serverEndPoint);
            NetworkStream clientStream = client.GetStream();

            string json = JsonConvert.SerializeObject(loginRequest);
            byte[] jsonBuffer = new ASCIIEncoding().GetBytes(json);
            byte[] length = BitConverter.GetBytes(jsonBuffer.Length);
            Array.Reverse(length);
            byte[] buffer = new byte[5 + jsonBuffer.Length];
            buffer[0] = 101;
            for (int i = 1; i < 5; i++)
            {
                buffer[i] = length[i - 1];
            }
            for (int i = 0; i < jsonBuffer.Length; i++)
            {
                buffer[i + 5] = jsonBuffer[i];
            }
            clientStream.Write(buffer, 0, buffer.Length);
            clientStream.Flush();
            buffer = new byte[4096];
            int bytesRead = clientStream.Read(buffer, 0, 4096);
            string message = Encoding.Default.GetString(buffer);
            MessageBox.Show(message);
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
