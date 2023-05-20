#pragma comment(lib, "urlmon.lib")

#include "json.hpp"
#include <urlmon.h>
#include <sstream>
#include <iostream>
#include <exception>
#include <vector>

using std::string;
using std::cout;
using std::endl;
using nlohmann::json;
using std::exception;
using std::vector;

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
    std::stringstream ss;
    stream->Read(buffer, 100, &bytesRead);
    while (bytesRead > 0U)
    {
        ss.write(buffer, (long long)bytesRead);
        stream->Read(buffer, 100, &bytesRead);
    }
    stream->Release();
    string resultString = ss.str();
    json data;
    std::stringstream(resultString) >> data;
    
    try
    {
        cout << data.dump() << endl << endl << endl;

        for (int i = 0; i < 10; i++)
        {
            for (json::iterator it = data["results"][i].begin(); it != data["results"][i].end(); ++it)
            {
                if (it.key() == "category")
                {
                    cout << it.key() << " : " << it.value() << "\n";
                }

                if (it.key() == "type")
                {
                    cout << it.key() << " : " << it.value() << "\n";
                }

                if (it.key() == "difficulty")
                {
                    cout << it.key() << " : " << it.value() << "\n";
                }

                if (it.key() == "question")
                {
                    cout << it.key() << " : " << it.value() << "\n";
                }

                if (it.key() == "correct_answer")
                {
                    cout << it.key() << " : " << it.value() << "\n";
                }

                if (it.key() == "incorrect_answers")
                {
                    cout << it.key() << " : " << it.value() << "\n";
                }
            }

            cout << endl;
        }
    }
    catch (exception& e)
    {
        cout << "Error has occurred: " << e.what() << endl;
    }

    return 0;
}