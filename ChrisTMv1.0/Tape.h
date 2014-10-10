/*
    Module: Tape
    File: Tape.h
    Application: TuringMachineApplication
    Language: C++
    Computer: Macbook Air
    Operating System: Ubuntu 14.10
    Course: CptS 322
    Author: Christopher Wilkins
    Date: 5/5/2014
    Description:
    Tape.h contains the code declaration for the Tape class.
    The tape of a Turing machine consists of an ordered sequence of cells,
    indexed starting at 0, which may grow to any size needed up to the limit
    of storage during operation of the machine on an input string. Each cell
    contains a character in the tape alphabet. An input string is stored in the
    lowest numbered tape cells at the beginning of operation, and all other tape
    cells initially contain the blank character. The current cell starts at the first
    cell on the tape. In performing a transition of the Turing machine, the character
    contained in the current cell may be read and written, and the current cell may be
    moved one cell to the left or right. The tape exists only as part of a Turing machine.
*/
#ifndef TAPE_H
#define TAPE_H

#include "Direction.h"
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class Tape
{
    private:
    string cells;
    int currentCell;
    char blank;

    public:
    Tape();
    void Load(fstream& definitionFile, bool& valid);
    void View() const;
    void Initialize(string inputString);
    void Update(char writeCharacter, Direction moveDirection);
    string Left(int maximumNumberOfCells) const;
    string Right(int maximumNumberOfCells) const;
    char CurrentCharacter() const;
    char BlankCharacter() const;
    bool IsFirstCell() const;
};

#endif // TAPE_H
