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
