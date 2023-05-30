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
    /// Interaction logic for RoomWindow.xaml
    /// </summary>
    public partial class RoomWindow : Window
    {
        private Communicator communicator;
        private string username;
        private RoomData roomData;
        private const int GetPlayersRequestCode = 105;
        private const int GetPlayersResponseCode = 205;


        public RoomWindow(ref Communicator communicator, string username, RoomData roomData)
        {
            InitializeComponent();
            WindowStartupLocation = System.Windows.WindowStartupLocation.CenterScreen;
            this.communicator = communicator;
            this.username = username;
            this.roomData = roomData;
            GetPlayers();
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
        }

    }
}
