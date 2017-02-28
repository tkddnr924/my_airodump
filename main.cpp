#include <iostream>
#include <capture.h>

using namespace std;

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        printf("%s <interface>\n", argv[0]);
        return 0;
    }

    Capture* capture = new Capture(argv[1]);
    capture->Start();

    return 0;
}
