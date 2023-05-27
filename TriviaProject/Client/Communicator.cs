﻿using System;
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
        private const int codeIndex = 0;
        private const int dataLengthIndex = 1;
        private const int packetHeaderSize = 5;

        /// <summary>
        /// Starts communication with the server
        /// </summary>
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

        /// <summary>
        /// Sends a packet to the server
        /// </summary>
        /// <param name="code">byte, the code of the packet</param>
        /// <param name="json">string, the json, data of the packet</param>
        public void sendPacket(byte code, string json)
        {
            // gets the json as array of bytes
            byte[] jsonBuffer = new ASCIIEncoding().GetBytes(json);

            // gets the length of the data as bytes
            byte[] length = BitConverter.GetBytes(jsonBuffer.Length);
            Array.Reverse(length);

            // create the packet to send
            byte[] buffer = new byte[packetHeaderSize + jsonBuffer.Length];
            buffer[codeIndex] = code;
            for (int i = 0; i < packetHeaderSize; i++)
            {
                buffer[i + dataLengthIndex] = length[i];
            }
            for (int i = 0; i < jsonBuffer.Length; i++)
            {
                buffer[i + packetHeaderSize] = jsonBuffer[i];
            }
            
            // sends the packet
            clientStream.Write(buffer, 0, buffer.Length);
            clientStream.Flush();
        }

    }
}
