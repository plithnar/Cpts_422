/*
    Module: Direction
    File: Direction.cpp
    Application: TuringMachineApplication
    Language: C++
    Computer: Macbook Air
    Operating System: Ubuntu 14.10
    Course: CptS 322
    Author: Christopher Wilkins
    Date: 5/5/2014
    Description:
    Direction.cpp contains the code implementation for Direction module.
    The Direction module provides methods to convert a Direction enumerated
    value to a string and convert a string to a Direction enumerated value.
*/
#include "Direction.h"
#include "Crash.h"

#include <string>

using namespace std;

/*
    The ReadDirection reads a value of a direction given as a string called dir.
    This string can contain either “R” or “L” in uppercase. This method determines
    the correct value of the Direction enumerated value.
*/
Direction ReadDirection(string dir)
{
    if (dir == "L")
        return LEFT;
    else if (dir == "R")
        return RIGHT;
    else
        throw Crash("Invalid direction");
}

/*
    The PrintDirection method accepts a value of the Direction enumeration as a parameter.
    It converts this direction to a string. If the enumerated value is “RIGHT”, a string
    is return with the value of “R”. If the enumerated value is “LEFT” a string is returned
    with the value of “L”
*/
string PrintDirection(Direction direction)
{
    switch (direction)
    {
        case LEFT:
        return string("L");
        case RIGHT:
        return string("R");
    }
    return "L";
}
