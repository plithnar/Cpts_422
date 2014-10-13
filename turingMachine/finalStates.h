#ifndef FINAL_STATE_H
#define FINAL_STATE_H

#include "stringPointer.h"
#include <string>

using namespace std;

class FinalState
{
private:
	stringPointer m_name;
	static int NumberOfStates;

public:
	FinalState();
	FinalState(string stateName);
	FinalState(const FinalState& fullState);

	virtual ~FinalState();

	FinalState& operator= (const FinalState& rhs);

	void GetName(string& stateName) const;

	void SetName(string stateName);

	int TotalNumberOfStates(void);

	void Load(ifstream &definitionFile, bool &valid);
};

typedef FinalState * FinalStatePointer;
#endif