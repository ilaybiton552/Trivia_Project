﻿using Newtonsoft.Json;
using Newtonsoft.Json.Converters;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Net.Sockets;
using System.Runtime.InteropServices;
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
    /// Interaction logic for RoomWindow.xaml
    /// </summary>
    public partial class RoomWindow : Window
    {
        private Communicator communicator;
        private string username;
        private RoomData roomData;
        private const int GetRoomStateRequestCode = 112;
        private const int GetRoomStateResponseCode = 212;
        private const int CloseRoomRequestCode = 110;
        private const int CloseRoomResponseCode = 210;
        private const int LeaveRoomRequestCode = 113;
        private const int LeaveRoomResponseCode = 213;
        private const int StartGameRequestCode = 111;
        private const int StartGameResponseCode = 211;
        private const int GetPlayersInRoomResponse = 205;
        private const int StatusSuccess = 1;
        private BackgroundWorker backgroundWorker;


        public RoomWindow(ref Communicator communicator, string username, RoomData roomData)
        {
            InitializeComponent();
            WindowStartupLocation = System.Windows.WindowStartupLocation.CenterScreen;
            this.communicator = communicator;
            this.username = username;
            this.roomData = roomData;
            UpdateRoomData();
            if (roomData.admin == username)
            {
                leaveButton.Width = 100;
                leaveButton.Content = "Close room";
                Button startGame = new Button();
                startGame.HorizontalAlignment = HorizontalAlignment.Right;
                startGame.VerticalAlignment = VerticalAlignment.Bottom;
                startGame.Content = "Start";
                startGame.Width = 60;
                startGame.Margin = new Thickness(0, 32.5, 5, 5);
                startGame.Click += StartGameClick;
                Grid.SetRow(startGame, 2);
                grid.Children.Add(startGame);
            }
            else
            {
                leaveButton.Content = "Leave";
                leaveButton.Width = 60;
            }
            backgroundWorker = new BackgroundWorker();
            SetBackgroundWorkerDetails();
        }

        /// <summary>
        /// Gets the players in the room
        /// </summary>
        private void GetPlayers()
        {
            // sends packet to server
            PacketInfo clientPacket = new PacketInfo() { code = GetRoomStateRequestCode, data = "" };
            communicator.SendPacket(clientPacket);

            // gets message from server
            PacketInfo serverPacket = communicator.GetMessageFromServer();
            if (serverPacket.code != GetRoomStateResponseCode)
            {
                MessageBox.Show("Error occured", "Error",
                    MessageBoxButton.OK, MessageBoxImage.Error);
                return;
            }
            GetRoomStateResponse response = JsonConvert.DeserializeObject<GetRoomStateResponse>(serverPacket.data);
            roomData.players = response.players;
            playersTextBlock.Text = roomData.players;
        }

        /// <summary>
        /// Updates the data of the room on the design
        /// </summary>
        private void UpdateRoomData()
        {
            nameTextBlock.Text = roomData.name;
            adminTextBlock.Text = roomData.admin;
            maxPlayersTextBlock.Text = roomData.maxPlayers.ToString();
            numOfQTextBlock.Text = roomData.numOfQuestions.ToString();
            timeTextBlock.Text = roomData.timePerQuestion.ToString();
            GetPlayers();
        }

        /// <summary>
        /// Goes back to menu window, after the user has left or the admin closes the room
        /// </summary>
        private void LeaveClick(object sender, RoutedEventArgs e)
        {
            if (roomData.admin == username)
            {
                PacketInfo clientPacket = new PacketInfo() { code = CloseRoomRequestCode, data = "" };
                communicator.SendPacket(clientPacket);
            }
            else
            {
                PacketInfo clientPacket = new PacketInfo() { code = LeaveRoomRequestCode, data = "" };
                communicator.SendPacket(clientPacket);

                backgroundWorker.CancelAsync();
                PacketInfo serverPacket = communicator.GetMessageFromServer();
                StatusPacket statusPacket = JsonConvert.DeserializeObject<StatusPacket>(serverPacket.data);
                if (statusPacket.status != StatusSuccess)
                {
                    MessageBox.Show("Error leaving the room", "Error",
                        MessageBoxButton.OK, MessageBoxImage.Error);
                    return;
                }
                backgroundWorker.RunWorkerAsync();
                MenuWindow menuWindow = new MenuWindow(ref communicator, username);
                Close();
                menuWindow.ShowDialog();
            }
        }

        /// <summary>
        /// the function starts the game
        /// </summary>
        private void StartGameClick(object sender, RoutedEventArgs e)
        {
            PacketInfo clientPacket = new PacketInfo() { code = StartGameRequestCode, data = "" };
            communicator.SendPacket(clientPacket);
        }

        /// <summary>
        /// Sets the details of the background worker
        /// </summary>
        private void SetBackgroundWorkerDetails()
        {
            backgroundWorker.WorkerSupportsCancellation = true;
            backgroundWorker.WorkerReportsProgress = true;
            backgroundWorker.DoWork += backgroundWorker_DoWork;
            backgroundWorker.ProgressChanged += backgroundWorker_ProgressChanged;
            backgroundWorker.RunWorkerAsync();
        }

        /// <summary>
        /// the function starts the background worker main thread
        /// </summary>
        void backgroundWorker_DoWork(object sender, DoWorkEventArgs e)
        {
            while (!backgroundWorker.CancellationPending)
            {
                PacketInfo serverPacket = communicator.GetMessageFromServer();
                backgroundWorker.ReportProgress(0, serverPacket);
            }
            e.Cancel = true;
        }

        /// <summary>
        /// the function update the window with thread
        /// </summary>
        void backgroundWorker_ProgressChanged(object sender, ProgressChangedEventArgs e)
        {
            try
            {
                PacketInfo packet = (PacketInfo)e.UserState;
                switch (packet.code)
                {
                    case StartGameResponseCode:
                        HandleStartGameResponse(packet);
                        break;
                    case LeaveRoomResponseCode:
                        HandleLeaveRoomResponse(packet);
                        break;
                    case CloseRoomResponseCode:
                        HandleCloseRoomResponse(packet);
                        break;
                    case GetPlayersInRoomResponse:
                        HandleGetPlayersResponse(packet);
                        break;
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show("Exception - " + ex);
            }
        }

        /// <summary>
        /// Handles with a start game response from the server
        /// </summary>
        /// <param name="packet">PacketInfo, the information of the packet</param>
        private void HandleStartGameResponse(PacketInfo packet)
        {
            StatusPacket statusPacket = JsonConvert.DeserializeObject<StatusPacket>(packet.data);
            if (statusPacket.status != StatusSuccess)
            {
                MessageBox.Show("Error starting the game", "Error",
                    MessageBoxButton.OK, MessageBoxImage.Error);
            }
            else
            {
                backgroundWorker.CancelAsync();
                MessageBox.Show("Starting a game");
            }
        }

        /// <summary>
        /// Handles leave room response
        /// </summary>
        /// <param name="packet">PacketInfo, the information of the packet</param>
        private void HandleLeaveRoomResponse(PacketInfo packet)
        {
            StatusPacket statusPacket = JsonConvert.DeserializeObject<StatusPacket>(packet.data);
            MessageBox.Show("The admin closed this room");
            backgroundWorker.CancelAsync();
            MenuWindow menuWindow = new MenuWindow(ref communicator, username);
            Close();
            menuWindow.ShowDialog();
        }

        /// <summary>
        /// Handles close room response
        /// </summary>
        /// <param name="packet">PacketInfo, the information of the packet</param>
        private void HandleCloseRoomResponse(PacketInfo packet)
        {
            StatusPacket statusPacket = JsonConvert.DeserializeObject<StatusPacket>(packet.data);
            if (statusPacket.status != StatusSuccess)
            {
                MessageBox.Show("Error closing the room", "Error", 
                    MessageBoxButton.OK, MessageBoxImage.Error);
            }
            else
            {
                backgroundWorker.CancelAsync();
                MenuWindow menuWindow = new MenuWindow(ref communicator, username);
                Close();
                menuWindow.ShowDialog();
            }
        }

        /// <summary>
        /// Handles get players response
        /// </summary>
        /// <param name="packet">PacketInfo, the information of the packet</param>
        private void HandleGetPlayersResponse(PacketInfo packet)
        {
            GetPlayersResponse playersPacket = JsonConvert.DeserializeObject<GetPlayersResponse>(packet.data);
            playersTextBlock.Text = playersPacket.players;
        }

    }
}
