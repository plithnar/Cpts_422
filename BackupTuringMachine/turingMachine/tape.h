#ifndef TAPE_H
#define TAPE_H

#include "direction.h"
#include <string>
#include <fstream>

using namespace std;

class Tape
{
private:
	string m_cells;
	int m_currentCell;
	char m_blank;

public:
	Tape();
	void Load(ifstream &definition, bool &valid);
	void View() const;
	void Initialize(string inputString);
	void Update(char writeChar, Direction moveDirection);
	string Left(int maxNumberOfCells) const;
	string Right(int maxNumberOfCells) const;
	char CurrentCharacter() const;
	char BlankCharacter() const;
	bool IsFirstCell() const;
};

#endif