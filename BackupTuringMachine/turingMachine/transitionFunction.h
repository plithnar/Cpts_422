#ifndef TRANSITION_FUNCTION_H
#define TRANSITION_FUNCTION_H

#include "transition.h"
#include "direction.h"
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class TransitionFunction
{
private:
	vector<Transition> transitions;

public:
	void Load(ifstream &definition, bool &valid);
	void View(void) const;
	void Add(Transition t);
	int Size() const;
	string SourceState(int index) const;
	char ReadCharacter(int index) const;
	string DestinationState(int index) const;
	char WriteCharacter(int index) const;

	bool IsDefinedTransition(string sourceState, char readChar, string &destState,
							 char &writeCharacter, Direction &moveDirection) const;

	bool IsSourceState(string state) const;
};


#endif