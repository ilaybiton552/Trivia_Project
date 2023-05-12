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
    return signupRequest;
}

/// <summary>
/// the function converts bytes to integer
/// </summary>
/// <param name="buffer">the bytes to convert</param>
/// <returns>the converted bytes as number</returns>
unsigned int JsonRequestPacketDeserializer::convertByteToNumber(const vector<unsigned char>& buffer)
{
    int num = 0;

    for (int i = 0; i < MAX_BYTES_UNSIGNED_INT; i++) // from bytes to int
    {
        num = (num << NUM_OF_BITS_IN_BYTE) + buffer[i];
    }

    return num;
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
