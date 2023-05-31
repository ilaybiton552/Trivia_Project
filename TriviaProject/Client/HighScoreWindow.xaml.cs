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
    /// Interaction logic for HighScoreWindow.xaml
    /// </summary>
    public partial class HighScoreWindow : Window
    {
        private Communicator communicator;
        private string username;
        private HighScoresDetails scores;
        private const int getHighScoreRequestCode = 107;
        private const int getHighScoreResponseCode = 208;
        private const int numOfScores = 3;

        public HighScoreWindow(ref Communicator communicator, string username)
        {
            InitializeComponent();
            WindowStartupLocation = System.Windows.WindowStartupLocation.CenterScreen;
            this.communicator = communicator;
            this.username = username;
            scores = new HighScoresDetails();
            GetHighScores();
            this.DataContext = scores;
        }

        /// <summary>
        /// Gets the high scores from the server
        /// </summary>
        private void GetHighScores()
        {
            PacketInfo clientPacket = new PacketInfo() { code = getHighScoreRequestCode, data = "b" };
            communicator.SendPacket(clientPacket);

            PacketInfo serverPacket = communicator.GetMessageFromServer();
            if (serverPacket.code != getHighScoreResponseCode)
            {
                MessageBox.Show("An error has occured", "Error",
                    MessageBoxButton.OK, MessageBoxImage.Error);
                return;
            }
            HighScores highScores = JsonConvert.DeserializeObject<HighScores>(serverPacket.data);

            for (int i = 0; i < numOfScores && highScores.highScores != ""; i++)
            {
                string temp = highScores.highScores;
                scores.usernames[i] = temp.Remove(temp.IndexOf(','));
                // removes the first username in the string
                highScores.highScores = highScores.highScores.Substring(highScores.highScores.IndexOf(',') + 1);
                temp = highScores.highScores;
                scores.scores[i] = int.Parse(temp.Remove(temp.IndexOf(';')));
                // removes the first score in the string
                highScores.highScores = highScores.highScores.Substring(highScores.highScores.IndexOf(';') + 1);
            }

        }

        /// <summary>
        /// Goes a window back (statistics window)
        /// </summary>
        private void BackClick(object sender, RoutedEventArgs e)
        {
            StatisticsWindow statisticsWindow = new StatisticsWindow(ref communicator, username);
            Close();
            statisticsWindow.ShowDialog();
        }

    }
}
