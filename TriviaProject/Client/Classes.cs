using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Client
{
    class LoginRequest
    {
        public string username { get; set; }
        public string password { get; set; }
    }

    class PacketInfo
    {
        public byte code;
        public string data { get; set; }
    }
}
