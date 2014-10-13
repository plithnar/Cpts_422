#include "turingMachine.h"
#include "tape.h"
#include "inputAlphabet.h"
#include "tapeAlphabet.h"
#include "state.h"
#include "finalStates.h"
#include <string>
#include <vector>
#include <iostream>

using namespace std;

TuringMachine::TuringMachine(string definitionFileName)
{
	// open file
	m_numberOfTransitions = 0;
	m_used = false;
	m_operating = false;
	m_accepted = false;
	m_rejected = false;
	ifstream defFile;
	m_valid = true;
	defFile.open(definitionFileName.c_str());
	if(!defFile)
	{
		cout<<"File "<<definitionFileName<<" does not exist\n";
		m_valid = false;
	}
	else
	{
		char desValue = ' ';
		char buffer[6];
		int level = 0;
		// load the description
		desValue = defFile.get();
		while(desValue != EOF)
		{
			if(desValue == 'S')
			{
				buffer[0] = desValue;
				desValue = defFile.get();
				level++;
				if(desValue == 'T')
				{
					buffer[1] = desValue;
					desValue = defFile.get();
					level++;
					if(desValue == 'A')
					{
						buffer[2] = desValue;
						desValue = defFile.get();
						level++;
						if(desValue == 'T')
						{
							buffer[3] = desValue;
							desValue = defFile.get();
							level++;
							if(desValue == 'E')
							{
								buffer[4] = desValue;
								desValue = defFile.get();
								level++;
								if(desValue == 'S')
								{
									buffer[5] = desValue;
									desValue = defFile.get();
									level++;
									if(desValue == ':')
									{
										break;
									}
								}
							}
						}
					}
				}
				for(int i = 0; i < level; i++)
				{
					m_description.push_back(buffer[i]);
				}
				level = 0;
			}
			m_description.push_back(desValue);
			desValue = defFile.get();
		}
		//	cout<<"DESCRIPTION STARTS\n";

		//	for(int i = 0; i < m_description.size(); i++)
		//	{
		//		cout<<m_description[i];
		//	}
		string value;
		// load states
		while((defFile>>value) && (value != "INPUT_ALPHABET:"))
		{
			StatePointer s = new State(value);
			bool duplicate = false;
			for(int i = 0; i < (int)m_states.size(); i++)
			{
				string name;
				m_states[i].GetName(name);
				if(name == value)
				{
					duplicate = true;
				}
			}
			if(!duplicate)
			{
				m_states.push_back(*s);
			}
			else
			{
				cout<<"Error: Duplicate state "<<value<<" in definition file\n";
				m_valid = false;
			}
			delete(s);
		}
		//	cout<<m_description[0];
		// pass to input to load input
		m_inputAlphabet.Load(defFile, m_valid);
		// pass to tapeAlphabet to load tapeAlphabet
		m_tapeAlphabet.Load(defFile, m_valid);

		for(int i = 0; i < m_inputAlphabet.Size(); i++)
		{
			if(!m_tapeAlphabet.IsElement(m_inputAlphabet.Element(i)))
			{
				cout<<"Error: Input character "<<m_inputAlphabet.Element(i);
				cout<<" is not a tape character.\n";
				m_valid = false;
			}
		}

		//	cout<<m_description[0];
		// pass to transitionFunction to load transitions

		bool sourceNext = true;
		bool readNext = false;
		bool destNext = false;
		bool writeNext = false;
		bool moveNext = false;
		//bool fullTransition = false;

		string source, destination;
		char read, write;
		Direction move;

		while((defFile>>value) && (value != "INITIAL_STATE:"))
		{
			bool stateMatch = false;
			if(sourceNext)
			{
				string stateTest = "";
				for(int i = 0; i < (int)m_states.size() && !stateMatch; i++)
				{
					m_states[i].GetName(stateTest);
					if(value == stateTest)
					{
						stateMatch = true;
					}
				}
				if(!stateMatch)
				{
					cout<<value<<" is not a valid state, defines an invalid transition function"<<endl;
					m_valid = false;
				}
				else
				{
					source = value;
					sourceNext = false;
					readNext = true;
				}
			}
			else if(readNext)
			{
				if(value.length() != 1)
				{
					cout<<value<<" is not a valid tape character, defines an invalid transition function"<<endl;
					m_valid = false;
				}
				else if(!m_tapeAlphabet.IsElement(value[0]))
				{
					cout<<value<<" is not a valid tape character, defines an invalid transition function"<<endl;
					m_valid = false;
				}
				else
				{
					read = value[0];
					readNext = false;
					destNext = true;
				}
			}
			else if(destNext)
			{
				string stateTest = "";
				for(int i = 0; i < (int)m_states.size() && !stateMatch; i++)
				{
					m_states[i].GetName(stateTest);
					if(value == stateTest)
					{
						stateMatch = true;
					}
				}
				if(!stateMatch)
				{
					cout<<value<<" is not a valid state, defines an invalid transition function"<<endl;
				}
				else
				{
					destination = value;
					destNext = false;
					writeNext = true;
				}
			}
			else if(writeNext)
			{
				if(value.length() != 1)
				{
					cout<<value<<" is not a valid tape character, defines an invalid transition function"<<endl;
					m_valid = false;
				}
				else if(!m_tapeAlphabet.IsElement(value[0]))
				{
					cout<<value<<" is not a valid tape character, defines an invalid transition function"<<endl;
					m_valid = false;
				}
				else
				{
					write = value[0];
					writeNext = false;
					moveNext = true;
				}
			}
			else if(moveNext)
			{
				value[0] = toupper(value[0]);
				if(value.length() != 1)
				{
					cout<<value<<" is not a valid direction, defines an invalid transition function"<<endl;
					m_valid = false;
				}
				else if(!((value[0] == 'L') || (value[0] == 'R')))
				{
					cout<<value<<" is not a valid direction, defines an invalid transition function"<<endl;
					m_valid = false;
				}
				else
				{
					move = value[0];
					sourceNext = true;
					moveNext = false;
					//		fullTransition = true;
					bool found = false;
					for(int i = 0; i < m_transitionFunction.Size(); i++)
					{
						if((m_transitionFunction.SourceState(i) == source) &&
							(m_transitionFunction.ReadCharacter(i) == read))
						{
							found = true;
						}
					}
					if(found)
					{
						cout<<"Error: Transition from state "<<source;
						cout<<" reading character "<<read<<" is already defined\n";
						m_valid = false;
					}
					else
					{
						Transition t(source, read, destination, write, move);
						m_transitionFunction.Add(t);
					}
				}
			}
		}

		if((!sourceNext))
		{
			cout<<"Error, incomplete transition function provided\n";
			m_valid = false;
		}

		// read for initialState

		if((defFile>>value))
		{
			bool stateMatch =  false;
			for(int i = 0; i < (int)m_states.size() && !stateMatch; i++)
			{
				string stateTest;
				m_states[i].GetName(stateTest);
				if(value == stateTest)
				{
					stateMatch = true;
				}
			}
			if(stateMatch)
			{
				m_initialState = value;
			}
			else
			{
				cout<<"Illegal initial state character.\n";
				m_valid = false;
			}
		}

		if(!((defFile>>value) && (value == "BLANK_CHARACTER:")))
		{
			cout<<"Missing blank character keyword after initialState.\n";
			m_valid = false;
		}

		// pass to tape to load blank
		m_tape.Load(defFile, m_valid);

		if(!(m_tapeAlphabet.IsElement(m_tape.BlankCharacter()))) 
		{
			cout<<"Error: Blank character "<<m_tape.BlankCharacter();
			cout<<" is not a member of the tape alphabet.\n";
			m_valid = false;
		}

		if(m_inputAlphabet.IsElement(m_tape.BlankCharacter()))
		{

			cout<<"Error: Blank character "<<m_tape.BlankCharacter();
			cout<<" is a member of the input alphabet.\n";
		}

		// pass to finalStates to load final states
		while((defFile>>value))
		{
			StatePointer s = new State(value);
			string stateTest;
			bool found = false;
			for(int i = 0; i < (int)m_states.size(); i++)
			{
				m_states[i].GetName(stateTest);
				if(value == stateTest)
				{
					found = true;
				}
			}
			if(found)
			{
				if(m_transitionFunction.IsSourceState(value))
				{
					cout<<"Error: Final state "<<value<<" has a transition out";
					cout<<" of it. Not a valid final state\n";
				}
				m_finalStates.push_back(*s);
			}
			else
			{
				cout<<"Error: final state "<<value<<" is not a valid state"<<endl;
				m_valid = false;
			}
			delete(s);
		}

		defFile.close();

		if(m_states.size() == 0)
		{
			cout<<"Error: No states defined\n";
			m_valid = false;
		}
		
		if(m_initialState.size() == 0)
		{
			cout<<"Error: No initial state defined\n";
			m_valid = false;
		}
		
		if(m_inputAlphabet.Size() == 0)
		{
			cout<<"Error: No input alphabet defined\n";
			m_valid = false;
		}

		if(m_tapeAlphabet.Size() == 0)
		{
			cout<<"Error: No tape alphabet defined\n";
			m_valid = false;
		}
		
		if(m_transitionFunction.Size() == 0)
		{
			cout<<"Error: No transitions defined\n";
			m_valid = false;
		}
	}
}

void TuringMachine::ViewDefinition() const
{
	string stateName;
	//print description
	for(int i = 0; i < (int)m_description.size(); i++)
	{
		cout<<m_description[i];
	}
	//print states
	cout<<endl<<"Q: {";
	for(int i = 0; i < (int)m_states.size(); i++)
	{
		m_states[i].GetName(stateName);
		cout<<stateName;
		if(i != ((int)m_states.size() -1))
		{
			cout<<", ";
		}
	}
	cout<<"}"<<endl<<endl;

	//print input alphabet
	cout<<"Sigma: {";
	m_inputAlphabet.View();
	cout<<"}"<<endl<<endl;

	//print tape alphabet
	cout<<"Gamma: {";
	m_tapeAlphabet.View();
	cout<<"}"<<endl<<endl;

	//print transitions
	cout<<"Delta:"<<endl;
	m_transitionFunction.View();
	cout<<endl;
	
	//print initial state
	cout<<"q0 = "<<m_initialState<<endl<<endl;

	//print blank
	m_tape.View();

	//print final states
	cout<<"F = {";
	for(int i = 0; i < (int)m_finalStates.size(); i++)
	{
		m_finalStates[i].GetName(stateName);
		cout<<stateName;
		if(i != ((int)m_finalStates.size() -1))
		{
			cout<<", ";
		}
		
	}
	cout<<"}";
}

void TuringMachine::ViewInstantaneousDescription(int maxNumCells) const
{
	//print the number of transitions
	cout<<m_numberOfTransitions<<") ";
	//print the stuff to the left of the tape head
	cout<<m_tape.Left(maxNumCells);
	//print the state (bracketed by '[]')
	cout<<"["<<m_currentState<<"]";
	//print the stuff to the right of the tape head
	cout<<m_tape.Right(maxNumCells)<<endl;
}

void TuringMachine::Initialize(string inputString)
{
	m_tape.Initialize(inputString);
	m_originalInputString = inputString;
	m_numberOfTransitions = 0;
	m_used = true;
	m_operating = true;
	m_accepted = false;
	m_rejected = false;
	m_currentState = m_initialState;
}

void TuringMachine::PerformTransitions(int maxNumberTransitions)
{
	int i = 0;
	string sourceState = m_currentState;
	char readChar;
	string destinationState;
	char writeChar;
	Direction moveDir;
	string finalStateTest;

	for(i = 0; i < maxNumberTransitions; i++)
	{
		for(int j = 0; j < (int)m_finalStates.size(); j++)
		{
			m_finalStates[j].GetName(finalStateTest);
			if(m_currentState == finalStateTest)
			{
				//String accepted at this point!
				m_accepted = true;
				m_operating = false;
				return;
			}
		}

		readChar = m_tape.CurrentCharacter();
		if(!m_transitionFunction.IsDefinedTransition(sourceState, readChar, destinationState,
												 writeChar, moveDir))
		{
			cout<<"Undefined transition from "<<sourceState<<" reading "<<readChar<<".\n";
			m_rejected = true;
			m_operating = false;
			return;
		}
		try
		{
			m_tape.Update(writeChar, moveDir);
		}
		catch(exception &e)
		{
			cout<<e.what()<<endl;
			m_rejected = true;
			m_operating = false;
			return;
		}
		m_currentState = destinationState;
		sourceState = destinationState;
		m_numberOfTransitions++;
	}
}

void TuringMachine::TerminateOperation()
{
	m_operating = false;
}

string TuringMachine::InputString() const
{
	return m_originalInputString;
}

int TuringMachine::TotalNumberOfTransitions() const
{
	return m_numberOfTransitions;
}

bool TuringMachine::IsValidDefinition() const
{
	return m_valid;
}

bool TuringMachine::IsOperating() const
{
	return m_operating;
}

bool TuringMachine::IsAcceptedInputString() const
{
	return m_accepted;
}

bool TuringMachine::IsRejectedInputString() const
{
	return m_rejected;
}

bool TuringMachine::IsUsed() const
{
	return m_used;
}

bool TuringMachine::IsValidInputString(string input) const
{
	for(int i = 0; i < (int)input.size(); i++)
	{
		bool found = false;
		for(int j = 0; (j < m_inputAlphabet.Size() && !found); j++)
		{
			if(input[i] == m_inputAlphabet.Element(j))
			{
				found = true;
			}
		}
		if(!found)
		{
			//the character isn't a part of the input alphabet
			return false;
		}
	}

	return true;
}