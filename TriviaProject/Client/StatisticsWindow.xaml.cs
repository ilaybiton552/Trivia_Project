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
    /// Interaction logic for StatisticsWindow.xaml
    /// </summary>
    public partial class StatisticsWindow : Window
    {
        private Communicator communicator;
        private string username;

        public StatisticsWindow(ref Communicator communicator, string username)
        {
            InitializeComponent();
            WindowStartupLocation = System.Windows.WindowStartupLocation.CenterScreen;
            this.communicator = communicator;
            this.username = username;
        }

        /// <summary>
        /// Goes to window personal stats
        /// </summary>
        private void PersonlStatisticsClick(object sender, RoutedEventArgs e)
        {
            PersonalStatsWindow personalStatsWindow = new PersonalStatsWindow(ref communicator, username);
            Close();
            personalStatsWindow.ShowDialog();
        }

        /// <summary>
        /// Goes to window high scores
        /// </summary>
        private void HighScoresClick(object sender, RoutedEventArgs e)
        {
            HighScoreWindow highScoreWindow = new HighScoreWindow(ref communicator, username);
            Close();
            highScoreWindow.ShowDialog();
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
