/*
    Module: Direction
    File: Direction.h
    Application: TuringMachineApplication
    Language: C++
    Computer: Macbook Air
    Operating System: Ubuntu 14.10
    Course: CptS 322
    Author: Christopher Wilkins
    Date: 5/5/2014
    Description:
    Direction.h contains the code declaration for Direction module.
    The Direction module provides methods to convert a Direction enumerated
    value to a string and convert a string to a Direction enumerated value.
*/
#ifndef DIRECTION_H_INCLUDED
#define DIRECTION_H_INCLUDED

#include <string>
using namespace std;

enum Direction { LEFT, RIGHT };

string PrintDirection(Direction direction);

Direction ReadDirection(string dir);

#endif // DIRECTION_H_INCLUDED
