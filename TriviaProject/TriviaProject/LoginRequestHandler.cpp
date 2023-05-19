#include "LoginRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"

/// <summary>
/// Constructor of LoginRequestHandler
/// </summary>
/// <param name="handlerFactory">reference of RequestHandlerFactory, the handler factory</param>
LoginRequestHandler::LoginRequestHandler(RequestHandlerFactory& handlerFactory) : m_handlerFactory(handlerFactory)
{
}

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
    if (requestInfo.id == LOGIN_REQUEST)
    {
        return login(requestInfo);
    }
    return signup(requestInfo);
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

/// <summary>
/// Handles with login request
/// </summary>
/// <param name="requestInfo">reference of RequestInfo, the information of the request</param>
/// <returns>ReqeustResult, the result of the server for the request</returns>
RequestResult LoginRequestHandler::login(const RequestInfo& requestInfo)
{
    RequestResult requestResult;

    requestResult.newHandler = nullptr;
    LoginRequest loginRequest = JsonRequestPacketDeserializer::deserializeLoginRequest(requestInfo.buffer);
    LoginResponse loginResponse = { m_handlerFactory.getLoginManager().login(loginRequest.username, loginRequest.password) };
    requestResult.response = JsonResponsePacketSerializer::serializeResponse(loginResponse);
    if (loginResponse.status == SUCCESS_CODE)
    {
        requestResult.newHandler = m_handlerFactory.createMenuRequestHandler();
    }

    return requestResult;
}

/// <summary>
/// Handles with sign request
/// </summary>
/// <param name="requestInfo">reference of RequestInfo, the information of the request</param>
/// <returns>ReqeustResult, the result of the server for the request</returns>
RequestResult LoginRequestHandler::signup(const RequestInfo& requestInfo)
{
    RequestResult requestResult;

    requestResult.newHandler = nullptr;
    SignupRequest signupRequest = JsonRequestPacketDeserializer::deserializeSignupRequest(requestInfo.buffer);
    SignupResponse signupResponse = { m_handlerFactory.getLoginManager().signup(signupRequest.username, signupRequest.password, signupRequest.email, signupRequest.address, signupRequest.phoneNumber, signupRequest.birthDate)};
    requestResult.response = JsonResponsePacketSerializer::serializeResponse(signupResponse);
    if (signupResponse.status == SUCCESS_CODE)
    {
        requestResult.newHandler = m_handlerFactory.createMenuRequestHandler();
    }

    return requestResult;
}
