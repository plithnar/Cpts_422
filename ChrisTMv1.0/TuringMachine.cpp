/*
    Module: TuringMachine
    File: TuringMachine.cpp
    Application: TuringMachineApplication
    Language: C++
    Computer: Macbook Air
    Operating System: Ubuntu 14.10
    Course: CptS 322
    Author: Christopher Wilkins
    Date: 5/5/2014
    Description:
    TuringMachine.cpp contains the code implementation for the TuringMachine class.
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

#include "TuringMachine.h"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

#include "Tape.h"
#include "InputAlphabet.h"
#include "TapeAlphabet.h"
#include "TransitionFunction.h"
#include "Crash.h"
#include "States.h"
#include "FinalStates.h"
#include "UpperCase.h"

using namespace std;

/*
    The TuringMachine is the constructor for the TuringMachine class.
    It sets all attributes of the TuringMachine class with their intial values.
    It accepts the name of the Turing Machine definition
    file as a string. The constructor creates the Turing Machine definition file
    object. It creates instances of Tape, TapeAlphabet, InputAlphabet, States,
    FinalStates, and TransitionFunction. It passes the turing machine definition
    file object to each of the classes.
*/

TuringMachine::TuringMachine(string definitionFileName):
        initialState(""), currentState(""), originalInputString(""),
        numberOfTransitions(0), valid(true), used(false), accepted(false),
        rejected(false)
{
    fstream definitionFile(definitionFileName.c_str());
    if (!definitionFile.good())
    {
        valid = false;
        cout << "Could not open " << definitionFileName << "." << endl;
        return;
    }
    string input("");
    string statesHeader = "STATES:";
    bool statesFound = false;
    while (getline(definitionFile, input))
    {
        size_t index = ToUpper(input).find("STATES:", 0);
        if (index != string::npos)
        {
            string desc = input.substr(0, index);
            string stat = input.substr(index, input.length() - index);
            definitionFile.seekp((long)definitionFile.tellp()- ((long)(stat.length()+1) - statesHeader.length()));
            statesFound = true;
            break;
        }
        else
        {
            description.push_back(input);
        }
    }
    if (statesFound == false)
    {
        cout << "States is not first header in defintion file." << endl;
        valid = false;
    }

    states.Load(definitionFile, valid);
    inputAlphabet.Load(definitionFile, valid);
    tapeAlphabet.Load(definitionFile, valid);
    for (int i=0; i<inputAlphabet.Size(); i++)
    {
        if (!tapeAlphabet.IsElement(inputAlphabet.Element(i)))
        {
            cout << "Input character " << inputAlphabet.Element(i) << " is not in tape alphabet." << endl;
            valid = false;
        }
    }
    transitionFunction.Load(definitionFile, valid);
    for (int i=0; i<transitionFunction.Size(); i++)
    {
        if (!states.IsElement(transitionFunction.SourceState(i)))
        {
            cout << "Source state " << transitionFunction.SourceState(i) << " is not in states." << endl;
            valid = false;
        }
        if (!tapeAlphabet.IsElement(transitionFunction.ReadCharacter(i)))
        {
            cout << "Read character " << transitionFunction.ReadCharacter(i) << " is not in tape alphabet." << endl;
            valid = false;
        }
        if (!states.IsElement(transitionFunction.DestinationState(i)))
        {
            cout << "Destination state " << transitionFunction.DestinationState(i) << " is not in states." << endl;
            valid = false;
        }
        if (!tapeAlphabet.IsElement(transitionFunction.WriteCharacter(i)))
        {
            cout << "Write character " << transitionFunction.WriteCharacter(i) << " is not in tape alphabet." << endl;
            valid = false;
        }
    }
    definitionFile >> input;
    initialState = input;
    if (!states.IsElement(initialState))
    {
        cout << "Initial state " << initialState << " is not in states." << endl;
        valid = false;
    }
    definitionFile >> input;
    if (input != "BLANK_CHARACTER:")
    {
        cout << "BLANK_CHARACTER: not after initial state." << endl;
        valid = false;
    }
    tape.Load(definitionFile, valid);
    if (!tapeAlphabet.IsElement(tape.BlankCharacter()))
    {
        cout << "Blank character " << tape.BlankCharacter() << " is not in the tape alphabet." << endl;
        valid = false;
    }
    finalStates.Load(definitionFile, valid);
    for (int i=0; i<finalStates.Size(); i++)
    {
        if (!states.IsElement(finalStates.Element(i)))
        {
            cout << "Input character " << finalStates.Element(i) << " is not in tape alphabet." << endl;
            valid = false;
        }
    }
    if (valid == false)
    {
        cout << "Invalid turing machine definition file." << endl << endl;
    }
    else
    {
        cout << "Turing machine successfully loaded." << endl << endl;
    }
}

/*
    The ViewDefinition method displays the turing machine definition.
    This prints the definition onscreen. The definition consists of
    the description, states, final states, initial state, transition
    functions, input alphabet, tape alphabet, and blank character.
*/
void TuringMachine::ViewDefinition() const
{
    for (unsigned int i=0; i < description.size(); i++)
    {
        cout << description[i] << endl;
    }
    states.View();
    inputAlphabet.View();
    tapeAlphabet.View();
    transitionFunction.View();
    cout << "q = " << initialState << endl;
    tape.View();
    finalStates.View();
}

/*
    The ViewInstantaniousDescription method prints the instantaneous description onscreen.
    The instantaneous description consists of the truncated tape, containing the current
    state that the turing machine is in in flat brackets (“[]”) at the location of the tape
    head. It accepts an integer as a parameter that represents the maximum number of cells
    to show on either side of the tape head. If the number of cells to the left is greater
    than maximumNumberOfCells, “<” will be displayed on the left of the instantaneous description.
    Likewise, if the number of cells to the right of the tape head is greater than maximumNumberofCells,
    a “>” will be displayed on the right of the instantaneous description.
*/
void TuringMachine::ViewInstantaneousDescription(int maximumNumberOfCells) const
{
    cout << tape.Left(maximumNumberOfCells) << " [" << currentState << "] " << tape.Right(maximumNumberOfCells) << endl;
}

/*
    The initialize method will prepare the turing machine to run on an input string.
    This includes reseting all attributes to their original values. It accepts a string
    parameter called inputString, the value of which the Initialize method will set the
    initialInputString attribute to.
*/
void TuringMachine::Initialize(string inputString)
{
    tape.Initialize(inputString);
    originalInputString = inputString;
    currentState = initialState;
    numberOfTransitions = 0;
    accepted = false;
    rejected = false;
    operating = false;
}

/*
    The PerformTransitions method will perform transitions on the input string.
    It accepts the maximum number of transitions to be performed as an integer as a parameter.
    It looks at the current state and current character at the position of the tape head
    to determine whether or not there is a valid transition from this state and character.
    If there is then it performs the transition. Otherwise, it prints an error and rejects
    the input string. If there is an attempt to move left from the first cell on the tape head,
    the input string is rejected. The PerformTransitions prints the instantaneous description
    of before and after the transitions were performed.
*/
void TuringMachine::PerformTransitions(int maximumTransitions)
{
    used = true;
    operating = true;
    for (int i=0; i < maximumTransitions; i++)
    {
        bool transitionPerformed = false;
        char current = tape.CurrentCharacter();

        char write = 0;
        string dest = "";
        Direction mv;
        if (finalStates.IsElement(currentState))
        {
            operating = false;
            accepted = true;
            rejected = false;
            return;
        }
        if (transitionFunction.IsDefinedTransition(currentState, current, dest, write, mv))
        {
            try
            {
                tape.Update(write, mv);
                currentState = dest;
            }
            catch (Crash c)
            {
                cout << c.what() << endl;
                operating = false;
                accepted = false;
                rejected = true;
            }
            numberOfTransitions++;
            transitionPerformed = true;
        }
        if (finalStates.IsElement(currentState))
        {
            operating = false;
            accepted = true;
            rejected = false;
            return;
        }
        if (!transitionPerformed)
        {
            operating = false;
            accepted = false;
            rejected = true;
        }
    }
}

/*
    The TerminateOperation will stop operation on an input string if the turing machine
    is currently running on one. It will set the operating attribute to false.
*/
void TuringMachine::TerminateOperation()
{
    operating = false;
}

/*
    The InputString method will return the original input string as a string.
    This method is a getter for the originalInputString parameter.
*/
string TuringMachine::InputString() const
{
    return originalInputString;
}

/*
    The TotalNumberOfTransitions method will return the total number of transitions
    that have run on the current input string as an integer. This is a getter for the
    numberOfTransitions attribute. If the turing machine has never run on an input string
    then it will return 0.
*/
int TuringMachine::TotalNumberOfTransitions() const
{
    return numberOfTransitions;
}

/*
    The IsValidInputString method will check to see if a given input string is valid.
    It accepts an input string as a string. It will check each character of the given input
    string to see if it is in the InputAlphabet class by calling the InputAlphabet class's
    IsElement() method on each character. If every character is an element of the InputAlphabet
    then it will return true. Otherwise, it will return false.
*/
bool TuringMachine::IsValidInputString(string inputString) const
{
    for (unsigned int i=0; i<inputString.length(); i++)
    {
        if (!inputAlphabet.IsElement(inputString[i]))
            return false;
    }
    return true;
}

/*
    The IsUsed method will return whether or not that turing machine has been used as a boolean.
    This method is a getter for the used attribute.
*/
bool TuringMachine::IsUsed() const
{
    return used;
}

/*
    The IsUsed method will return whether or not that turing machine is currently operating on an input
    string. This method is a getter for the operating attribute.
*/
bool TuringMachine::IsOperating() const
{
    return operating;
}

/*
    The IsAcceptedInputString method will return whether or not that turing machine has accepted the current
    input string. This method is a getter for the accepted attribute.
*/
bool TuringMachine::IsAcceptedInputString() const
{
    return accepted;
}


/*
    The IsRejectedInputString method will return whether or not that turing machine has rejected the current
    input string. This method is a getter for the rejected attribute.
*/
bool TuringMachine::IsRejectedInputString() const
{
    return rejected;
}

/*
    The IsValid method will return as a boolean whether or not the turing machine has evaluated the turing
    machine definition file as being valid. This method acts a getter for the “valid” boolean attribute.
*/
bool TuringMachine::IsValid() const
{
    return valid;
}
