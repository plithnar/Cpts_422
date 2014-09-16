#ifndef STATE_H
#define STATE_H

#include <string>

using namespace std;

class State
{
    private:
    string* name;
    static int numberOfStates;

    public:
    State();
    State(string name);
    State(const State& state);
    State& operator=(const State& state);
    virtual ~State();

    void GetName(string& stateName) const;
    void SetName(string stateName);
    static int TotalNumberOfStates();
};

typedef State* statePointer;

#endif // STATE_H
