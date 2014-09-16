/*
    Module: Uppercase
    File: Uppercase.h
    Application: TuringMachineApplication
    Language: C++
    Computer: Macbook Air
    Operating System: Ubuntu 14.10
    Course: CptS 322
    Author: Christopher Wilkins
    Date: 5/5/2014
    Description:
    Uppercase.h contains the code declaration for Uppercase methods.
    The Uppercase module contains a method that is used by the Turing Machine
    application to convert strings to uppercase. The purpose of this is to get
    strings to the same case so they can be compared without being restricted by
    case sensitivity.
*/
#ifndef UPPERCASE_INCLUDED
#define UPPERCASE_INCLUDED

#include <string>

std::string ToUpper(std::string value);

#endif // UPPERCASE_INCLUDED
