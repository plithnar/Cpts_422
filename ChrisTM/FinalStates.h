/*
    Module: FinalSates
    File: FinalStates.h
    Application: TuringMachineApplication
    Language: C++
    Computer: Macbook Air
    Operating System: Ubuntu 14.10
    Course: CptS 322
    Author: Christopher Wilkins
    Date: 5/5/2014
    Description:
    FinalStates.h contains the code declaration for the FinalStates class.
    The final states of a turing machine consists of all possible halt states
    of the Turing machine. These are states that the Turing machine can enter
    but not leave. The states are represented by a string that is the state's name.
    The States class stores all of the states as strings and allows a specific
    state to be referenced by an integer index.
*/
#ifndef FINALSTATES_H
#define FINALSTATES_H

#include <fstream>
#include <string>
#include <vector>

using namespace std;

class FinalStates
{
    private:
    vector<string> states;

    public:
    void Load(fstream& definitionFile, bool& valid);
    void View() const;
    int Size() const;
    string Element(int index) const;
    bool IsElement(string value) const;
};

#endif // FINALSTATES_H
