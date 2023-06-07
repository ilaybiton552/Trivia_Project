using System;
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

    public class PersonalStatistics
    {
        public int numOfGames { get; set; }
        public int numOfRightAnswers { get; set; }
        public int numOfWrongAnswers { get; set; }
        public float averageAnswerTime { get; set; }
    }

    public class HighScores
    {
        public string highScores { get; set;}
    }

    public class HighScoresDetails
    {
        private const int numOfScores = 3;
        public string[] usernames { get; set; }
        public int[] scores { get; set; }
        public HighScoresDetails()
        {
            usernames = new string[numOfScores];
            scores = new int[numOfScores];
        }
    }

    public class CreateRoomRequest
    {
        public string roomName { get; set; }
        public int maxUsers { get; set; }
        public int questionCount { get; set; }
        public int answerTimeout { get; set; }
    }

    public class GetRoomResponse
    {
        public string rooms { get; set; }
    }

    public class RoomData
    {
        public int id { get; set; }
        public string name { get; set; }
        public int maxPlayers { get; set; }
        public int numOfQuestions { get; set; }
        public int timePerQuestion { get; set; }
        public int isActive { get; set; } 

        public string admin { get; set; }
        public string players { get; set; }
    }

    public class RoomIdRequest
    {
        public int roomId { get; set; }
    }

    public class GetPlayersResponse
    {
        public string players { get; set; }
    }

    public class CreateRoomResponse
    {
        public int status { get; set; }
        public int roomId { get; set;}
    }

    public class GetRoomStateResponse
    {
        public int status { get; set; }
        public bool hasGameBegan { get; set; }
        public string players { get; set; }
        public int questionCount { get; set; }
        public int answerTimeout { get; set; }
    }

}
