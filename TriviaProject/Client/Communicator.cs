using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;

namespace Client
{
    class Communicator
    {
        private TcpClient client;
        private NetworkStream clientStream;
        private const int port = 8826;
        private const string host = "127.0.0.1";

        public Communicator()
        {
            client = new TcpClient();
            IPEndPoint serverEndPoint = new IPEndPoint(IPAddress.Parse(host), port);
            client.Connect(serverEndPoint);
            clientStream = client.GetStream();
        }

        /// <summary>
        /// Closes the cliet connection
        /// </summary>
        public void Close()
        {
            clientStream.Close();
            client.Close();
        }
    }
}
