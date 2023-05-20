#pragma comment(lib, "urlmon.lib")

#include <urlmon.h>
#include <sstream>
#include <iostream>

using namespace std;

int main()
{

    IStream* stream;
    //Also works with https URL's - unsure about the extent of SSL support though.
    HRESULT result = URLOpenBlockingStream(0, L"https://opentdb.com/api.php?amount=10&type=multiple", &stream, 0, 0);
    if (result != 0)
    {
        return 1;
    }
    char buffer[100];
    unsigned long bytesRead;
    stringstream ss;
    stream->Read(buffer, 100, &bytesRead);
    while (bytesRead > 0U)
    {
        ss.write(buffer, (long long)bytesRead);
        stream->Read(buffer, 100, &bytesRead);
    }
    stream->Release();
    string resultString = ss.str();

    cout << resultString << endl;

    return 0;
}