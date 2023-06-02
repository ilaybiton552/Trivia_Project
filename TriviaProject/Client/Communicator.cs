﻿using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;

namespace Client
{
    public class Communicator
    {
        private TcpClient client;
        private NetworkStream clientStream;
        private const int port = 8826;
        private const string host = "127.0.0.1";
        private const int codeIndex = 0;
        private const int dataLengthIndex = 1;
        private const int packetHeaderSize = 5;
        private const int recv = 1024;
        private const int clientLogoutCode = 0;
        private const int statusSuccess = 1;

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
            SendClientLogoutMessage();
            clientStream.Close();
            client.Close();
        }

        /// <summary>
        /// Sends a packet to the server
        /// </summary>
        /// <param name="packetInfo">PacketInfo, the info of the packet</param>
        public void SendPacket(PacketInfo packetInfo)
        {
            byte[] buffer = CreatePacket(packetInfo);
            
            // sends the packet
            clientStream.Write(buffer, 0, buffer.Length);
            clientStream.Flush();
        }

        /// <summary>
        /// Makes the packet to send to the server
        /// </summary>
        /// <param name="packetInfo">PacketInfo, the info of the packet to create</param>
        /// <returns>array of byte, the packet</returns>
        private byte[] CreatePacket(PacketInfo packetInfo)
        {
            // gets the json as array of bytes
            byte[] jsonBuffer = new ASCIIEncoding().GetBytes(packetInfo.data);

            // gets the length of the data as bytes
            byte[] length = BitConverter.GetBytes(jsonBuffer.Length);
            Array.Reverse(length);

            // creates the packet to send
            byte[] buffer = new byte[packetHeaderSize + jsonBuffer.Length];
            buffer[codeIndex] = packetInfo.code;
            for (int i = 0; i < packetHeaderSize - dataLengthIndex; i++)
            {
                buffer[i + dataLengthIndex] = length[i];
            }
            for (int i = 0; i < jsonBuffer.Length; i++)
            {
                buffer[i + packetHeaderSize] = jsonBuffer[i];
            }

            return buffer;
        }

        /// <summary>
        /// Gets the message from the server
        /// </summary>
        /// <returns>PacketInfo, the inforamtion of the packet from the server</returns>
        public PacketInfo GetMessageFromServer()
        {
            PacketInfo packetInfo = new PacketInfo();

            // gets the header of the packet to know how many bytes of data to read
            byte[] buffer = new byte[packetHeaderSize];
            clientStream.Read(buffer, 0, buffer.Length);
            packetInfo.code = buffer[codeIndex];
            Array.Reverse(buffer);
            int dataLength = BitConverter.ToInt32(buffer, 0);

            // gets all of the data of the packet
            packetInfo.data = "";
            while (dataLength > 0)
            {
                buffer = new byte[recv];
                int bytesRead = clientStream.Read(buffer, 0, recv);
                packetInfo.data += Encoding.Default.GetString(buffer);
                dataLength -= bytesRead;
            }

            return packetInfo;
        }

        /// <summary>
        /// Sends a message to the server that the client logged out from the server
        /// </summary>
        private void SendClientLogoutMessage()
        {
            StatusPacket statusPacket = new StatusPacket() { status = statusSuccess};
            string json = JsonConvert.SerializeObject(statusPacket);
            PacketInfo packetInfo = new PacketInfo() { code=clientLogoutCode, data=json };
            SendPacket(packetInfo);
        }

    }
}
