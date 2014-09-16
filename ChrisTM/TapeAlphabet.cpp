/*
    Module: TapeAlphabet
    File: TapeAlphabet.cpp
    Application: TuringMachineApplication
    Language: C++
    Computer: Macbook Air
    Operating System: Ubuntu 14.10
    Course: CptS 322
    Author: Christopher Wilkins
    Date: 5/5/2014
    Description:
    TapeAlphabet.cpp contains the code implementation for the TapeAlphabet class.
    The tape alphabet of a turing machine consists of the characters that can appear
    on the tape in the Turing machine. The tape alphabet consists of all possible characters
    regardless of whether or not they can appear in the input string. It consists of all character
    which can appear on the tape. This includes the input alphabet, the blank character, and any
    output character that can be put onto the tape by a transition. It is responsible for reading
    the TAPE_ALPHABET section of the Turing Machine definition file and checking to see if it is valid.
*/

#include "TapeAlphabet.h"
#include "UpperCase.h"
#include <sstream>
#include <string>
#include <iostream>

using namespace std;

/*
    The method load reads a series of characters from the Turing machine definition
    file. Each character is separated by any number of white space characters. Each
    character becomes an element of the alphabet character vector. If any of the
    characters are reserved or not printable, or the next keyword does not follow in
    the file, an error message is displayed and valid is set to false. If the file
    consists of characters that are not separated by any white space, an error message
    is displayed and valid is set to false.
*/
void TapeAlphabet::Load(fstream& definitionFile, bool& valid)
{
    const string nextToken = "TRANSITION_FUNCTION:";
    stringstream readAlpha;
    string temp("");
    while (definitionFile >> temp)
    {
        char readChar = 0;
        if (ToUpper(temp) == nextToken)
        {
            if (alphabet.size() < 1)
            {
                cout << "Empty tape alphabet section." << endl;
                valid = false;
            }
            return;
        }
        readAlpha << temp;
        readAlpha >> readChar;
        if (readChar == 0)
        {
            cout << "Invalid tape alphabet character." << endl;
            valid = false;
            return;
        }
        else
        {
            if (IsElement(readChar))
            {
                cout << "Duplicate tape alphabet character." << endl;
                valid = false;
                return;
            }
            alphabet.push_back(readChar);
        }
    }
    if (ToUpper(temp) != nextToken)
    {
        cout << nextToken << " not found after tape alphabet." << endl;
        valid = false;
    }
}

/*
    The View method prints the tape alphabet to the screen. It prints out each
    element of the alphabet character vector with each character separated by a
    comma and a space.
*/
void TapeAlphabet::View() const
{
    cout << "Gamma: { ";
    for (unsigned int i=0; i<alphabet.size(); i++)
    {
        cout << alphabet[i] << " ";
    }
    cout << "}" << endl << endl;
}

/*
    The IsElement method accepts a character value and looks to see if the character
    is an element of the alphabet character vector. If the character is in the alphabet
    character vector, the method returns true. Otherwise, the method returns false.
*/
bool TapeAlphabet::IsElement(char value) const
{
    for (unsigned int i = 0; i < alphabet.size(); i++)
    {
        if (alphabet[i] == value)
            return true;
    }
    return false;
}
