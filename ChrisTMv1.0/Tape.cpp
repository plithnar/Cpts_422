/*
    Module: Tape
    File: Tape.cpp
    Application: TuringMachineApplication
    Language: C++
    Computer: Macbook Air
    Operating System: Ubuntu 14.10
    Course: CptS 322
    Author: Christopher Wilkins
    Date: 5/5/2014
    Description:
    Tape.cpp contains the code implementation for the Tape class.
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
#include "Tape.h"

#include "Direction.h"
#include "Crash.h"
#include "UpperCase.h"
#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

/*
    The tape constructor initialize the attributes of the Tape class.
    It initializes the tape cells with a single space, initializes the
    currentCell number to 0, and initializes the blank character to an
    empty space.
*/
Tape::Tape():
      cells(" "), currentCell(0), blank(' ')
{
}

/*
    The method Load reads the blank character from the Turing machine definition
    file. If the blank character is reserved or not printable, or the next keyword
    does not follow in the file, an error message is displayed and valid is set to false.
*/
void Tape::Load(fstream& definitionFile, bool& valid)
{
    string value;
    if ((definitionFile >> value)   &&
        (value.length() == 1)       &&
        (value[0] != '\\')          &&
        (value[0] != '[')   && (value[0] != ']') &&
        (value[0] != '<')   && (value[0] != '>') &&
        (value[0] >= '!')   && (value[0] <= '~'))
    {
        blank = value[0];
    }
    else
    {
        valid = false;
        cout << "Illegal blank character" << endl;
    }

    if (!(definitionFile >> value) || ToUpper(value) != "FINAL_STATES:")
    {
        valid = false;
        cout << "Missing keyword after blank character." << endl;
    }
}

/*
    The method view displays the blank character of the Turing machine.
*/
void Tape::View() const
{
    cout << "B = " << blank <<  endl << endl;
}

/*
    The method initialize sets the Turing machine tape to the input string
    given by the inputString parameter followed by a blank character, replacing
    the previous contents of the tape. The current cell is set to the first cell
    on the tape, indicated by the index 0.
*/
void Tape::Initialize(string inputString)
{
    cells = inputString + blank;
    currentCell = 0;
}

/*
    The method update first determines if the update of the Turing machine tape
    is possible. The method returns if a left move is specified from the first cell.
    If a right move is specified from the last cell, a blank character is appended to
    the tape. If no storage is available for this character, the character to write on
    the tap is stored in the current cell, replacing the previous character in that cell.
    To move the current cell one cell to the left, the index is decremented, or to move the
    current cell one cell to the right, the index is incremented.
*/
void Tape::Update(char writeCharacter, Direction moveDirection)
{
    if (moveDirection == LEFT && (unsigned int) currentCell == 0)
        throw Crash("Left move from first cell.");
    if (moveDirection == RIGHT && (unsigned int) currentCell == cells.length()-1)
        cells += blank;
    cells[currentCell] = writeCharacter;
    if (moveDirection == LEFT)
        currentCell--;
    else
        currentCell++;
}

/*
    The method left returns the character string up to the maximum number of cells from the
    Turing machine tape to the left of the current cell, excluding that cell. The length of the
    string will be less than the maximum if there are fewer cells to the left of the current cell.
    If the string is truncated from the tape, the reserved character '<' will be added to the beginning
    of the string.
*/
string Tape::Left(int maximumNumberOfCells) const
{
    int firstCell = max(currentCell - maximumNumberOfCells, 0);
    string value = cells.substr(firstCell, currentCell - firstCell);
    if (value.length() < (unsigned int) currentCell)
    {
        value.insert(0, "<");
    }
    return value;
}

/*
    The method right returns a character string up to the maximum number of cells from the Turing machine
    tape to the right of the current cell, including that cell. The length of the string will be less than
    the maximum if there are fewer cells to the right of the current cell up to the rightmost nonblank character.
    If the string is truncated from the tape, the reserved character '>' will be added to the end of the string.
*/
string Tape::Right(int maximumNumberOfCells) const
{
    int endCell = cells.length()-1;
    while (endCell >= currentCell && cells[endCell] == blank)
    {
        endCell--;
    }
    int lastCell = min(endCell, currentCell + maximumNumberOfCells);
    string value = cells.substr(currentCell, lastCell - currentCell + 1);
    if (value.length() < (unsigned int)(endCell - currentCell + 1))
    {
        value.append(">");
    }
    return value;
}

/*
    The method current_character returns the character contained in the current cell on the Turing machine tape.
*/
char Tape::CurrentCharacter() const
{
    return cells[currentCell];
}

/*
    The method blankCharacter return the blank character of the Turing machine tape.
*/
char Tape::BlankCharacter() const
{
    return blank;
}

/*
    The method IsFirstCell returns a value of true if the current cell on the Turing machine
    tape is the first cell, indicated by the index 0. Otherwise it returns a value of false.
*/
bool Tape::IsFirstCell() const
{
    return (currentCell == 0);
}
