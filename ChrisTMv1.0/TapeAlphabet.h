/*
    Module: TapeAlphabet
    File: TapeAlphabet.h
    Application: TuringMachineApplication
    Language: C++
    Computer: Macbook Air
    Operating System: Ubuntu 14.10
    Course: CptS 322
    Author: Christopher Wilkins
    Date: 5/5/2014
    Description:
    TapeAlphabet.h contains the code declaration for the TapeAlphabet class.
    The tape alphabet of a turing machine consists of the characters that can appear
    on the tape in the Turing machine. The tape alphabet consists of all possible characters
    regardless of whether or not they can appear in the input string. It consists of all character
    which can appear on the tape. This includes the input alphabet, the blank character, and any
    output character that can be put onto the tape by a transition. It is responsible for reading
    the TAPE_ALPHABET section of the Turing Machine definition file and checking to see if it is valid.
*/
#ifndef TAPEALPHABET_H
#define TAPEALPHABET_H

#include <vector>
#include <fstream>

using namespace std;

class TapeAlphabet
{
    private:
    vector<char> alphabet;

    public:
    void Load(fstream& definitionFile, bool& valid);
    void View() const;
    bool IsElement(char value) const;
};

#endif // TAPEALPHABET_H
