#ifdef _WIN32
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#ifndef NOMINMAX
#define NOMINMAX
#endif
#endif

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "IronCScript.h"

using namespace std;
using namespace cse;

void printUsage(const char* programName) {
    cout << "Usage: " << programName << " <script_file> [platform]" << endl;
    cout << endl;
    cout << "Arguments:" << endl;
    cout << "  script_file   Path to the IronCS script file" << endl;
    cout << "  platform     Target platform (optional, default: x86-64)" << endl;
    cout << endl;
    cout << "Supported platforms: " << IronCScript::supportedPlatforms() << endl;
    cout << endl;
    cout << "Example:" << endl;
    cout << "  " << programName << " scripts/hello.c" << endl;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printUsage(argv[0]);
        return 1;
    }

    string scriptFile = argv[1];
    string platform = "x86-64";
    if (argc > 2) {
        platform = argv[2];
    }

    cout << "IronCScript v" << IronCScript::version() << endl;
    cout << "Platform: " << platform << endl;
    cout << "Script: " << scriptFile << endl;
    cout << endl;

    IronCScript engine;
    engine.setPlatform(platform);

    cout << "Executing script..." << endl;
    if (!engine.executeFile(scriptFile)) {
        cerr << "Error: " << engine.getLastError() << endl;
        return 1;
    }

    cout << endl;
    cout << "Script executed successfully." << endl;
    cout << "Return value: " << engine.getLastReturnValue() << endl;

    return engine.getLastReturnValue();
}