#include "TapeAlphabet.h"
#include "InputAlphabet.h"

#include <iostream>
#include <fstream>

void TestTapeAlphabet()
{
    fstream file("tmtapealphabet.def");
    bool valid = true;
    string input("");
    file >> input;
    TapeAlphabet tapeAlphabet;
    tapeAlphabet.Load(file, valid);
    tapeAlphabet.View();
    cout << "valid: ";
    if (valid)
        cout << "yes" << endl;
    else
        cout << "no" << endl;
}

void TestInputAlphabet()
{
    fstream file("tminputalphabet.def");
    bool valid = true;
    string input("");
    file >> input;
    InputAlphabet inputAlphabet;
    inputAlphabet.Load(file, valid);
    inputAlphabet.View();
    if (valid)
        cout << "yes" << endl;
    else
        cout << "no" << endl;
}
