#include "Tests.h"

#include "TuringMachine.h"

#include <iostream>

int main()
{
    TuringMachine tm("tm.def");
    if (!tm.IsValid()) return 1;
    tm.ViewDefinition();

    tm.Initialize("aaaaaabbbbbb");
    tm.PerformTransitions(1);
    while (tm.IsOperating())
    {
        string a;
        tm.PerformTransitions(1);
        cin >> a;
        cout << a << endl;
    }
    return 0;
}
