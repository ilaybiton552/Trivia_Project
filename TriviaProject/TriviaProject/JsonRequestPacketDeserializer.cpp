#include "JsonRequestPacketDeserializer.h"

/// <summary>
/// Deserizlizes login request
/// </summary>
/// <param name="buffer">vector of bytes, the login request from the client</param>
/// <returns>struct LoginRequest, struct with the data of login request</returns>
LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(const vector<unsigned char>& buffer)
{
    LoginRequest loginRequest;
    json data = getJsonFromBuffer(buffer);
    loginRequest.password = data["password"];
    loginRequest.username = data["username"];
    return loginRequest;
}

/// <summary>
/// Deserizlizes signup request
/// </summary>
/// <param name="buffer">vector of bytes, the signup request from the client</param>
/// <returns>struct SignupRequest, struct with the data of signup request</returns>
SignupRequest JsonRequestPacketDeserializer::deserializeSignupRequest(const vector<unsigned char>& buffer)
{
    SignupRequest signupRequest;
    json data = getJsonFromBuffer(buffer);
    signupRequest.email = data["email"];
    signupRequest.password = data["password"];
    signupRequest.username = data["username"];
    signupRequest.address = data["address"];
    signupRequest.phoneNumber = data["phone"];
    signupRequest.birthDate = data["birthdate"];
    return signupRequest;
}

/// <summary>
/// Deserizlizes get players in room request
/// </summary>
/// <param name="buffer">vector of bytes, the get players in room request from the client</param>
/// <returns>struct GetPlayersInRoomRequest, struct with the data of get players in room request</returns>
GetPlayersInRoomRequest JsonRequestPacketDeserializer::deserializeGetPlayersInRoomRequest(const vector<unsigned char>& buffer)
{
    GetPlayersInRoomRequest request;
    json data = getJsonFromBuffer(buffer);
    request.roomId = data["roomId"];
    return request;
}

/// <summary>
/// Deserizlizes join room request
/// </summary>
/// <param name="buffer">vector of bytes, the join room request from the client</param>
/// <returns>struct JoinRoomRequest, struct with the data of join room request</returns>
JoinRoomRequest JsonRequestPacketDeserializer::deserializeJoinRoomRequest(const vector<unsigned char>& buffer)
{
    JoinRoomRequest request;
    json data = getJsonFromBuffer(buffer);
    request.roomId = data["roomId"];
    return request;
}

/// <summary>
/// Deserizlizes create room request
/// </summary>
/// <param name="buffer">vector of bytes, the get players in create room client</param>
/// <returns>struct CreateRoomRequest, struct with the data of create room request</returns>
CreateRoomRequest JsonRequestPacketDeserializer::deserializeCreateRoomRequest(const vector<unsigned char>& buffer)
{
    CreateRoomRequest request;
    json data = getJsonFromBuffer(buffer);
    request.roomName = data["roomName"];
    request.maxUsers = data["maxUsers"];
    request.questionCount = data["questionCount"];
    request.answerTimeout = data["answerTimeout"];
    return request;
}

/// <summary>
/// Deserizlizes submit answer request
/// </summary>
/// <param name="buffer">vector of bytes, the sumbit answer request from the client</param>
/// <returns>struct SubmitAnswerRequest, struct with the data of submit answer request</returns>
SubmitAnswerRequest JsonRequestPacketDeserializer::deserializeSubmitAnswerRequest(const vector<unsigned char>& buffer)
{
    SubmitAnswerRequest request;
    json data = getJsonFromBuffer(buffer);
    request.answerId = data["answerId"];
    request.answerTime = data["answerTime"];
    return request;
}

/// <summary>
/// Converts the data of the buffer to json
/// </summary>
/// <param name="buffer">vector of bytes, the request from the client</param>
/// <returns>json, the json from the packet</returns>
json JsonRequestPacketDeserializer::getJsonFromBuffer(const vector<unsigned char>& buffer)
{
    string data(buffer.begin(), buffer.end()); // converts the vector to string
    return json::parse(data);
}
