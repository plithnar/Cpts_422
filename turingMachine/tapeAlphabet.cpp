#include "tapeAlphabet.h"
#include <vector>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

TapeAlphabet::TapeAlphabet()
{
}

char TapeAlphabet::Element(int index) const
{
	return m_alphabet[index];
}
	
bool TapeAlphabet::IsElement(char value) const
{
	for(int i = 0; i < Size(); i++)
	{
		if(Element(i) == value)
		{
			return true;
		}
	}
	return false;
}

void TapeAlphabet::Load(ifstream &definition, bool &valid)
{
	string value;
	while(((definition>>value) && (value != "TRANSITION_FUNCTION:")))
	{
		if(!((value.length() == 1)
			&& (value[0] != '\\') && (value[0] != '[')
			&& (value[0] != ']') && (value[0] != '<')
			&& (value[0] != '>') && (value[0] >= '!')
			&& (value[0] <= '~')))
		{
			cout<<"Illegal Tape Alphabet character "<<value<<".\n";
			valid = false;
		}
		else if(IsElement(value[0]))
		{
			cout<<"Input Character "<<value<<" in the Tape Alphabet twice.\n";
			valid = false;
		}
		else
		{
			m_alphabet.push_back(value[0]);
		}
	}
}

int TapeAlphabet::Size() const
{
	return m_alphabet.size();
}

void TapeAlphabet::View() const
{
	for(int i = 0; i < Size(); i++)
	{
		cout<<Element(i);
		if(i != (Size() - 1))
		{
			cout<<", ";
		}
	}
}