/*
    Module: Validate
    File: Validate.h
    Application: TuringMachineApplication
    Language: C++
    Computer: Macbook Air
    Operating System: Ubuntu 14.10
    Course: CptS 322
    Author: Christopher Wilkins
    Date: 5/5/2014
    Description:
    Validate.h contains the code declaration for Validate methods.
    The Validate file contains methods that are used by the Turing Machine
    Application to verify whether or not input strings are valid.
*/
#ifndef VALIDATE_INCLUDED
#define VALIDATE_INCLUDED

#include <string>

using namespace std;

bool Validate(char value);

bool Validate(string value);

#endif // VALIDATE_INCLUDED
