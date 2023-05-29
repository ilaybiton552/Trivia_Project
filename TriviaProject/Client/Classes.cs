﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Security.RightsManagement;
using System.Text;
using System.Threading.Tasks;

namespace Client
{
    public class LoginRequest
    {
        public string username { get; set; }
        public string password { get; set; }
    }

    public class PacketInfo
    {
        public byte code { get; set; }
        public string data { get; set; }
    }

    public class StatusPacket
    {
        public int status {get; set; }
    }

    public class CreateRoomRequest
    {
        public string roomName { get; set; }
        public int maxUsers { get; set; }
        public int questionCount { get; set; }
        public int answerTimeOut { get; set; }
    }
}
