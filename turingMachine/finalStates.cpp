#include "finalStates.h"
#include "stringPointer.h"
#include <string>

using namespace std;

int FinalState::NumberOfStates = 0;

FinalState::FinalState()
{
	m_name = new string();
	NumberOfStates++;
}

FinalState::FinalState(string stateName)
{
	m_name = new string(stateName);
	NumberOfStates++;
}

FinalState::FinalState(const FinalState& state)
{
	m_name = new string(*state.m_name);
	NumberOfStates++;
}

FinalState::~FinalState()
{
	delete m_name;
	NumberOfStates--;
}

FinalState& FinalState::operator=(const FinalState& rhs)
{
	if(this != &rhs)
	{
		*m_name = *rhs.m_name;
	}
	return *this;
}

void FinalState::GetName(string& stateName) const
{
	stateName = *m_name;
}

void FinalState::SetName(string stateName)
{
	*m_name = stateName;
}

int FinalState::TotalNumberOfStates()
{
	return NumberOfStates;
}

void FinalState::Load(ifstream &definitionFile, bool &valid)
{

}