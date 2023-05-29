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

    public class RoomDataList
    {
        public LinkedListNode<int> id { get; set; }
        public LinkedListNode<string> name { get; set; }
        public LinkedListNode<int> maxPlayers { get; set; }
        public LinkedListNode<int> numOfQuestions { get; set; }
        public LinkedListNode<int> timePerQuestion { get; set; }
        public LinkedListNode<int> isActive { get; set; } 

        public RoomDataList()
        {
            id = new LinkedListNode<int>();
            name = new LinkedListNode<string>();
            maxPlayers = new LinkedListNode<int>();
            numOfQuestions = new LinkedListNode<int>();
            timePerQuestion = new LinkedListNode<int>();
            isActive = new LinkedListNode<int>();
        }
    }

}
