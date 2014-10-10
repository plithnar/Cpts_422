/*
    Module: Transition
    File: Transition.h
    Application: TuringMachineApplication
    Language: C++
    Computer: Macbook Air
    Operating System: Ubuntu 14.10
    Course: CptS 322
    Author: Christopher Wilkins
    Date: 5/5/2014
    Description:
    Transition.cpp contains the code declaration for the Transition class.
    A transition defines one possible transition that the turing machine can
    perform. A transition consists of a source state that the Turing machine
    must be in the perform the transition, a read character that must be on
    the tape at the position of the tape head for the transition to be performed,
    a write character that is written to the tape at the position of the tape head
    when the transition is performed, direction (either left or right) to move the
    tape head, and a destination state that the Turing machine will enter once the
    transition has been performed.
*/
#ifndef TRANSITION_H
#define TRANSITION_H

#include "Direction.h"
#include <string>

using namespace std;

class Transition
{
    private:
    string source;
    char read;
    string destination;
    char write;
    Direction direction;

    public:
    Transition(string sourceState, char readCharacter, string destinationState, char writeCharacter, Direction moveDirection);
    string SourceState() const;
    char ReadCharacter() const;
    string DestinationState() const;
    char WriteCharacter() const;
    Direction MoveDirection() const;
};

#endif // TRANSITION_H
