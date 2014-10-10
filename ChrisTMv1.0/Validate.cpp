/*
    Module: Validate
    File: Validate.cpp
    Application: TuringMachineApplication
    Language: C++
    Computer: Macbook Air
    Operating System: Ubuntu 14.10
    Course: CptS 322
    Author: Christopher Wilkins
    Date: 5/5/2014
    Description:
    Validate.cpp contains the code implementation for Validate methods.
    The Validate file contains methods that are used by the Turing Machine
    Application to verify whether or not input strings are valid.
*/
#include "Validate.h"

#include <string>

using namespace std;

/*
    The Validate method is an overloaded method that checks to see whether a given
    character called value contains a value that is a reserved character. This method
    returns true as a boolean if the character is not a reserved character. It returns
    false as a boolean if it is a reserved character.
*/
bool Validate(char value)
{
    return
       ((value != '\\')  &&
        (value != '[')   && (value != ']') &&
        (value != '<')   && (value != '>'));
        //        (value >= '!')   && (value <= '~')
}

/*
    The Validate method is an overloaded method that checks to see whether a given string
    called value contains any characters that are reserved characters. This method returns
    true as a boolean if the string does not contain any reserved characters. It returns false
    as a boolean if it contains any reserved characters.
*/
bool Validate(string value)
{
    for (unsigned int i=0; i < value.length(); i++)
    {
        if (!Validate(value[i]))
            return false;
    }
    return true;
}
