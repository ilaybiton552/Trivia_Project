#include "LoginRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"

/// <summary>
/// Checks if the request is relevant
/// </summary>
/// <param name="requestInfo">RequestInfo, the information of the request</param>
/// <returns>bool, if the request is relevant to the handler</returns>
bool LoginRequestHandler::isRequestRelevant(const RequestInfo& requestInfo)
{
    vector<unsigned char> codeRequestByte;
    codeRequestByte.push_back(requestInfo.buffer[0]);
    int codeRequest = convertByteToNumber(codeRequestByte);
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
    int codeRequest = convertByteToNumber(codeRequestByte);

    if (codeRequest == LOGIN_REQUEST)
    {
        LoginRequest loginRequest = JsonRequestPacketDeserializer::deserializeLoginRequest(requestInfo.buffer);
        // success in login (for now)
    }
    else // signup request
    {
        SignupRequest signRequest = JsonRequestPacketDeserializer::deserializeSignupRequest(requestInfo.buffer);
        // success in signup (for now)
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

    for (int i = 0; i < MAX_BYTES_UNSIGNED_INT; i++) // from bytes to int
    {
        num = (num << NUM_OF_BITS_IN_BYTE) + buffer[i];
    }

    return num;
}