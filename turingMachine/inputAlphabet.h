#ifndef INPUT_ALPHABET_H
#define INPUT_ALPHABET_H

#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

class InputAlphabet
{
private:
	vector<char> m_alphabet;

public:
	InputAlphabet();
	char Element(int index) const;
	bool IsElement(char value);
	void Load(ifstream &definition, bool &valid);
	int Size() const;
	void View() const;
};
#endif