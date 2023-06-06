using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
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
    /// Interaction logic for RoomWindow.xaml
    /// </summary>
    public partial class RoomWindow : Window
    {
        private Communicator communicator;
        private string username;
        private RoomData roomData;
        private const int GetPlayersRequestCode = 105;
        private const int GetPlayersResponseCode = 205;
        private const int CloseRoomRequestCode = 110;
        private const int CloseRoomResponseCode = 210;
        private const int LeaveRoomRequestCode = 113;
        private const int LeaveRoomResponseCode = 213;
        private const int StartGameRequestCode = 111;
        private const int StartGameResponseCode = 211;


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
            
        }

        /// <summary>
        /// Gets the players in the room
        /// </summary>
        private void GetPlayers()
        {
            // sends packet to server
            string json = JsonConvert.SerializeObject(new RoomIdRequest() { roomId = roomData.id });
            PacketInfo clientPacket = new PacketInfo() { code = GetPlayersRequestCode, data = json };
            communicator.SendPacket(clientPacket);

            // gets message from server
            PacketInfo serverPacket = communicator.GetMessageFromServer();
            if (serverPacket.code != GetPlayersResponseCode)
            {
                MessageBox.Show("Error occured", "Error",
                    MessageBoxButton.OK, MessageBoxImage.Error);
                return;
            }
            GetPlayersResponse response = JsonConvert.DeserializeObject<GetPlayersResponse>(serverPacket.data);
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

                // getting the message from the server
                PacketInfo serverPacket = communicator.GetMessageFromServer();
                if (serverPacket.code != CloseRoomResponseCode)
                {
                    MessageBox.Show("Error closing the room", "Error",
                        MessageBoxButton.OK, MessageBoxImage.Error);
                    return;
                }
            }
            else
            {
                PacketInfo clientPacket = new PacketInfo() { code = LeaveRoomRequestCode, data = "" };
                communicator.SendPacket(clientPacket);

                // getting the message from the server
                PacketInfo serverPacket = communicator.GetMessageFromServer();
                if (serverPacket.code != LeaveRoomResponseCode)
                {
                    MessageBox.Show("Error leaving the room", "Error",
                        MessageBoxButton.OK, MessageBoxImage.Error);
                    return;
                }
            }

            MenuWindow menuWindow = new MenuWindow(ref communicator, username);
            Close();
            menuWindow.ShowDialog();
        }

        /// <summary>
        /// the function starts the game
        /// </summary>
        private void StartGameClick(object sender, RoutedEventArgs e)
        {
            PacketInfo clientPacket = new PacketInfo() { code = StartGameRequestCode, data = "" };
            communicator.SendPacket(clientPacket);

            // getting the message from the server
            PacketInfo serverPacket = communicator.GetMessageFromServer();
            if (serverPacket.code != StartGameResponseCode)
            {
                MessageBox.Show("Error starting the game", "Error",
                    MessageBoxButton.OK, MessageBoxImage.Error);
                return;
            }
        }
    }
}
