/*
    Module: FinalSates
    File: FinalStates.cpp
    Application: TuringMachineApplication
    Language: C++
    Computer: Macbook Air
    Operating System: Ubuntu 14.10
    Course: CptS 322
    Author: Christopher Wilkins
    Date: 5/5/2014
    Description:
    FinalStates.cpp contains the code implementation for the FinalStates class.
    The final states of a turing machine consists of all possible halt states
    of the Turing machine. These are states that the Turing machine can enter
    but not leave. The states are represented by a string that is the state's name.
    The States class stores all of the states as strings and allows a specific
    state to be referenced by an integer index.
*/
#include "FinalStates.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

/*
    The method load reads a series of strings from the Turing machine definition
    file. Each string is separated by any number of white space characters. Each
    string becomes an element of the states string vector. If any of the strings
    consist of a single character that is reserved or not printable, or the next
    keyword does not follow in the file, an error message is displayed and valid
    is set to false.
*/
void FinalStates::Load(fstream& definitionFile, bool& valid)
{
    stringstream readAlpha;
    string temp("");
    while (definitionFile >> temp)
    {
        if (IsElement(temp))
        {
            cout << "Duplicate final state found." << endl;
            valid = false;
            return;
        }
        states.push_back(temp);
    }
}

/*
    The View method prints the final state names to the screen. It prints out each
    element of the states character vector with each string separated by a comma and
    a space.
*/
void FinalStates::View() const
{
    cout << "F = { ";
    for (unsigned int i=0; i<states.size(); i++)
    {
        cout << states[i] << " ";
    }
    cout << "}" << endl << endl;
}

/*
    The Size method returns the number of state names that are in the states string vector
    as an integer. The number indicates the total number of final states that are part of
    the Turing machine definition.
*/
int FinalStates::Size() const
{
    return states.size();
}

/*
    The Element method returns the final state name at a given index as a string in the
    alphabet character vector. If the index is less than zero or greater than the size of
    the states string vector, it throws an exception and exits. Otherwise, it returns the
    character at the given index in the states string vector.
*/
string FinalStates::Element(int index) const
{
    // std::vector will throw an out of range exception if index is out of range.
    return states[index];
}

/*
    The IsElement method accepts a string value and looks to see if the string is an element
    of the states string vector. If the value is in the states string vector, the method returns
    true. Otherwise, the method returns false.
*/
bool FinalStates::IsElement(string value) const
{
    for (unsigned int i = 0; i < states.size(); i++)
    {
        if (states[i] == value)
            return true;
    }
    return false;
}
