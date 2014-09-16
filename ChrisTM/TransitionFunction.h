/*
    Module: TransitionFunction
    File: TransitionFunction.h
    Application: TuringMachineApplication
    Language: C++
    Computer: Macbook Air
    Operating System: Ubuntu 14.10
    Course: CptS 322
    Author: Christopher Wilkins
    Date: 5/5/2014
    Description:
    TransitionFunction.h contains the code declaration for the TransitionFunction class.
    The transition function describes all possible transitions of the Turing machine.
    It is used by the Turing Machine to get information about a particular transition,
    as well as to check to see if a transition is valid. The TransitionFunction manages
    the transitions in the program and reads the TRANSITION_FUNCTION section of the Turing
    Machine definition file. It verifies that this portion of the file is valid.
*/
#ifndef TRANSITIONFUNCTION_H
#define TRANSITIONFUNCTION_H

#include "Direction.h"
#include "Transition.h"
#include <string>
#include <fstream>
#include <vector>

using namespace std;

class TransitionFunction
{
    private:
    vector<Transition> transitions;

    public:
    void Load(fstream& defininitionFile, bool& valid);
    void View() const;
    int Size() const;
    string SourceState(int index) const;
    char ReadCharacter(int index) const;
    string DestinationState(int index) const;
    char WriteCharacter(int index) const;
    Direction MoveDirection(int index) const;
    bool IsDefinedTransition(string source, char readCharacter,
                             string& destination, char& writeCharacter,
                             Direction& moveDirection) const;
    bool IsSourceState(string state) const;
};

#endif // TRANSITIONFUNCTION_H
