#include "transitionFunction.h"
#include "transition.h"
#include "direction.h"
#include <string>
#include <fstream>
#include <vector>
#include <iostream>

using namespace std;

void TransitionFunction::Load(ifstream& definition, bool& valid)
{
}

void TransitionFunction::Add(Transition t)
{
	transitions.push_back(t);
}

void TransitionFunction::View(void) const
{
	int i = 0;
	for(i = 0; i < (int)transitions.size(); i++)
	{
		cout<<"("<<transitions[i].GetSource()<<", ";
		cout<<transitions[i].GetRead()<<") = (";
		cout<<transitions[i].GetDestination()<<", ";
		cout<<transitions[i].GetWrite()<<", ";
		cout<<transitions[i].GetMove()<<")"<<endl;
	}
}

int TransitionFunction::Size(void) const
{
	return transitions.size();
}

string TransitionFunction::SourceState(int index) const
{
	return transitions[index].GetSource();
}

char TransitionFunction::ReadCharacter(int index) const
{
	return transitions[index].GetRead();
}

string TransitionFunction::DestinationState(int index) const
{
	return transitions[index].GetDestination();
}

char TransitionFunction::WriteCharacter(int index) const
{
	return transitions[index].GetWrite();
}

bool TransitionFunction::IsDefinedTransition(string source, char read,
											 string &destination, char &write,
											 Direction &move) const
{
	for(int i = 0; i < (int)transitions.size(); i++)
	{
		if((transitions[i].GetSource() == source) && (transitions[i].GetRead() == read))
		{
			destination = transitions[i].GetDestination();
			write = transitions[i].GetWrite();
			move = transitions[i].GetMove();
			return true;
		}
	}

	return false;
}

bool TransitionFunction::IsSourceState(string state) const
{
	int i = 0;
	for(i = 0; i < (int)transitions.size(); i++)
	{
		if(transitions[i].GetSource() == state)
		{
			return true;
		}
	}

	return false;
}