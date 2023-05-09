#include "JsonResponsePacketSerializer.h"

/// <summary>
/// Serializes an error response
/// </summary>
/// <param name="errorResponse">struct ErrorResponse, the response to serialize</param>
/// <returns>vector of bytes, the serialized response</returns>
vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(ErrorResponse errorResponse)
{
    vector<unsigned char> buffer;
    return buffer;
}

/// <summary>
/// Serializes a login response
/// </summary>
/// <param name="loginResponse">struct LoginResponse, the response to serialize</param>
/// <returns>vector of bytes, the serialized response</returns>
vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(LoginResponse loginResponse)
{
    vector<unsigned char> buffer;
    return buffer;
}

/// <summary>
/// Serializes an error response
/// </summary>
/// <param name="signupResponse">struct SignupResponse, the response to serialize</param>
/// <returns>vector of bytes, the serialized response</returns>
vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(SignupResponse signupResponse)
{
    vector<unsigned char> buffer;
    return buffer;
}

/// <summary>
/// Converts a number to a byte
/// </summary>
/// <param name="num">int, the number to convert</param>
/// <returns>unsigned char, the converted number</returns>
unsigned char JsonResponsePacketSerializer::convertNumberToByte(const int num)
{
    return 0;
}
