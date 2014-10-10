/*
    Module: States
    File: States.cpp
    Application: TuringMachineApplication
    Language: C++
    Computer: Macbook Air
    Operating System: Ubuntu 14.10
    Course: CptS 322
    Author: Christopher Wilkins
    Date: 5/5/2014
    Description:
    Sates.cpp contains the code implementation for the Sates class.
    The states of a turing machine consists of all possible states that the Turing machine
    can be in. The states are represented by a string that is the state's name. The States
    class stores all of the states as strings and allows a specific state to be referenced
    by an integer index.
*/
#include "States.h"
#include "UpperCase.h"
#include "Validate.h"

#include <sstream>
#include <fstream>
#include <iostream>

using namespace std;

/*
    The method load reads a series of strings from the Turing machine definition file. Each string
    is separated by any number of white space characters. Each string becomes an element of the states
    string vector. If any of the strings consist of a single character that is reserved or not printable,
    or the next keyword does not follow in the file, an error message is displayed and valid is set to false.
*/
void States::Load(fstream& definitionFile, bool& valid)
{
    const string nextToken = "INPUT_ALPHABET:";
    stringstream readAlpha;
    string temp("");
    while (definitionFile >> temp)
    {
        if (ToUpper(temp) == nextToken)
        {
            if (states.size() < 1)
            {
                cout << "Empty state section in definition file" << endl;
                valid = false;
            }
            return;
        }
        if (IsElement(temp))
        {
            cout << "Duplicate state found." << endl;
            valid = false;
        }
        if (!Valid(temp))
        {
            cout << "Invalid state found " << temp << endl;
            valid = false;
        }
        states.push_back(temp);
    }
    if (ToUpper(temp) != nextToken)
    {
        cout << nextToken << " not found after states." << endl;
        valid = false;
    }
}

/*
    The View method prints the state names to the screen. It prints out each element of the states character
    vector with each string separated by a comma and a space.
*/
void States::View() const
{
    cout << "Gamma: { ";
    for (unsigned int i=0; i<states.size(); i++)
    {
        cout << states[i] << " ";
    }
    cout << "}" << endl << endl;
}

/*
    The IsElement method accepts a string value and looks to see if the string is an element of the states
    string vector. If the value is in the states string vector, the method returns true. Otherwise, the
    method returns false.
*/
bool States::IsElement(string value) const
{
    for (unsigned int i = 0; i < states.size(); i++)
    {
        if (states[i] == value)
            return true;
    }
    return false;
}
