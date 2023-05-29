using System;
using System.Collections.Generic;
using System.Linq;
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

    public class PersonalStatistics
    {
        public int numOfGames { get; set; }
        public int numOfRightAnswer { get; set; }
        public int numOfWrongAnswers { get; set; }
        public float averageAnswerTime { get; set; }
    }

    public class HighScores
    {
        public string highScores { get; set;}
    }

}
