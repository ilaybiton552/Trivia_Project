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
        private User user = new User();

        public SignupWindow()
        {
            InitializeComponent();
            User user = new User();
            this.DataContext = user;
        }

        private void btnClear_Click(object sender, RoutedEventArgs e)
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

        private void btnSignup_Click(object sender, RoutedEventArgs e)
        {
            if (!user.isEmpty() && !Validation.GetHasError(tbPassword) && !Validation.GetHasError(tbEmail) && !Validation.GetHasError(tbAddress) && !Validation.GetHasError(tbPhone) && !Validation.GetHasError(tbBirthdate))
            {
                tbUsername.BorderBrush = Brushes.Green;
                tbPassword.BorderBrush = Brushes.Green;
                tbEmail.BorderBrush = Brushes.Green;
                tbAddress.BorderBrush = Brushes.Green;
                tbPhone.BorderBrush = Brushes.Green;
                tbBirthdate.BorderBrush = Brushes.Green;
                MessageBox.Show("Welcome", "Ok", MessageBoxButton.OK);
                Close();
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
    }
}
