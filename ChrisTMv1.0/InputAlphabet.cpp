/*
    Module: InputAlphabet
    File: InputAlphabet.cpp
    Application: TuringMachineApplication
    Language: C++
    Computer: Macbook Air
    Operating System: Ubuntu 14.10
    Course: CptS 322
    Author: Christopher Wilkins
    Date: 5/5/2014
    Description:
    InputAlphabet.cpp contains the code implementation for the InputAlphabet class.
    The tape alphabet of a turing machine consists of the characters that can be used
    as input to the turing machine. It is responsible for reading the INPUT_ALPHABET
    section of the Turing Machine definition file and checking to see if it is valid.
*/
#include "InputAlphabet.h"
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include "UpperCase.h"

using namespace std;

/*
    The method load reads a series of characters from the Turing machine definition file.
    Each character is separated by any number of white space characters. Each character
    becomes an element of the alphabet character vector. If any of the characters are
    reserved or not printable, or the next keyword does not follow in the file, an error
    message is displayed and valid is set to false. If the file consists of characters that
    are not separated by any white space, an error message is displayed and valid is set to false.
*/
void InputAlphabet::Load(fstream& definitionFile, bool& valid)
{
    const string nextToken = "TAPE_ALPHABET:";
    stringstream readAlpha;
    string temp("");
    while (definitionFile >> temp)
    {
        char readChar = 0;
        if (ToUpper(temp) == nextToken)
        {
            if (alphabet.size() < 1)
            {
                cout << "Empty input alphabet section." << endl;
                valid = false;
            }
            return;
        }
        readAlpha << temp;
        readAlpha >> readChar;
        if (readChar == 0)
        {
            valid = false;
            cout << "Invalid character in input alphabet." << endl;
            return;
        }
        else
        {
            if (IsElement(readChar))
            {
                valid = false;
                cout << "Duplicate element in input alphabet." << endl;
                return;
            }
            alphabet.push_back(readChar);
        }
    }
    if (ToUpper(temp) != nextToken)
    {
        cout << nextToken << " not found after input alphabet." << endl;
        valid = false;
    }
}

/*
    The View method prints the input alphabet to the screen. It prints out each element of
    the alphabet character vector with each character separated by a comma and a space.
*/
void InputAlphabet::View() const
{
    cout << "Sigma: { ";
    for (unsigned int i=0; i<alphabet.size(); i++)
    {
        cout << alphabet[i] << " ";
    }
    cout << "}" << endl << endl;
}

/*
    The Size method returns the number of characters that are in the alphabet character vector.
*/
int InputAlphabet::Size() const
{
    return alphabet.size();
}

/*
    The Element method returns the input character at a given index in the alphabet character
    vector. If the index is less than zero or greater than the size of the alphabet character
    vector, it throws an exception and exits. Otherwise, it returns the character at the given
    index in the alphabet character vector.
*/
char InputAlphabet::Element(int index) const
{
    // if out of bounds, out of range exception is thrown by std::vector
    return alphabet[index];
}

/*
    The IsElement method accepts a character value and looks to see if the character is an element
    of the alphabet character vector. If the character is in the alphabet character vector, the method
    returns true. Otherwise, the method returns false.
*/
bool InputAlphabet::IsElement(char value) const
{
    for (unsigned int i = 0; i < alphabet.size(); i++)
    {
        if (alphabet[i] == value)
            return true;
    }
    return false;
}
