/*
    Module: InputAlphabet
    File: InputAlphabet.h
    Application: TuringMachineApplication
    Language: C++
    Computer: Macbook Air
    Operating System: Ubuntu 14.10
    Course: CptS 322
    Author: Christopher Wilkins
    Date: 5/5/2014
    Description:
    InputAlphabet.h contains the code declaration for the InputAlphabet class.
    The tape alphabet of a turing machine consists of the characters that can be used
    as input to the turing machine. It is responsible for reading the INPUT_ALPHABET
    section of the Turing Machine definition file and checking to see if it is valid.
*/
#ifndef INPUTALPHABET_H
#define INPUTALPHABET_H

#include <fstream>
#include <string>
#include <vector>

using namespace std;

class InputAlphabet
{
    private:
    vector<char> alphabet;

    public:
    void Load(fstream& definitionFile, bool& valid);
    void View() const;
    int Size() const;
    char Element(int index) const;
    bool IsElement(char value) const;
};

#endif // INPUTALPHABET_H
