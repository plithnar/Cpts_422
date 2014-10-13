#include "transition.h"
#include <string>

using namespace std;

Transition::Transition(string newSource, char newRead, string newDest, char newWrite,
				Direction newDir):
	source(newSource),
	read(newRead),
	destination(newDest),
	write(newWrite),
	move(newDir)
{
};

string Transition::GetSource() const
{
	return source;
};

char Transition::GetRead() const
{
	return read;
};

string Transition::GetDestination() const
{
	return destination;
};

char Transition::GetWrite() const
{
	return write;
};

Direction Transition::GetMove() const
{
	return move;
}