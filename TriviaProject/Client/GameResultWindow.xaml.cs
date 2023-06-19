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
        List<PlayerResult> results;
        public GameResultWindow(List<PlayerResult> results)
        {
            InitializeComponent();
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
                textBlock.Text = result.username + " score: " + result.rightAnswers.ToString() + " average time: " + result.averageTime.ToString();
                scores.Children.Add(textBlock);
            }
        }

        /// <summary>
        /// Click event, closes the score window
        /// </summary>
        private void ExitClick(object sender, RoutedEventArgs e)
        {
            Close();
        }
    }
}
