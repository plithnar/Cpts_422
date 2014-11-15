#ifndef TAPE_ALPHABET_H
#define TAPE_ALPHABET_H

#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

class TapeAlphabet
{
private:
	vector<char> m_alphabet;

public:
	TapeAlphabet();
	char Element(int index) const;
	bool IsElement(char value) const;
	void Load(ifstream &definition, bool &valid);
	int Size() const;
	void View()const;
	void Alphabet(vector<char> alpha);
};
#endif