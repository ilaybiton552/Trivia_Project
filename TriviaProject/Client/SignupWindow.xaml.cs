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
    /// Interaction logic for SignupWindow.xaml
    /// </summary>
    public partial class SignupWindow : Window
    {
        private User user;
        private Communicator communicator;
        private const int SignupRequestCode = 102;
        private const int SignupResponseCode = 202;

        enum Codes { Success = 1, UserExists = 3, RegexError = 7};

        public SignupWindow(ref Communicator communicator)
        {
            InitializeComponent();
            WindowStartupLocation = System.Windows.WindowStartupLocation.CenterScreen;
            this.communicator = communicator;
            user = new User();
            this.DataContext = user;
        }

        /// <summary>
        /// Clears the data of all the text boxes
        /// </summary>
        private void ClearClick(object sender, RoutedEventArgs e)
        {
            tbUsername.BorderBrush = Brushes.Gray;
            tbPassword.BorderBrush = Brushes.Gray;
            tbEmail.BorderBrush = Brushes.Gray;
            tbAddress.BorderBrush = Brushes.Gray;
            tbPhone.BorderBrush = Brushes.Gray;
            tbBirthdate.BorderBrush = Brushes.Gray;
            user = new User();
            this.DataContext = user;
        }

        /// <summary>
        /// Sends a signup request to the server
        /// </summary>
        private void SignupClick(object sender, RoutedEventArgs e)
        {
            if (!user.isEmpty() && !Validation.GetHasError(tbPassword) && !Validation.GetHasError(tbEmail) && !Validation.GetHasError(tbAddress) && !Validation.GetHasError(tbPhone) && !Validation.GetHasError(tbBirthdate))
            {
                tbUsername.BorderBrush = Brushes.Green;
                tbPassword.BorderBrush = Brushes.Green;
                tbEmail.BorderBrush = Brushes.Green;
                tbAddress.BorderBrush = Brushes.Green;
                tbPhone.BorderBrush = Brushes.Green;
                tbBirthdate.BorderBrush = Brushes.Green;

                string json = JsonConvert.SerializeObject(user);
                PacketInfo packetToSend = new PacketInfo() { code = SignupRequestCode, data = json };
                communicator.SendPacket(packetToSend);

                PacketInfo receivedPacket = this.communicator.GetMessageFromServer();
                if (receivedPacket.code == SignupResponseCode)
                {
                    StatusPacket statusPacket = JsonConvert.DeserializeObject<StatusPacket>(receivedPacket.data);
                    switch ((Codes)statusPacket.status)
                    {
                        case Codes.Success:
                            // when adding menu window, send to there and remove the next 2 lines
                            MessageBox.Show("Sending to menu...", "success", MessageBoxButton.OK);
                            communicator.Close();
                            Close();
                            break;
                        case Codes.UserExists:
                            MessageBox.Show("The user already exists", "Error",
                                MessageBoxButton.OK, MessageBoxImage.Error);
                            break;
                        case Codes.RegexError:
                            MessageBox.Show("Wrong user data format", "Error",
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

            else
            {
                if(user.isEmpty())
                {
                    tbUsername.BorderBrush = Brushes.Red;
                    tbPassword.BorderBrush = Brushes.Red;
                    tbEmail.BorderBrush = Brushes.Red;
                    tbAddress.BorderBrush = Brushes.Red;
                    tbPhone.BorderBrush = Brushes.Red;
                    tbBirthdate.BorderBrush = Brushes.Red;
                }
                if (tbUsername.Text.Length == 0)
                {
                    tbUsername.BorderBrush = Brushes.Red;
                }
                else
                {
                    tbUsername.BorderBrush = Brushes.Green;
                }
                if (Validation.GetHasError(tbPassword) || tbPassword.Text.Length == 0)
                {
                    tbPassword.BorderBrush = Brushes.Red;
                }
                else
                {
                    tbPassword.BorderBrush = Brushes.Green;
                }
                if (Validation.GetHasError(tbEmail) || tbEmail.Text.Length == 0)
                {
                    tbEmail.BorderBrush = Brushes.Red;
                }
                else
                {
                    tbEmail.BorderBrush = Brushes.Green;
                }
                if (Validation.GetHasError(tbAddress) || tbAddress.Text.Length == 0)
                {
                    tbAddress.BorderBrush = Brushes.Red;
                }
                else
                {
                    tbAddress.BorderBrush = Brushes.Green;
                }
                if (Validation.GetHasError(tbPhone) || tbPhone.Text.Length == 0)
                {
                    tbPhone.BorderBrush = Brushes.Red;
                }
                else
                {
                    tbPhone.BorderBrush = Brushes.Green;
                }
                if (Validation.GetHasError(tbBirthdate) || tbBirthdate.Text.Length == 0)
                {
                    tbBirthdate.BorderBrush = Brushes.Red;
                }
                else
                {
                    tbBirthdate.BorderBrush = Brushes.Green;
                }

                MessageBox.Show("Error", "Error", MessageBoxButton.OK);
            }
        }


        /// <summary>
        /// Opens login window and closes sign up window
        /// </summary>
        private void LoginClick(object sender, RoutedEventArgs e)
        {
            LoginWindow loginWindow = new LoginWindow(ref communicator);
            Close();
            loginWindow.ShowDialog();
        }

    }
}
