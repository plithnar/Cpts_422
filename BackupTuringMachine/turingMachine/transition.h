#ifndef TRANSITION_H
#define TRANSITION_H

#include "direction.h"
#include <string>

using namespace std;

class Transition
{
private:
	string source;
	char read;
	string destination;
	char write;
	Direction move;

public:
	Transition(string newSource, char newRead, string newDest, char newWrite,
				Direction newDir);

	string GetSource() const;

	char GetRead() const;

	string GetDestination() const;

	char GetWrite() const;

	Direction GetMove() const;
};

#endif