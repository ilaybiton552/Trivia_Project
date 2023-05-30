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
        /// Adds buttons of all of the rooms
        /// </summary>
        private void AddRoomsData() 
        {
            for (var it = roomDataList.First; it != null; it = it.Next) 
            {
                var button = new Button() { Content = it.Value.name, MaxWidth = 300 };
                buttons.Children.Add(button);
            }
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

                roomDataList.AddLast(roomData);
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
