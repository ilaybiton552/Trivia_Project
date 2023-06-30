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
    /// Interaction logic for GameResultWindow.xaml
    /// </summary>
    public partial class GameResultWindow : Window
    {
        private List<PlayerResult> results;
        private string username;
        private Communicator communicator;
        public GameResultWindow(ref Communicator communicator, string username, List<PlayerResult> results)
        {
            InitializeComponent();
            WindowStartupLocation = System.Windows.WindowStartupLocation.CenterScreen;
            this.communicator = communicator;
            this.username = username;
            this.results = results.OrderBy(result => -result.rightAnswers).ToList();
            DisplayResults();
        }

        /// <summary>
        /// Displayes the results of the game
        /// </summary>
        private void DisplayResults()
        {
            foreach (PlayerResult result in results) 
            {
                TextBlock textBlock = new TextBlock();
                textBlock.Foreground = Brushes.White;
                textBlock.Text = result.username + " score: " + result.rightAnswers.ToString() + " average time: " + Math.Round(result.averageTime, 2).ToString();
                scores.Children.Add(textBlock);
            }
        }

        /// <summary>
        /// Click event, closes the score window
        /// </summary>
        private void ExitClick(object sender, RoutedEventArgs e)
        {
            MenuWindow menuWindow = new MenuWindow(ref communicator, username);
            Application.Current.Windows[0].Close(); // closing GameWindow
            Close();
            menuWindow.ShowDialog();
        }
    }
}
