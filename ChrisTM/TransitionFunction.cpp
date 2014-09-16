/*
    Module: TransitionFunction
    File: TransitionFunction.cpp
    Application: TuringMachineApplication
    Language: C++
    Computer: Macbook Air
    Operating System: Ubuntu 14.10
    Course: CptS 322
    Author: Christopher Wilkins
    Date: 5/5/2014
    Description:
    TransitionFunction.cpp contains the code implementation for the TransitionFunction class.
    The transition function describes all possible transitions of the Turing machine.
    It is used by the Turing Machine to get information about a particular transition,
    as well as to check to see if a transition is valid. The TransitionFunction manages
    the transitions in the program and reads the TRANSITION_FUNCTION section of the Turing
    Machine definition file. It verifies that this portion of the file is valid.
*/
#include "TransitionFunction.h"
#include "Crash.h"
#include "Validate.h"
#include "Transition.h"
#include "Direction.h"
#include "UpperCase.h"
#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <sstream>

using namespace std;

/*
    The method load reads a series of strings from the Turing machine definition file. Each string
    represents the definition for one entire transition of the Turing machine. The format of the
    each transition is:
	source_state	read_character	destination_state	write_character 	tape_direction
    Each part of the transition is separated by white space. If the transition is not in this format,
    then valid will be set to false and the method will exit. If the transition is in a valid format,
    then a new Transition object will be created using the transition data as its parameters, and it
    will be added to the transitions transition vector.
*/
void TransitionFunction::Load(fstream& definitionFile, bool& valid)
{
    string nextToken = "INITIAL_STATE:";
    stringstream readAlpha;
    int part = 0;
    string temp("");
    string source, dest;
    char r, w;
    Direction mv;
    while (definitionFile >> temp)
    {
        int currPart = part % 5;
        if (ToUpper(temp) == nextToken)
        {
            if (currPart != 0)
            {
                cout << "Incomplete transition." << endl;
                valid = false;
            }
            if (transitions.size() < 1)
            {
                cout << "Empty transition function." << endl;
                valid = false;
            }
            return;
        }
        if (currPart == 0)
        {
            if (Validate(dest))
                source = temp;
            else
                cout << "Destination state name contains reserved characters." << endl;
        }
        else if (currPart == 1)
        {
            char readChar = 0;
            readAlpha << temp;
            readAlpha >> readChar;
            if (readChar == 0 || !Validate(readChar))
            {
                valid = false;
                cout << "Invalid read character (" << readChar << ") in transition." << endl;
                return;
            }
            else
            {
                r = readChar;
            }
        }
        else if (currPart == 2)
        {
            if (Validate(dest))
                dest = temp;
            else
                cout << "Destination state name contains reserved characters." << endl;
        }
        else if (currPart == 3)
        {
            char readChar = 0;
            readAlpha << temp;
            readAlpha >> readChar;
            if (readChar == 0 || !Validate(readChar))
            {
                valid = false;
                cout << "Invalid write character (" << readChar << ") in transition." << endl;
                return;
            }
            else
            {
                w = readChar;
            }
        }
        else if (currPart == 4)
        {
            try
            {
                mv = ReadDirection(temp);
            }
            catch (Crash c)
            {
                cout << c.what() << " in transition." << endl;
                valid = false;
            }
            transitions.push_back(Transition(source, r, dest, w, mv));
        }
        part++;
    }
    if (ToUpper(temp) != nextToken)
    {
        cout << nextToken << " not found after states." << endl;
        valid = false;
    }
}

/*
    The View method displays the transition function in its entirety. It displays the transtition function
    as close to the theoretical formal definition of a turing machine as possible.
*/
void TransitionFunction::View() const
{
    for (unsigned int i=0; i<transitions.size(); i++)
    {
//        cout << "Delta(s0, a) = (s1, X, R)" << endl;
        cout << "Delta(" << transitions[i].SourceState() << ", " <<
                transitions[i].ReadCharacter() << ") = (" << transitions[i].DestinationState() <<
                ", " << transitions[i].WriteCharacter() << ", " <<
                PrintDirection(transitions[i].MoveDirection()) << ")" << endl;
    }
    cout << endl;
}

/*
    The size method returns as an integer the number of transitions in the transition functions
    transtitions Transition vector.
*/
int TransitionFunction::Size() const
{
    return transitions.size();
}

/*
    The SourceState method is a getter method that returns the source state as a string of a transition
    at a given index in the transitions transition vector.
*/
string TransitionFunction::SourceState(int index) const
{
    return transitions[index].SourceState();
}

/*
    The ReadCharacter method is a getter method that returns the read character as a character of a transition
    at a given index in the transitions transition vector.
*/
char TransitionFunction::ReadCharacter(int index) const
{
    return transitions[index].ReadCharacter();
}

/*
    The DestinationState method is a getter method that returns the destination state as a string of a transition
    at a given index in the transitions transition vector.
*/
string TransitionFunction::DestinationState(int index) const
{
    return transitions[index].DestinationState();
}

/*
    The WriteCharacter method is a getter method that returns the write character as a character of a transition
    at a given index in the transitions transition vector.
*/
char TransitionFunction::WriteCharacter(int index) const
{
    return transitions[index].WriteCharacter();
}

/*
    The MoveDirection method is a getter method that returns the move direction as a Direction enumeration value of a
    transition at a given index in the transitions transition vector. It returns a value of either LEFT or RIGHT.
*/
Direction TransitionFunction::MoveDirection(int index) const
{
    return transitions[index].MoveDirection();
}

/*
    The IsValidTransition checks a source state given by the source parameter and a read character given the read
    character and checkds to see if there is a valid transition corresponding to the state and character. If there
    is, the method fills in the write character, destination state, and move direction with the correct values from
    the transition function. It also returns true. Otherwise, it does not fill in these values and returns false as
    a boolean.
*/
bool TransitionFunction::IsDefinedTransition(string source, char read,
                                             string& destination, char& write,
                                             Direction& move) const
{
    for(unsigned int i = 0; i < transitions.size(); i++)
    {
        if((transitions[i].SourceState() == source) && (transitions[i].ReadCharacter() == read))
        {
            destination = transitions[i].DestinationState();
            write = transitions[i].WriteCharacter();
            move = transitions[i].MoveDirection();
            return true;
        }
    }
    return false;
}

/*
    The IsSourceState method checks to see if a state name given by the state parameter is in the transition
    function as a sourceState value in one of the transitions. If it is, the method returns true as a boolean.
    Otherwise, the method returns false.
*/
bool TransitionFunction::IsSourceState(string state) const
{
    for (unsigned int i=0; i < transitions.size(); i++)
    {
        if (transitions[i].SourceState() == state)
            return true;
    }
    return false;
}
