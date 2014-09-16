/*
    Module: States
    File: States.h
    Application: TuringMachineApplication
    Language: C++
    Computer: Macbook Air
    Operating System: Ubuntu 14.10
    Course: CptS 322
    Author: Christopher Wilkins
    Date: 5/5/2014
    Description:
    Sates.h contains the code declaration for the Sates class.
    The states of a turing machine consists of all possible states that the Turing machine
    can be in. The states are represented by a string that is the state's name. The States
    class stores all of the states as strings and allows a specific state to be referenced
    by an integer index.
*/
#ifndef STATES_H
#define STATES_H

#include <fstream>
#include <string>
#include <vector>

using namespace std;

class States
{
    private:
    vector<string> states;

    public:
    void Load(fstream& definitionFile, bool& valid);
    void View() const;
    bool IsElement(string value) const;
};

#endif // STATES_H
