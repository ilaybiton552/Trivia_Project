﻿using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.ComponentModel;
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
        private BackgroundWorker backgroundWorker;
        private int timePerQuestion;

        public GameWindow(ref Communicator communicator, string username, int timePerQuestion)
        {
            InitializeComponent();
            WindowStartupLocation = System.Windows.WindowStartupLocation.CenterScreen;
            this.communicator = communicator;
            this.username = username;
            this.timePerQuestion = timePerQuestion;
            backgroundWorker = new BackgroundWorker();
            SetBackgroundWorkerDetails();
            GetQuestion();
            tbQuestion.Text += question;
            AddAnswers();
        }

        /// <summary>
        /// Sets the details of the background worker
        /// </summary>
        private void SetBackgroundWorkerDetails()
        {
            backgroundWorker.WorkerSupportsCancellation = true;
            backgroundWorker.WorkerReportsProgress = true;
            backgroundWorker.DoWork += BackgroundWorker_DoWork;
            backgroundWorker.ProgressChanged += BackgroundWorker_ProgressChanged;
        }

        /// <summary>
        /// Do the work of the background worker
        /// </summary>
        void BackgroundWorker_DoWork(object sender, DoWorkEventArgs e)
        {
            for (int i = (int)e.Argument; i > 0; i--)
            {
                backgroundWorker.ReportProgress(i);
                Thread.Sleep(1000); // wait for 1 second
            }
            backgroundWorker.ReportProgress(0);
        }

        /// <summary>
        /// the function update the window with thread
        /// </summary>
        void BackgroundWorker_ProgressChanged(object sender, ProgressChangedEventArgs e)
        {
            time.Text = e.ProgressPercentage.ToString();
            if (e.ProgressPercentage == 0)
            {
                SubmitAnswer(NoAnswerId, timePerQuestion);
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
            SubmitAnswer answer = new SubmitAnswer() { answerId = NoAnswerId, answerTime = timePerQuestion };
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
