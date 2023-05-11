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
    vector<unsigned char> codeRequestByte;
    codeRequestByte.push_back(requestInfo.buffer[0]);
    int codeRequest = JsonRequestPacketDeserializer::convertByteToNumber(codeRequestByte);
	return (codeRequest == LOGIN_REQUEST || codeRequest == SIGNUP_REQUEST);
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

    vector<unsigned char> codeRequestByte;
    codeRequestByte.push_back(requestInfo.buffer[0]);
    int codeRequest = JsonRequestPacketDeserializer::convertByteToNumber(codeRequestByte);

    if (codeRequest == LOGIN_REQUEST)
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