using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading;
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
    /// Interaction logic for GameWindow.xaml
    /// </summary>
    public partial class GameWindow : Window
    {
        private Communicator communicator;
        private string username;
        private Question question;
        private const int LeaveGameResponseCode = 214;
        private const int LeaveGameRequestCode = 114;
        private const int GetQuestionResponseCode = 215;
        private const int GetQuestionRequestCode = 115;
        private const int SubmitAnswerResponseCode = 216;
        private const int SubmitAnswerRequestCode = 116;
        private const int GetGameResultsResponseCode = 217;
        private const int GetGameResultsRequestCode = 117;

        public GameWindow(ref Communicator communicator, string username)
        {
            InitializeComponent();
            WindowStartupLocation = System.Windows.WindowStartupLocation.CenterScreen;
            this.communicator = communicator;
            this.username = username;
            GetQuestion();
            tbQuestion.Text += question;
            AddAnswers();
        }

      
        /// <summary>
        /// the function adds answer to the game screen
        /// </summary>
        private void AddAnswers()
        {
            answers.Children.Clear();
            for (int i = 0; i < 4; i++)
            {
                Button button = new Button();
                button.Content += i.ToString();
                button.Content += ".";
                button.Content += question.answers[i];
                button.Tag = i;
                button.Click += AnswerClick;
                answers.Children.Add(button);
            }
        }

        private void GetQuestion()
        {
            PacketInfo packet = new PacketInfo() { code = GetQuestionRequestCode, data = ""};
            communicator.SendPacket(packet);

            PacketInfo receivedPacket = communicator.GetMessageFromServer();
            if (receivedPacket.code != GetQuestionResponseCode)
            {
                MessageBox.Show("Error occured", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
                return;
            }

            GetQuestionResponse response = JsonConvert.DeserializeObject<GetQuestionResponse>(receivedPacket.data);

            question = new Question();
            question.question = response.question;
            while (response.answers != "")
            {
                string temp = response.answers;
                int answerId = int.Parse(temp.Remove(temp.IndexOf(':')));
                response.answers = temp.Substring(response.answers.IndexOf(':') + 1);

                temp = response.answers;
                string answer = temp.Remove(temp.IndexOf(','));
                response.answers = response.answers.Substring(response.answers.IndexOf(',') + 1);

                question.answers.Add(answer);
            }
        }

        private void AnswerClick(object sender, RoutedEventArgs e)
        {

        }
        
    }

}
