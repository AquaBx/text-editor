#include "src/Client/Client.h"

int main()
{
    try
    {
        Client myClient(800, 800);
        myClient.run();
        return EXIT_SUCCESS;
    }
    catch (std::exception& e)
    {
        return EXIT_FAILURE;
    }
}

int WinMain(int argc, char** argv)
{
    return main();
}
