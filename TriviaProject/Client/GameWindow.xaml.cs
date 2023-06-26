using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Timers;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using System.Net;

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
        private const int StatusSuccess = 1;
        private const int NoAnswerId = 4; // when the user doesn't answer on time
        private BackgroundWorker timerBackgroundWorker;
        private BackgroundWorker gameBackgroundWorker;
        private int timePerQuestion;
        private Stopwatch stopwatch;
        private AutoResetEvent gameEvent;

        public GameWindow(ref Communicator communicator, string username, int timePerQuestion)
        {
            InitializeComponent();
            WindowStartupLocation = System.Windows.WindowStartupLocation.CenterScreen;
            this.communicator = communicator;
            this.username = username;
            this.timePerQuestion = timePerQuestion;
            stopwatch = new Stopwatch();
            timerBackgroundWorker = new BackgroundWorker();
            gameBackgroundWorker = new BackgroundWorker();
            gameEvent = new AutoResetEvent(false);
            SetBackgroundWorkerDetails();
            gameBackgroundWorker.RunWorkerAsync(0); // get the first question
        }

        /// <summary>
        /// Sets the details of the background worker
        /// </summary>
        private void SetBackgroundWorkerDetails()
        {
            timerBackgroundWorker.WorkerSupportsCancellation = true;
            timerBackgroundWorker.WorkerReportsProgress = true;
            timerBackgroundWorker.DoWork += TimerBackgroundWorker_DoWork;
            timerBackgroundWorker.ProgressChanged += TimerBackgroundWorker_ProgressChanged;
            timerBackgroundWorker.RunWorkerCompleted += TimerBackgroundWorker_CompletedRun;

            gameBackgroundWorker.WorkerSupportsCancellation = true;
            gameBackgroundWorker.WorkerReportsProgress = true;
            gameBackgroundWorker.DoWork += GameBackgroundWorker_DoWork;
            gameBackgroundWorker.ProgressChanged += GameBackgroundWorker_ProgressChanged;
        }

        /// <summary>
        /// Do the work of the background worker
        /// </summary>
        void TimerBackgroundWorker_DoWork(object sender, DoWorkEventArgs e)
        {
            for (int i = (int)e.Argument; i >= 0 && !e.Cancel && gameBackgroundWorker.IsBusy; i--)
            {
                timerBackgroundWorker.ReportProgress(i);
                if (i != 0) // don't want to wait when time is over
                {
                    // spread 1 second into 10 0.1 second (to be more accurate with cancellation)
                    for (int j = 0; j < 10 && !e.Cancel; j++)
                    {
                        if (timerBackgroundWorker.CancellationPending)
                        {
                            e.Cancel = true;
                        }
                        Thread.Sleep(100); // wait 0.1 second
                    }
                }
            }
        }

        /// <summary>
        /// the function update the window with thread
        /// </summary>
        void TimerBackgroundWorker_ProgressChanged(object sender, ProgressChangedEventArgs e)
        {
            time.Text = e.ProgressPercentage.ToString();
            if (e.ProgressPercentage == 0) // end of time
            {
                SubmitAnswer(NoAnswerId, timePerQuestion);
                gameEvent.Set(); // notify game worker
            }
        }

        /// <summary>
        /// Start the timer again if the game worker is still running
        /// </summary>
        void TimerBackgroundWorker_CompletedRun(object sender, RunWorkerCompletedEventArgs e)
        {
            if (gameBackgroundWorker.IsBusy)
            {
                timerBackgroundWorker.RunWorkerAsync(timePerQuestion);
            }
        }

        /// <summary>
        /// Do the work of the background worker
        /// </summary>
        void GameBackgroundWorker_DoWork(object sender, DoWorkEventArgs e)
        {
            while (GetQuestion() == StatusSuccess && !gameBackgroundWorker.CancellationPending)
            {
                timerBackgroundWorker.CancelAsync();
                gameBackgroundWorker.ReportProgress(0);
                stopwatch.Restart(); // starting the answer time for the user
                gameEvent.WaitOne(); // wait until answer
                Thread.Sleep(250); // wait to see if the client is right or wrong
            }
            GetGameResults();
        }

        /// <summary>
        /// the function update the window with thread
        /// </summary>
        void GameBackgroundWorker_ProgressChanged(object sender, ProgressChangedEventArgs e)
        {
            tbQuestion.Text = "Question: " + question.question;
            if (question.question.Length > 70)
            {
                tbQuestion.FontSize = 20;
            }
            else if (question.question.Length > 55)
            {
                tbQuestion.FontSize = 25;
            }
            else
            {
                tbQuestion.FontSize = 30;
            }
            AddAnswers();
            if (!timerBackgroundWorker.IsBusy) // timer isn't working
            {
                timerBackgroundWorker.RunWorkerAsync(timePerQuestion);
            }
        }

        /// <summary>
        /// Submits the answer of the client to the server
        /// </summary>
        /// <param name="answerId">int, the id of the answer</param>
        /// <param name="answerTime">float, the time it took to the player to answer</param>
        /// <returns>int, the correct answer id</returns>
        private int SubmitAnswer(int answerId, float answerTime)
        {
            SubmitAnswer answer = new SubmitAnswer() { answerId = answerId, answerTime = answerTime };
            string json = JsonConvert.SerializeObject(answer);
            PacketInfo clientPacket = new PacketInfo() { code = SubmitAnswerRequestCode, data = json };
            communicator.SendPacket(clientPacket);

            PacketInfo serverPacket = communicator.GetMessageFromServer();
            if (serverPacket.code != SubmitAnswerResponseCode)
            {
                MessageBox.Show("Error occured", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
                return -1;
            }
            SubmitAnswerResponse response = JsonConvert.DeserializeObject<SubmitAnswerResponse>(serverPacket.data);
            if (response.status != StatusSuccess)
            {
                MessageBox.Show("Error occured", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
                return -1;
            }
            return response.correctAnswerId;
        }

        /// <summary>
        /// Gets the results of the game
        /// </summary>
        private void GetGameResults()
        {
            PacketInfo clientPacket = new PacketInfo() { code = GetGameResultsRequestCode, data = "" };
            communicator.SendPacket(clientPacket);

            PacketInfo serverPacket = communicator.GetMessageFromServer();
            if (serverPacket.code != GetGameResultsResponseCode)
            {
                MessageBox.Show("Error occured", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
                return;
            }
            GameResultResponse response = JsonConvert.DeserializeObject<GameResultResponse>(serverPacket.data);
            if (response.status != StatusSuccess)
            {
                MessageBox.Show("Error occured", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
                return;
            }
            string results = response.results;
            List<PlayerResult> playerResults = new List<PlayerResult>();
            while (results != "")
            {
                PlayerResult currResult = new PlayerResult();

                // get username
                currResult.username = results.Remove(results.IndexOf(','));
                results = results.Substring(results.IndexOf(',') + 1);

                // get right answers
                currResult.rightAnswers = int.Parse(results.Remove(results.IndexOf(',')));
                results = results.Substring(results.IndexOf(',') + 1);

                // get the wrong answers
                currResult.wrongAnswers = int.Parse(results.Remove(results.IndexOf(',')));
                results = results.Substring(results.IndexOf(',') + 1);

                // get average time
                currResult.averageTime = float.Parse(results.Remove(results.IndexOf(';')));
                results = results.Substring(results.IndexOf(';') + 1);

                playerResults.Add(currResult);
            }

            Dispatcher.Invoke(() =>
            {
                GameResultWindow gameResultWindow = new GameResultWindow(ref communicator, username, playerResults);
                gameResultWindow.Show();
            });
        }


        /// <summary>
        /// the function adds answer to the game screen
        /// </summary>
        private void AddAnswers()
        {
            answers.Children.Clear();
            foreach (var answer in question.answers)
            {
                Button button = new Button();
                button.Content += answer.Value;
                button.Tag = answer.Key;
                button.Click += AnswerClick;
                answers.Children.Add(button);
            }
        }

        /// <summary>
        /// Gets the question from the server
        /// </summary>
        /// <returns>int, the status of the packet</returns>
        private int GetQuestion()
        {
            PacketInfo packet = new PacketInfo() { code = GetQuestionRequestCode, data = ""};
            communicator.SendPacket(packet);

            PacketInfo receivedPacket = communicator.GetMessageFromServer();
            if (receivedPacket.code != GetQuestionResponseCode)
            {
                MessageBox.Show("Error occured", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
                return -1;
            }

            GetQuestionResponse response = JsonConvert.DeserializeObject<GetQuestionResponse>(receivedPacket.data);
            if (response.status != StatusSuccess) // no more questions left
            {
                return response.status;
            }

            question = new Question();
            question.question = WebUtility.HtmlDecode(response.question);
            question.answers = new Dictionary<int, string>();
            response.answers = WebUtility.HtmlDecode(response.answers);
            while (response.answers != "")
            {
                string temp = response.answers;
                int answerId = int.Parse(temp.Remove(temp.IndexOf(':')));
                response.answers = temp.Substring(response.answers.IndexOf(':') + 1);

                temp = response.answers;
                string answer = temp.Remove(temp.IndexOf(';'));
                response.answers = response.answers.Substring(response.answers.IndexOf(';') + 1);

                question.answers.Add(answerId, answer);
            }

            return response.status;
        }

        /// <summary>
        /// Sends the answer to the server
        /// </summary>
        private void AnswerClick(object sender, RoutedEventArgs e)
        {
            stopwatch.Stop(); // stoping the answer time for the user
            Button answerButton = (Button)sender;
            answerButton.Template = (ControlTemplate)Resources["NoHover"];
            int answerId = (int)answerButton.Tag;
            int correctAnswerId = SubmitAnswer(answerId, (float)(stopwatch.ElapsedMilliseconds / 1000.0));
            if (correctAnswerId == answerId) // correct answer
            {
                answerButton.Background = Brushes.Green;
            }
            else
            {
                answerButton.Background = Brushes.Red;
            }
            gameEvent.Set(); // notify game worker
        }

        /// <summary>
        /// Click for a button which let the player leave the game
        /// </summary>
        private void LeaveClick(object sender, RoutedEventArgs e)
        {
            PacketInfo clientPacket = new PacketInfo() { code = LeaveGameRequestCode, data = "" };
            communicator.SendPacket(clientPacket);
            PacketInfo serverPacket = communicator.GetMessageFromServer();
            if (serverPacket.code != LeaveGameResponseCode)
            {
                MessageBox.Show("Error leaving", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
                return;
            }
            StatusPacket packet = JsonConvert.DeserializeObject<StatusPacket>(serverPacket.data);
            if (packet.status != StatusSuccess)
            {
                MessageBox.Show("Error leaving", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
                return;
            }
            MenuWindow menuWindow = new MenuWindow(ref communicator, username);
            Close();
            menuWindow.ShowDialog();
        }

    }

}
