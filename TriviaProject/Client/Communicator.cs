using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;

namespace Client
{
    class Communicator
    {
        private TcpClient client;

        public Communicator()
        {
            client = new TcpClient();
        }
    }
}
