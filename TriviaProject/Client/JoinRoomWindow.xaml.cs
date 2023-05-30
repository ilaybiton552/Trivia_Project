using Newtonsoft.Json;
using Newtonsoft.Json.Bson;
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
    /// Interaction logic for JoinRoomWindow.xaml
    /// </summary>
    public partial class JoinRoomWindow : Window
    {
        private Communicator communicator;
        private string username;
        private LinkedList<RoomData> roomDataList;
        private const int ErrorResponseCode = 200;
        private const int GetRoomsResponseCode = 204;
        private const int GetRoomsRequestCode = 104;
        private const int JoinRoomResponseCode = 206;
        private const int JoinRoomRequestCode = 108;
        private const int GetPlayersInRoomRequestCode = 105;
        private const int GetPlayersInRoomResponseCode = 205;

        public JoinRoomWindow(ref Communicator communicator, string username)
        {
            InitializeComponent();
            WindowStartupLocation = System.Windows.WindowStartupLocation.CenterScreen;
            this.communicator = communicator;
            this.username = username;
            roomDataList = new LinkedList<RoomData>();
            GetRooms();
            AddRoomsData();
        }

        /// <summary>
        /// Adds the names of all of the rooms as buttons
        /// </summary>
        private void AddRoomsData() 
        {
            for (var it = roomDataList.First; it != null; it = it.Next) 
            {
                Button button = new Button();
                button.Click += RoomClick;
                button.BorderBrush = Brushes.Black;
                button.Background = Brushes.Azure;
                button.Content = it.Value.name;
                button.MouseEnter += ShowRoomDetails;
                button.Tag = it.Value.id;
                rooms.Children.Add(button);
            }
        }

        /// <summary>
        /// Shows the details of the room the mouse is on
        /// </summary>
        private void ShowRoomDetails(object sender, MouseEventArgs e)
        {
            Button button = (Button)sender;
            RoomData roomData = GetRoomData((int)button.Tag);
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
            
        }

        /// <summary>
        /// Gets all of the data of the rooms
        /// </summary>
        private void GetRooms()
        {
            PacketInfo packetToSend = new PacketInfo() { code = GetRoomsRequestCode, data =""};
            communicator.SendPacket(packetToSend);

            PacketInfo receivedPacket = this.communicator.GetMessageFromServer();
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
                players = players.Substring(players.IndexOf(','));

                while (players.IndexOf(',') != -1) // while there are more than 1 playres left
                {
                    temp = players;
                    roomData.players.AddLast(temp.Remove(temp.IndexOf(',')));
                    players = players.Substring(players.IndexOf(','));
                }

                roomData.players.AddLast(players); // inserting last players
            }

        }

        /// <summary>
        /// Opens menu window and closes join room window
        /// </summary>
        private void MenuClick(object sender, MouseButtonEventArgs e)
        {
            MenuWindow menuWindow = new MenuWindow(ref communicator, username);
            Close();
            menuWindow.ShowDialog();
        }
    }
}
