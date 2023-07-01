﻿using Newtonsoft.Json;
using Newtonsoft.Json.Bson;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Runtime.CompilerServices;
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
using System.Windows.Media.TextFormatting;
using System.Windows.Shapes;

namespace Client
{
    /// <summary>
    /// Interaction logic for JoinRoomWindow.xaml
    /// </summary>
    public partial class JoinRoomWindow : Window
    {
        private Communicator communicator;
        private string username;
        private LinkedList<RoomData> roomDataList;
        private const int GetRoomsResponseCode = 204;
        private const int GetRoomsRequestCode = 104;
        private const int JoinRoomResponseCode = 206;
        private const int JoinRoomRequestCode = 108;
        private const int GetPlayersInRoomRequestCode = 105;
        private const int GetPlayersInRoomResponseCode = 205;
        private const int SuccesStatus = 1;
        private const int roomNotActive = 0;
        private BackgroundWorker backgroundWorker;

        public JoinRoomWindow(ref Communicator communicator, string username)
        {
            InitializeComponent();
            this.communicator = communicator;
            this.username = username;
            roomDataList = new LinkedList<RoomData>();
            backgroundWorker = new BackgroundWorker();
            SetBackgroundWorkerDetails();
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
            backgroundWorker.RunWorkerAsync();
        }

        /// <summary>
        /// Adds the names of all of the rooms as buttons
        /// </summary>
        private void AddRoomsData() 
        {
            rooms.Children.Clear();
            for (var it = roomDataList.First; it != null; it = it.Next) 
            {
                if (it.Value.isActive == roomNotActive)
                {
                    Button button = new Button();
                    button.Click += RoomClick;
                    button.Content = it.Value.name;
                    button.MouseEnter += ShowRoomDetails;
                    button.Tag = it.Value.id;
                    rooms.Children.Add(button);
                }
            }
        }

        /// <summary>
        /// Shows the details of the room the mouse is on
        /// </summary>
        private void ShowRoomDetails(object sender, MouseEventArgs e)
        {
            Button button = (Button)sender;
            RoomData roomData = GetRoomData((int)button.Tag);
            nameTextBlock.Text = "Name: " + roomData.name;
            adminTextBlock.Text = "   Admin: " + roomData.admin;
            maxPlayersTextBlock.Text = "   Max Players: " + roomData.maxPlayers.ToString();
            numOfQTextBlock.Text = "Number of Questions: " + roomData.numOfQuestions.ToString();
            timeTextBlock.Text = "   Time per Question: " + roomData.timePerQuestion.ToString();
            playersTextBlock.Text = "Players: " + roomData.players;
        }

        /// <summary>
        /// Gets data of a room by its id
        /// </summary>
        /// <param name="roomId">int, the id of the room</param>
        private RoomData GetRoomData(int roomId)
        {
            RoomData roomData = new RoomData();
            for (var it = roomDataList.First; it != null; it = it.Next)
            {
                if (it.Value.id == roomId)
                {
                    roomData = it.Value;
                }
            }
            return roomData;
        }

        /// <summary>
        /// Sends the user to the room he joined
        /// </summary>
        private void RoomClick(object sender, RoutedEventArgs e)
        {
            // sends the join room request packet
            int id = (int)((Button)sender).Tag; // room id
            RoomIdRequest request = new RoomIdRequest() { roomId = id };
            string json = JsonConvert.SerializeObject(request);
            PacketInfo clientPacket = new PacketInfo() { code = JoinRoomRequestCode, data = json };
            communicator.SendPacket(clientPacket);

            // getting the message from the server
            PacketInfo serverPacket = communicator.GetMessageFromServer();
            if (serverPacket.code != JoinRoomResponseCode)
            {
                MessageBox.Show("Error joining room", "Error", 
                    MessageBoxButton.OK, MessageBoxImage.Error);
                return;
            }
            StatusPacket response = JsonConvert.DeserializeObject<StatusPacket>(serverPacket.data);
            if (response.status != SuccesStatus)
            {
                MessageBox.Show("Error joining room", "Error",
                    MessageBoxButton.OK, MessageBoxImage.Error);
                return;
            }

            backgroundWorker.CancelAsync(); // closes the background worker
            RoomWindow roomWindow = new RoomWindow(ref communicator, username, GetRoomData(id));
            roomWindow.WindowStartupLocation = WindowStartupLocation.Manual;
            roomWindow.Left = this.Left;
            roomWindow.Top = this.Top;
            Close();
            roomWindow.ShowDialog();
        }

        /// <summary>
        /// Gets all of the data of the rooms
        /// </summary>
        private void GetRooms()
        {
            PacketInfo packetToSend = new PacketInfo() { code = GetRoomsRequestCode, data =""};
            communicator.SendPacket(packetToSend);

            PacketInfo receivedPacket = communicator.GetMessageFromServer();
            if (receivedPacket.code != GetRoomsResponseCode)
            {
                MessageBox.Show("Error occured", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
                return;
            }
            GetRoomResponse response = JsonConvert.DeserializeObject<GetRoomResponse>(receivedPacket.data);

            while (response.rooms != "") 
            {
                // room id
                string temp = response.rooms;
                RoomData roomData = new RoomData();
                roomData.id = int.Parse(temp.Remove(temp.IndexOf(',')));
                response.rooms = response.rooms.Substring(response.rooms.IndexOf(',') + 1);

                // room name
                temp = response.rooms;
                roomData.name = temp.Remove(temp.IndexOf(','));
                response.rooms = response.rooms.Substring(response.rooms.IndexOf(',') + 1);

                // max players
                temp = response.rooms;
                roomData.maxPlayers = int.Parse(temp.Remove(temp.IndexOf(',')));
                response.rooms = response.rooms.Substring(response.rooms.IndexOf(',') + 1);

                // num of questions
                temp = response.rooms;
                roomData.numOfQuestions = int.Parse(temp.Remove(temp.IndexOf(',')));
                response.rooms = response.rooms.Substring(response.rooms.IndexOf(',') + 1);

                // time per question
                temp = response.rooms;
                roomData.timePerQuestion = int.Parse(temp.Remove(temp.IndexOf(',')));
                response.rooms = response.rooms.Substring(response.rooms.IndexOf(',') + 1);

                // is active
                temp = response.rooms;
                roomData.isActive = int.Parse(temp.Remove(temp.IndexOf(';')));
                response.rooms = response.rooms.Substring(response.rooms.IndexOf(';') + 1);

                GetPlayers(ref roomData);
                roomDataList.AddLast(roomData);
            }

        }

        /// <summary>
        /// Gets the players in the room
        /// </summary>
        /// <param name="roomData">ref of RoomData, the data of the current room</param>
        private void GetPlayers(ref RoomData roomData)
        {
            // sending the packet to the server
            RoomIdRequest request = new RoomIdRequest() { roomId = roomData.id};
            string json = JsonConvert.SerializeObject(request);
            PacketInfo clientPacket = new PacketInfo() { code = GetPlayersInRoomRequestCode, data = json};
            communicator.SendPacket(clientPacket);

            // receiving the packet from the server
            PacketInfo serverPacket = communicator.GetMessageFromServer();
            if (serverPacket.code != GetPlayersInRoomResponseCode)
            {
                MessageBox.Show("Error occured", "Error", 
                    MessageBoxButton.OK, MessageBoxImage.Error); 
                return;
            }
            GetPlayersResponse response = JsonConvert.DeserializeObject<GetPlayersResponse>(serverPacket.data);
            string players = response.players;

            // getting the players
            if (players.IndexOf(',') == -1) // only admin in the room
            {
                roomData.admin = players;
            }
            else
            {
                string temp = players;
                roomData.admin = temp.Remove(temp.IndexOf(','));
            }
            roomData.players = players;
        }

        /// <summary>
        /// the function starts the background worker main thread
        /// </summary>
        void BackgroundWorker_DoWork(object sender, DoWorkEventArgs e)
        {
            while (true)
            {
                if (backgroundWorker.CancellationPending)
                {
                    e.Cancel = true;
                    return;
                }
                backgroundWorker.ReportProgress(0);
                Thread.Sleep(3 * 1000); // wait for 3 seconds
            }
        }

        /// <summary>
        /// the function update the window with thread
        /// </summary>
        void BackgroundWorker_ProgressChanged(object sender, ProgressChangedEventArgs e)
        {
            this.roomDataList.Clear(); // clear the room list
            rooms.Children.Clear(); // clear the window
            GetRooms(); // update the room list
            AddRoomsData(); // add the updated rooms to the window
        }

        /// <summary>
        /// Goes a window back (menu window)
        /// </summary>
        private void BackClick(object sender, RoutedEventArgs e)
        {
            backgroundWorker.CancelAsync(); // closes the background worker
            MenuWindow menuWindow = new MenuWindow(ref communicator, username);
            menuWindow.WindowStartupLocation = WindowStartupLocation.Manual;
            menuWindow.Left = this.Left;
            menuWindow.Top = this.Top;
            Close();
            menuWindow.ShowDialog();
        }
    } 
}
