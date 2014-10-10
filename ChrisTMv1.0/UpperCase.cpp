/*
    Module: Uppercase
    File: Uppercase.cpp
    Application: TuringMachineApplication
    Language: C++
    Computer: Macbook Air
    Operating System: Ubuntu 14.10
    Course: CptS 322
    Author: Christopher Wilkins
    Date: 5/5/2014
    Description:
    Uppercase.cpp contains the code implementation for Uppercase methods.
    The Uppercase module contains a method that is used by the Turing Machine
    application to convert strings to uppercase. The purpose of this is to get
    strings to the same case so they can be compared without being restricted by
    case sensitivity.
*/
#include "UpperCase.h"
#include <algorithm>
#include <string>

using namespace std;

/*
    The ToUpper method accepts a string called value and converts each character
    in the string to uppercase. The method returns the same string with every
    character uppercase as a string.
*/
string ToUpper(string value)
{
    transform(value.begin(), value.end(), value.begin(), ::toupper);
    return value;
}
