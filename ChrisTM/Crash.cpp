/*
    Module: Crash
    File: Crash.cpp
    Application: TuringMachineApplication
    Language: C++
    Computer: Macbook Air
    Operating System: Ubuntu 14.10
    Course: CptS 322
    Author: Christopher Wilkins
    Date: 5/5/2014
    Description:
    Crash.cpp contains the code implementation for Crash module.
    The Crash class is an exception class that carries information
    about a crash of the turing machine.
*/
#include "Crash.h"
#include <stdexcept>

using namespace std;

Crash::Crash(string reason):
       runtime_error(reason.c_str())
{
}
