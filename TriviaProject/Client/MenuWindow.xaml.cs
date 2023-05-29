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

        }

        /// <summary>
        /// Gets to join room window
        /// </summary>
        private void JoinRoomClick(object sender, RoutedEventArgs e)
        {

        }

        /// <summary>
        /// Gets to statistics window
        /// </summary>
        private void StatisticsClick(object sender, RoutedEventArgs e)
        {

        }

        /// <summary>
        /// Exits the client
        /// </summary>
        private void ExitClick(object sender, RoutedEventArgs e)
        {
            communicator.Close();
            Close();
        }

    }
}
