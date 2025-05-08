#include <iostream>
#include "../Logger.h"
#include "headers/DSResultsScraper.h"

using json = nlohmann::json;
using namespace std;

int main(int argc, char* argv[])
{
    vector<string> arg(argv, argv + argc);
    if (arg.size() < 2) {
		DSResultsScraper::printHelp();
        return 0;
    }
    try {
        DSResultsScraper dsScraper(arg[1], arg[2]);
        dsScraper.run();
    }
    catch(exception e) {
        DSResultsScraper::printHelp();
        return 0;
    }

    return 0;
}
