#include "Tests.h"

#include <iostream>
#include <string>
#include <fstream>

#include "TransitionFunction.h"

using namespace std;

void TestTransitionFunction()
{
    fstream file("tmtransitionfunction.def");
    bool valid = true;
    string input("");
    file >> input;
    TransitionFunction transitionFunction;
    transitionFunction.Load(file, valid);
    transitionFunction.View();
    if (valid)
        cout << "yes" << endl;
    else
        cout << "no" << endl;
}
