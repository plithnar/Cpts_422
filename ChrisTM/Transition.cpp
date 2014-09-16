/*
    Module: Transition
    File: Transition.cpp
    Application: TuringMachineApplication
    Language: C++
    Computer: Macbook Air
    Operating System: Ubuntu 14.10
    Course: CptS 322
    Author: Christopher Wilkins
    Date: 5/5/2014
    Description:
    Transition.cpp contains the code implementation for the Transition class.
    A transition defines one possible transition that the turing machine can
    perform. A transition consists of a source state that the Turing machine
    must be in the perform the transition, a read character that must be on
    the tape at the position of the tape head for the transition to be performed,
    a write character that is written to the tape at the position of the tape head
    when the transition is performed, direction (either left or right) to move the
    tape head, and a destination state that the Turing machine will enter once the
    transition has been performed.
*/
#include "Transition.h"

/*
    The Transition method is the constructor of the Transition class. It initializes
    all of the values of the attributes of the class. The sourceState parameter is the
    value that is assigned to the source attribute. The readCharacter parameter is the
    value that is assigned to the read attribute. The destinationState parameter is the
    value that is assigned to the destinationState attribute. The writeCharacter parameter
    is the value that is assigned to the write attribute. The destinationState parameter is
    the value that is assigned to the destination attribute.
*/
Transition::Transition(string sourceState, char readCharacter, string destinationState, char writeCharacter, Direction moveDirection):
                       source(sourceState), read(readCharacter), destination(destinationState),
                       write(writeCharacter), direction(moveDirection)
{
}

/*
    The SourceState method is a getter method that returns the source state of the transition
    as a string. It returns the value of the source attribute.
*/
string Transition::SourceState() const
{
    return source;
}

/*
    The ReadCharacter method is a getter method that returns the read character of the transition
    as a character. It returns the value of the read attribute.
*/
char Transition::ReadCharacter() const
{
    return read;
}

/*
    The DestinationState method is a getter method that returns the destination state of the
    transition as a string. It returns the value of the destination attribute.
*/
string Transition::DestinationState() const
{
    return destination;
}

/*
    The WriteCharacter method is a getter method that returns the write character of the
    ransition as a character It returns the value of the write attribute.
*/
char Transition::WriteCharacter() const
{
    return write;
}

/*
    The MoveDirection method is a getter method that returns the direction to move the
    tape head in as a Direction enumeration value. It returns a value of either LEFT or
    RIGHT. It returns the value of the source attribute.
*/
Direction Transition::MoveDirection() const
{
    return direction;
}
