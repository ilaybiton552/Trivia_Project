#include "JsonRequestPacketDeserializer.h"

/// <summary>
/// Deserializes login request
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
/// Deserializes signup request
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
/// Deserializes get players in room request
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
/// Deserializes join room request
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
/// Deserializes create room request
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
/// Deserializes submit answer request
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
/// Deserializes add question request
/// </summary>
/// <param name="buffer">vector of bytes, the add question request from the client</param>
/// <returns>struct AddQuestionRequest, struct with the data of add question request</returns>
AddQuestionRequest JsonRequestPacketDeserializer::deserializeAddQuestionRequest(const vector<unsigned char>& buffer)
{
    AddQuestionRequest request;
    json data = getJsonFromBuffer(buffer);
    request.question = data["question"];
    request.correctAnswer = data["correctAnswer"];
    request.incorrectAnswer1 = data["incorrectAnswer1"];
    request.incorrectAnswer2 = data["incorrectAnswer2"];
    request.incorrectAnswer3 = data["incorrectAnswer3"];
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
