#include "State.h"
#include <cstddef>
#include <string>

using namespace std;

int State::numberOfStates = 0;

State::State()
{
    try
    {
        name = new string("");
    }
    catch (bad_alloc)
    {
        name = NULL;
    }
    numberOfStates++;
}

State::State(string stateName)
{
    try
    {
        name = new string(stateName);
    }
    catch (bad_alloc)
    {
        name = NULL;
    }
    numberOfStates++;
}

State::~State()
{
    delete name;
}

State::State(const State* state)
{
    name = NULL;
    try
    {
        if (state.name != NULL)
            name = new string(*state.name);
    }
    catch (bad_alloc)
    {
        name = NULL;
    }
}

State& State::operator=(const State& state)
{
    if (name != NULL)
        delete name;

    name = NULL;
    try
    {
        if (state.name != NULL)
            name = new string(*state.name);
    }
    catch (bad_alloc)
    {
        name = NULL;
    }
    return *this;
}

static int State::TotalNumberOfStates()
{
    return State::numberOfStates;
}

void State::GetName(string& stateName) const
{
    if (name != NULL)
        stateName = *name;
}
void State::SetName(string stateName)
{
    if (name != NULL)
        *name = stateName;
}
