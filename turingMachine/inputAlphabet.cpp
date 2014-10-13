#include "inputAlphabet.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

InputAlphabet::InputAlphabet()
{
}

char InputAlphabet::Element(int index) const
{
	return m_alphabet[index];
}
	
bool InputAlphabet::IsElement(char value)
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

void InputAlphabet::Load(ifstream &definition, bool &valid)
{
	string value;
	while(((definition>>value) && (value != "TAPE_ALPHABET:")))
	{
		if(!((value.length() == 1)
			&& (value[0] != '\\') && (value[0] != '[')
			&& (value[0] != ']') && (value[0] != '<')
			&& (value[0] != '>') && (value[0] >= '!')
			&& (value[0] <= '~')))
		{
			cout<<"Illegal Input Alphabet character "<<value<<".\n";
			valid = false;
		}
		else if(IsElement(value[0]))
		{
			cout<<"Input Character "<<value<<" in the Input Alphabet twice.\n";
			valid = false;
		}
		else
		{
			m_alphabet.push_back(value[0]);
		}
	}
}

int InputAlphabet::Size() const
{
	return m_alphabet.size();
}

void InputAlphabet::View() const
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