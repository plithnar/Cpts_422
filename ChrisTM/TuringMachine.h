/*
    Module: TuringMachine
    File: TuringMachine.h
    Application: TuringMachineApplication
    Language: C++
    Computer: Macbook Air
    Operating System: Ubuntu 14.10
    Course: CptS 322
    Author: Christopher Wilkins
    Date: 5/5/2014
    Description:
    TuringMachine.h contains the code declaration for the TuringMachine class.
    The TuringMachine class manages the operation of the Turing Machine in
    the turing machine application. It keeps track of whether or not the turing
    machine has operated on an input string, the number of transitions performed
    by the turing machine, the current state that the turing machine is in, the
    initial state that the turing machine starts in, and whether or not the current
    input string has been accepted or rejected. It is responsible for creating the
    definition file object that is passed to each part of the application. It also
    keeps track of whether or not the turing machine specified by the definition is
    valid. This class contains all of the methods that are necessary to view the turing
    machine, show its status, and run transitions on an input string.
*/
#ifndef TURINGMACHINE_H
#define TURINGMACHINE_H

#include <vector>
#include <string>
#include <fstream>

#include "Tape.h"
#include "InputAlphabet.h"
#include "TapeAlphabet.h"
#include "TransitionFunction.h"
#include "States.h"
#include "FinalStates.h"

using namespace std;

class TuringMachine
{
    private:
    Tape tape;
    TransitionFunction transitionFunction;
    TapeAlphabet tapeAlphabet;
    InputAlphabet inputAlphabet;
    States states;
    FinalStates finalStates;

    vector<string> description;
    string initialState;
    string currentState;
    string originalInputString;
    int numberOfTransitions;
    bool valid;
    bool used;
    bool operating;
    bool accepted;
    bool rejected;

    public:
    TuringMachine(string definitionFileName);
    void ViewDefinition() const;
    void ViewInstantaneousDescription(int maximumNumberOfCells) const;
    void Initialize(string inputString);
    void PerformTransitions(int maximumTransitions);
    void TerminateOperation();
    string InputString() const;
    int TotalNumberOfTransitions() const;
    bool IsValidInputString(string inputString) const;
    bool IsUsed() const;
    bool IsOperating() const;
    bool IsAcceptedInputString() const;
    bool IsRejectedInputString() const;
    bool IsValid() const;
};

#endif // TURINGMACHINE_H
