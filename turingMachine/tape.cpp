#include "crash.h"
#include "tape.h"
#include "direction.h"
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;

Tape::Tape():m_cells(" "),
			 m_currentCell(0),
			 m_blank(' ')
{
}

void Tape::Load(ifstream &definition, bool &valid)
{
	string value;
	if((definition>>value) && (value.length() == 1)
		&& (value[0] != '\\') && (value[0] != '[')
		&& (value[0] != ']') && (value[0] != '<')
		&& (value[0] != '>') && (value[0] >= '!')
		&& (value[0] <= '~'))
	{
		m_blank = value[0];
	}
	else
	{
		cout<<"Illegal blank character.\n";
		valid = false;
	}
	if(((definition>>value) && (value != "FINAL_STATES:")))
	{
		cout<<"Missing Final States keyword after blank.\n";
		valid = false;
	}
}

void Tape::View() const
{
	cout<<"B = "<<m_blank<<endl<<endl;
}

void Tape::Initialize(string input)
{
	m_cells = input + m_blank;
	m_currentCell = 0;
}

void Tape::Update(char writeCharacter, Direction moveDirection)
{
	moveDirection = toupper(moveDirection);

	if((moveDirection == 'L') && (m_currentCell == 0))
	{
		throw Crash("Left move from first cell");
	}

	if((moveDirection == 'R') && (m_currentCell  == (int)m_cells.length() - 1))
	{
		m_cells += m_blank;
	}
	m_cells[m_currentCell] = writeCharacter;
	if(moveDirection == 'L')
	{
		m_currentCell--;
	}
	else
	{
		m_currentCell++;
	}
}

string Tape::Left(int maxNumberCells) const
{
	int firstCell;
	firstCell = max(0, m_currentCell - maxNumberCells);
	string value = m_cells.substr(firstCell, m_currentCell-firstCell);
	if((int)value.length() < m_currentCell)
	{
		value.insert(0, "<");
	}
	return value;
}

string Tape::Right(int maxNumberCells) const
{
	int lastCell = m_cells.length() - 1;
	while((lastCell >= m_currentCell) && (m_cells[lastCell] == m_blank))
	{
		lastCell--;
	}

	int lastPrintCell = min(lastCell, m_currentCell + maxNumberCells - 1);

	string value = m_cells.substr(m_currentCell, lastPrintCell - m_currentCell + 1);

	if((int)value.length() < (lastCell - m_currentCell + 1))
	{
		value.append(">");
	}
	return value;
}

char Tape::CurrentCharacter() const
{
	return m_cells[m_currentCell];
}

char Tape::BlankCharacter() const
{
	return m_blank;
}

bool Tape::IsFirstCell() const
{
	if(m_currentCell == 0)
	{
		return true;
	}
	return false;
}

