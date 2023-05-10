#include "JsonRequestPacketDeserializer.h"

LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequst(vector<unsigned char> buffer)
{

}

SignupRequest JsonRequestPacketDeserializer::deserializeSignupRequst(vector<unsigned char> buffer)
{

}

/// <summary>
/// the function converts bytes to integer
/// </summary>
/// <param name="buffer">the bytes to convert</param>
/// <returns>the converted bytes as number</returns>
unsigned int JsonRequestPacketDeserializer::convertByteToNumber(vector<unsigned char> buffer)
{
    int num = 0;

    for (int i = 0; i < MAX_BYTES_UNSIGNED_INT; i++) // from bytes to int
    {
        num = (num << NUM_OF_BITS_IN_BYTE) + buffer[i];
    }

    return num;
}