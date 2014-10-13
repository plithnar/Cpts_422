#include "state.h"
#include "stringPointer.h"
#include <string>

using namespace std;

int State::NumberOfStates = 0;

State::State()
{
	m_name = new string();
	NumberOfStates++;
}

State::State(string stateName)
{
	m_name = new string(stateName);
	NumberOfStates++;
}

State::State(const State& state)
{
	m_name = new string(*state.m_name);
	NumberOfStates++;
}

State::~State()
{
	delete m_name;
	NumberOfStates--;
}

State& State::operator=(const State& rhs)
{
	if(this != &rhs)
	{
		*m_name = *rhs.m_name;
	}
	return *this;
}

void State::GetName(string& stateName) const
{
	stateName = *m_name;
}

void State::SetName(string stateName)
{
	*m_name = stateName;
}

int State::TotalNumberOfStates()
{
	return NumberOfStates;
}

void State::Load(ifstream &definitionFile, bool &valid)
{

}