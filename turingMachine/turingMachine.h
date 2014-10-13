#ifndef TURING_MACHINE_H
#define TURING_MACHINE_H

#include <string>
#include <vector>
#include <iostream>
#include "tape.h"
#include "inputAlphabet.h"
#include "tapeAlphabet.h"
#include "transitionFunction.h"
#include "state.h"
#include "finalStates.h"

using namespace std;

class TuringMachine
{
private:
	Tape m_tape;
	InputAlphabet m_inputAlphabet;
	TapeAlphabet m_tapeAlphabet;
	TransitionFunction m_transitionFunction;
	vector<State> m_states;
	vector<State> m_finalStates;

	vector<char> m_description;
	string m_initialState;
	string m_currentState;
	string m_originalInputString;
	int m_numberOfTransitions;
	bool m_valid;
	bool m_used;
	bool m_operating;
	bool m_accepted;
	bool m_rejected;

public:
	TuringMachine(string definitionFileName);
	void ViewDefinition() const;
	void ViewInstantaneousDescription(int maxNumCells) const;
	void Initialize(string InputString);
	void PerformTransitions(int maxNumberOfTransitions);
	void TerminateOperation();
	string InputString() const;
	int TotalNumberOfTransitions() const;
	bool IsValidDefinition() const;
	bool IsValidInputString(string value) const;
	bool IsUsed() const;
	bool IsOperating() const;
	bool IsAcceptedInputString() const;
	bool IsRejectedInputString() const;
};


#endif