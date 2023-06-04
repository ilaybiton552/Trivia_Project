#include "JsonResponsePacketSerializer.h"

/// <summary>
/// Serializes an error response
/// </summary>
/// <param name="errorResponse">struct ErrorResponse, the response to serialize</param>
/// <returns>vector of bytes, the serialized response</returns>
vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(ErrorResponse errorResponse)
{
    json response = { {"message", errorResponse.message} };
    return makeSerializedPacket(response, ERROR_RESPONSE_CODE);
}

/// <summary>
/// Serializes a login response
/// </summary>
/// <param name="loginResponse">struct LoginResponse, the response to serialize</param>
/// <returns>vector of bytes, the serialized response</returns>
vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(LoginResponse loginResponse)
{
    json response = { {"status", loginResponse.status} };
    return makeSerializedPacket(response, LOGIN_RESPONSE_CODE);
}

/// <summary>
/// Serializes an error response
/// </summary>
/// <param name="signupResponse">struct SignupResponse, the response to serialize</param>
/// <returns>vector of bytes, the serialized response</returns>
vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(SignupResponse signupResponse)
{
    json response = { {"status", signupResponse.status} };
    return makeSerializedPacket(response, SIGNUP_RESPONSE_CODE);
}

/// <summary>
/// Serializes a logout response
/// </summary>
/// <param name="logoutResponse">LogoutResponse, the response to serialize</param>
/// <returns>vector of bytes, the serialized response</returns>
vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(LogoutResponse logoutResponse)
{
    json response = { {"status", logoutResponse.status} };
    return makeSerializedPacket(response, LOGOUT_RESPONSE_CODE);
}

/// <summary>
/// Serializes a get room response
/// </summary>
/// <param name="getRoomResponse">GetRoomResponse, the response to serialize</param>
/// <returns>vector of bytes, the serialized response</returns>
vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(GetRoomResponse getRoomResponse)
{
    string rooms; // id,name,maxPlayers,numQuestions,timeQuestions,isActive;...
    for (auto it = getRoomResponse.rooms.begin(); it != getRoomResponse.rooms.end(); ++it)
    {
        rooms += std::to_string(it->id);
        rooms += ',';
        rooms += it->name;
        rooms += ',';
        rooms += std::to_string(it->maxPlayers);
        rooms += ',';
        rooms += std::to_string(it->numOfQuestionsInGame);
        rooms += ',';
        rooms += std::to_string(it->timePerQuestion);
        rooms += ',';
        rooms += std::to_string(it->isActive);
        rooms += ';';
    }
    json response = { {"rooms", rooms} };
    return makeSerializedPacket(response, GET_ROOM_RESPONSE_CODE);
}

/// <summary>
/// Serializes a get player in room response
/// </summary>
/// <param name="getPlayersInRoomResponse">GetPlayersInRoomResponse, the response to serialize</param>
/// <returns>vector of bytes, the serialized response</returns>
vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(GetPlayersInRoomResponse getPlayersInRoomResponse)
{
    string players;
    for (auto it = getPlayersInRoomResponse.players.begin(); it != getPlayersInRoomResponse.players.end(); ++it)
    {
        players += *it;
        players += ",";
    }
    if (!players.empty())
    {
        players.pop_back(); // deleting last comma
    }
    json response = { {"players", players} };
    return makeSerializedPacket(response, GET_PLAYERS_IN_ROOM_RESPONSE_CODE);
}

/// <summary>
/// Serializes a join room response
/// </summary>
/// <param name="joinRoomResponse">JoinRoomResponse, the response to serialize</param>
/// <returns>vector of bytes, the serialized response</returns>
vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(JoinRoomResponse joinRoomResponse)
{
    json response = { {"status", joinRoomResponse.status} };
    return makeSerializedPacket(response, JOIN_ROOM_RESPONSE_CODE);
}

/// <summary>
/// Serializes a create room response
/// </summary>
/// <param name="createRoomResponse">CreateRoomResponse, the response to serialize</param>
/// <returns>vector of bytes, the serialized response</returns>
vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(CreateRoomResponse createRoomResponse)
{
    json response = { {"status", createRoomResponse.status}, {"roomId", createRoomResponse.roomId}};
    return makeSerializedPacket(response, CREATE_ROOM_RESPONSE_CODE);
}

/// <summary>
/// Serializes a get high score response
/// </summary>
/// <param name="scoreResponse">getHighScoreResponse, the response to serialize</param>
/// <returns>vector of bytes, the serialized response</returns>
vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(getHighScoreResponse scoreResponse)
{
    string usersStatistics;
    for (auto it = scoreResponse.statistics.begin(); it != scoreResponse.statistics.end(); ++it)
    {
        usersStatistics += *it;
        usersStatistics += ';';
    }
    json response = { {"highScores", usersStatistics} };
    return makeSerializedPacket(response, GET_HIGH_SCORE_RESPONSE_CODE);
}

/// <summary>
/// Serializes a stats response
/// </summary>
/// <param name="statsResponse">getPersonalStatsResponse, the response to serialize</param>
/// <returns>vector of bytes, the serialized response</returns>
vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(getPersonalStatsResponse statsResponse)
{
    json response = { {"numOfGames", statsResponse.numOfGames}, {"numOfRightAnswers", statsResponse.rightAnswers}, 
                    {"numOfWrongAnswers", statsResponse.wrongAnswers}, {"averageAnswerTime", statsResponse.averageTime}};
    return makeSerializedPacket(response, GET_PERSONAL_STATS_RESPONSE_CODE);
}

vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(CloseRoomResponse closeRoomResponse)
{

}

vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(StartGameResponse startGameResponse)
{

}

vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(GetRoomStateResponse getRoomStateResponse)
{

}

vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(LeaveRoomResponse leaveRoomResponse)
{

}

/// <summary>
/// Converts a number to a byte
/// </summary>
/// <param name="num">unsigned int, the number to convert</param>
/// <returns>vector of bytes, the converted number</returns>
vector<unsigned char> JsonResponsePacketSerializer::convertNumberToByte(const unsigned int num)
{
    vector<unsigned char> numberInBytes;
    for (int i = 0; i < MAX_BYTES_UNSIGNED_INT; i++)
    {
        // >> binary right shift, & binary and
        numberInBytes.push_back((num >> NUM_OF_BITS_IN_BYTE * i) & MAX_VALUE_OF_BYTE); 
    }
    std::reverse(numberInBytes.begin(), numberInBytes.end());
    return numberInBytes;
}

/// <summary>
/// Converts json to bytes
/// </summary>
/// <param name="jsonObject">json, the object to convert</param>
/// <returns>vector of bytes, the json as bytes</returns>
vector<unsigned char> JsonResponsePacketSerializer::convertJsonToByte(const json jsonObject)
{
    vector<unsigned char> jsonAsBytes;
    string jsonAsString = jsonObject.dump();
    for (const unsigned char byte : jsonAsString)
    {
        jsonAsBytes.push_back(byte);
    }
    return jsonAsBytes;
}

/// <summary>
/// Creates the serialized packet
/// </summary>
/// <param name="packetData">json, the data of the packet</param>
/// <returns>vector of bytes, the serialized packet</returns>
vector<unsigned char> JsonResponsePacketSerializer::makeSerializedPacket(const json packetData, const int code)
{
    vector<unsigned char> buffer; // buffer as the protocol structure
    vector<unsigned char> data; // the data of the message
    vector<unsigned char> dataSize; // the size of the data

    buffer.push_back(convertNumberToByte(code)[FIRST_BYTE_INDEX]);
    data = convertJsonToByte(packetData);
    dataSize = convertNumberToByte(data.size());
    buffer.insert(buffer.end(), dataSize.begin(), dataSize.end());
    buffer.insert(buffer.end(), data.begin(), data.end());

    return buffer;
}
