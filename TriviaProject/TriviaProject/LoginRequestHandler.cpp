#include "LoginRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"

/// <summary>
/// Checks if the request is relevant
/// </summary>
/// <param name="requestInfo">RequestInfo, the information of the request</param>
/// <returns>bool, if the request is relevant to the handler</returns>
bool LoginRequestHandler::isRequestRelevant(const RequestInfo& requestInfo)
{
	return (requestInfo.id == LOGIN_REQUEST || requestInfo.id == SIGNUP_REQUEST);
}

/// <summary>
/// Handles with the request
/// </summary>
/// <param name="requestInfo">RequsetInfo, the info of the request</param>
/// <returns>RequestResult, the result of the server for the reqeust</returns>
RequestResult LoginRequestHandler::handleRequest(const RequestInfo& requestInfo)
{
    RequestResult requestResult;
    requestResult.newHandler = nullptr; // currently nothing

    if (requestInfo.id == LOGIN_REQUEST)
    {
        LoginRequest loginRequest = JsonRequestPacketDeserializer::deserializeLoginRequest(requestInfo.buffer);
        // success in login (for now)
        LoginResponse loginResponse = { SUCCESS_LOGIN_SIGNUP };
        requestResult.response = JsonResponsePacketSerializer::serializeResponse(loginResponse);
    }
    else // signup request
    {
        SignupRequest signRequest = JsonRequestPacketDeserializer::deserializeSignupRequest(requestInfo.buffer);
        // success in signup (for now)
        SignupResponse signupResponse = { SUCCESS_LOGIN_SIGNUP };
        requestResult.response = JsonResponsePacketSerializer::serializeResponse(signupResponse);
    }

	return requestResult;
}

/// <summary>
/// the function converts bytes to integer
/// </summary>
/// <param name="buffer">the bytes to convert</param>
/// <returns>the converted bytes as number</returns>
unsigned int LoginRequestHandler::convertByteToNumber(const vector<unsigned char>& buffer)
{
    int num = 0;

    for (int i = 0; i < buffer.size(); i++) // from bytes to int
    {
        num = (num << NUM_OF_BITS_IN_BYTE) + buffer[i];
    }

    return num;
}