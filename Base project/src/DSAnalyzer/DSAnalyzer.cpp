// DSAnalyzer.cpp : Defines the entry point for the application.
//
#include <iostream>
#include <iomanip> // For std::setw
#include <locale>  // For std::locale
#include <codecvt> // For std::codecvt_utf8 (if needed on older compilers)

#ifdef _WIN32
#include <windows.h>
#endif

#include "headers/DSConsoleUI.h"

#include "../Logger.h"

using namespace std;



int main(int argc, char** argv)
{
    Logger::Init();
    //AnalyzerCore ac;
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif
    vector<string> arg(argv, argv + argc);
    

	DSConsoleUi ds;
	ds.run(arg);
}


