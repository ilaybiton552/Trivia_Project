#include "JsonResponsePacketSerializer.h"

/// <summary>
/// Serializes an error response
/// </summary>
/// <param name="errorResponse">struct ErrorResponse, the response to serialize</param>
/// <returns>vector of bytes, the serialized response</returns>
vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(ErrorResponse errorResponse)
{
    vector<unsigned char> buffer; // buffer as the protocol structure
    vector<unsigned char> data; // the data of the message
    vector<unsigned char> dataSize; // the size of the data

    buffer.push_back(convertNumberToByte(ERROR_RESPONSE_CODE)[FIRST_BYTE_INDEX]);
    json response = { {"message", errorResponse.message} };
    data = convertJsonToByte(response);
    dataSize = convertNumberToByte(data.size());
    buffer.insert(buffer.end(), dataSize.begin(), dataSize.end());
    buffer.insert(buffer.end(), data.begin(), data.end());

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
