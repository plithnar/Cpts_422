#include <iostream>
#include <fstream>

#include "Tests.h"
#include "States.h"
#include "FinalStates.h"

using namespace std;

void TestStates()
{
    fstream file("tmstates.def");
    bool valid = true;
    string input("");
    file >> input;
    States states;
    states.Load(file, valid);
    states.View();
    if (valid)
        cout << "yes" << endl;
    else
        cout << "no" << endl;
}

void TestFinalStates()
{
    fstream file("tmfinalstates.def");
    bool valid = true;
    string input("");
    file >> input;
    FinalStates states;
    states.Load(file, valid);
    states.View();
    if (valid)
        cout << "yes" << endl;
    else
        cout << "no" << endl;
}
