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
        public MenuWindow(ref Communicator communicator)
        {
            InitializeComponent();
            this.communicator = communicator;
            WindowStartupLocation = System.Windows.WindowStartupLocation.CenterScreen;
        }
    }
}
