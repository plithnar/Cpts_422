/*
    Module: Crash
    File: Crash.h
    Application: TuringMachineApplication
    Language: C++
    Computer: Macbook Air
    Operating System: Ubuntu 14.10
    Course: CptS 322
    Author: Christopher Wilkins
    Date: 5/5/2014
    Description:
    Crash.h contains the code declaration for Crash module.
    The Crash class is an exception class that carries information
    about a crash of the turing machine.
*/
#ifndef CRASH_H_INCLUDED
#define CRASH_H_INCLUDED

#include <stdexcept>

using namespace std;

class Crash: public runtime_error
{
    public:
    Crash(string reason);
};

#endif // CRASH_H_INCLUDED
