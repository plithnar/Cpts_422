#ifndef STATE_H
#define STATE_H

#include "stringPointer.h"
#include <string>
#include <fstream>

using namespace std;

class State
{
private:
	stringPointer m_name;
	static int NumberOfStates;

public:
	State();
	State(string stateName);
	State(const State& fullState);

	virtual ~State();

	State& operator= (const State& rhs);

	void GetName(string& stateName) const;

	void SetName(string stateName);

	int TotalNumberOfStates(void);

	void Load(ifstream &definitionFile, bool &valid);
};

typedef State * StatePointer;
#endif