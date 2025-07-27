#include "controller/controller.h"

int main(int argc, char **argv)
{
    try
    {
        Controller controller;
        controller.init(argc, argv);
        controller.run();
    }
    catch (const std::exception &e)
    {
        std::cerr << "Fatal error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
