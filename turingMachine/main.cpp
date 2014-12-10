#include "tape.h"
#include "direction.h"
#include "transition.h"
#include "turingMachine.h"
#include "transitionFunction.h"
#include <stdlib.h>
#include <vector>
#include <exception>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char* argv[])
{
	const int success(0);
	const int failure(1);

	bool showHelp = false;
	bool listChange = false;

	int numCellsShown = 32;
	int numTransitions = 1;
	
	if(argc != 2)
	{
		cout<<"Usage: turingmachine <TURING MACHINE NAME>\n";
		return failure;
	}
	//argv[1] = "fullValidTm";
	string def = ".def";
	string defFile = argv[1];
	defFile.append(def.c_str());

	string str = ".str";
	string strFile = argv[1];
	strFile.append(str.c_str());
	
	TuringMachine machine(defFile);

	if(machine.IsValidDefinition() == false)
	{
		cout<<"Definition is invalid for reasons above\n";
		cin.get();
		return failure;
	}
	cout<<argv[1]<<" successfully loaded\n";
	
	string inputLine;
	vector<string> inputList;
	ifstream inputFile(strFile.c_str());
	if(inputFile.is_open())
	{
		while(inputFile>>inputLine)
		{
			if(inputLine == "\\")
			{
				inputLine = "";
			}
			if(!machine.IsValidInputString(inputLine))
			{
				cout<<"Input string "<<inputLine<<" is not a valid string this";
				cout<<" machine can operate on.\nIgnoring string "<<inputLine<<"\n";
			}
			else
			{
				bool duplicate = false;
				for(int i = 0; i < (int)inputList.size(); i++)
				{
					if(inputLine == inputList[i])
					{
						duplicate = true;
					}
				}
				if(duplicate)
				{
					cout<<"Input string "<<inputLine<<" is already in the input";
					cout<<" string list.\nIgnoring string "<<inputLine<<"\n";
				}
				else
				{
					inputList.push_back(inputLine);
				}
			}
		}
		inputFile.close();
	}

	cout<<"\nCommand: ";
	string userInput;

	getline(cin, userInput);
	for(int i = 0; i < (int) userInput.length(); i++)
	{
		userInput[i] = toupper(userInput[i]);
	}

	while(userInput != "X")
	{
		if(userInput == "H")
		{
			if(showHelp == true)
			{
				showHelp = false;
			}
			else
			{
				showHelp = true;
			}
		}
		else if(userInput == "I")
		{
			if(showHelp)
			{
				cout<<"\nEnter a new input string for the Turing Machine, or hit \"enter\" to return to the top level\n";
				cout<<"The empty line is entered via typing \"/\" at this point\n";
			}

			string newLine;
			cout<<"\nInput string for the Turing Machine: ";
			getline(cin, newLine);
			cout<<endl;
			if(newLine == "")
			{
				//Do nothing
			}
			else
			{
				if(newLine == "\\")
				{
					newLine = "";
				}
				if(!machine.IsValidInputString(newLine))
				{
					cout<<"Input string "<<newLine<<" is not a valid string this";
					cout<<" machine can operate on.\nIgnoring string "<<newLine<<"\n";
				}
				else
				{
					bool duplicate = false;
					for(int i = 0; i < (int)inputList.size(); i++)
					{
						if(newLine == inputList[i])
						{
							duplicate = true;
						}
					}
					if(duplicate)
					{
						cout<<"Input string \""<<newLine<<"\" is already in the input";
						cout<<" string list.\nIgnoring string "<<newLine<<"\n";
					}
					else
					{
						listChange = true;
						inputList.push_back(newLine);
						if(newLine == "")
						{
							newLine = "\\";
						}
						cout<<newLine<<" successfully entered into the input string list\n";
					}
				}
			}
		}
		else if (userInput == "C")
		{
			inputList.clear();
		}
		else if(userInput == "Q")
		{
			if(machine.IsOperating())
			{
				cout<<"\nInput string\""<<machine.InputString()<<"\" was neither accepted nor rejected within ";
				cout<<machine.TotalNumberOfTransitions()<<" transitions\n";
				machine.TerminateOperation();
			}
			else
			{
				cout<<"\nError: Machine not actively running, no action taken\n";
			}
		}
		else if(userInput == "R")
		{
			if(machine.IsOperating())
			{
				machine.ViewInstantaneousDescription(numCellsShown);
				machine.PerformTransitions(numTransitions);
				machine.ViewInstantaneousDescription(numCellsShown);
				if(machine.IsAcceptedInputString())
				{
					cout<<"Input string \""<<machine.InputString()<<"\" was accepted in ";
					cout<<machine.TotalNumberOfTransitions()<<" transitions\n";
				}
				else if(machine.IsRejectedInputString())
				{
					cout<<"Input string \""<<machine.InputString()<<"\" was rejected in ";
					cout<<machine.TotalNumberOfTransitions()<<" transitions\n";
				}
			}
			else
			{
				if(showHelp)
				{
					cout<<"\nEnter the number of an input string to perform operations on\n";
					cout<<"Enter an empty string to cancel command and return to top level menu\n";
				}
				cout<<"\nEnter input string number: ";
				string changeNum;
				getline(cin, changeNum);
				cout<<endl;
				bool number = true;
				int index;
				if(changeNum == "")
				{

				}
				else
				{
					for(int i = 0; i < (int)changeNum.length(); i++)
					{
						if(!isdigit(changeNum[i]))
						{
							number = false;
						}
					}
					if(number)
					{
						index = atoi(changeNum.c_str());
						index--;
						if((index >= (int)inputList.size()) || (index < 0))
						{
							cout<<"\nError: Integer needs to be between 1 and "<<inputList.size()<<endl;
						}
						else
						{
							machine.Initialize(inputList[index]);
							machine.ViewInstantaneousDescription(numCellsShown);
							machine.PerformTransitions(numTransitions);
							machine.ViewInstantaneousDescription(numCellsShown);
							if(machine.IsAcceptedInputString())
							{
								cout<<"Input string \""<<machine.InputString()<<"\" was accepted in ";
								cout<<machine.TotalNumberOfTransitions()<<" transitions\n";
							}
							else if(machine.IsRejectedInputString())
							{
								cout<<"Input string \""<<machine.InputString()<<"\" was rejected in ";
								cout<<machine.TotalNumberOfTransitions()<<" transitions\n";
							}
						}
					}

					else
					{
						cout<<"\nError: Requires an integer value.\nReturning to top level"<<endl;
					}
				}
			}
		}
		else if(userInput == "L")
		{
			if(inputList.size() > 0)
			{
				cout<<"\nList of input strings"<<endl;
			}
			else
			{
				cout<<"\nNo strings in the input string list"<<endl;
			}
			if(showHelp)
			{
				cout<<"";
			}
			for(int i = 0; i < (int) inputList.size(); i++)
			{
				string inputString = inputList[i];
				if(inputString == "")
				{
					inputString = "\\";
				}
				cout<<i+1<<") "<<inputString<<endl;
			}
		}

		else if(userInput == "E")
		{			
			if(showHelp)
			{
				cout<<"\nEnter an integer, or hit \"enter\" to not change current setting\n";
			}

			cout<<"\nSelect max number of transitions for each \"Run\" command <Current: "<<numTransitions<<">: ";

			string changeNum;
			getline(cin, changeNum);
			cout<<endl;
			bool number = true;

			for(int i = 0; i < (int)changeNum.length(); i++)
			{
				if(!isdigit(changeNum[i]))
				{
					number = false;
				}
			}

			if(changeNum == "")
			{
				//Do nothing
			}
			else if(number)
			{
				numTransitions = atoi(changeNum.c_str());
				cout<<"\nNumber of transitions to run in a single operation set to "<<numTransitions<<endl;
			}
			else
			{
				cout<<"\nError: Requires an integer value.\nSetting unchanged"<<endl;
			}

		}

		else if(userInput == "V")
		{
			machine.ViewDefinition();
		}

		else if(userInput == "W")
		{
			cout<<"\nComputer Science 322\n";
			cout<<"Spring 2014\n";
			cout<<"Instructor: Neil Corrigan\n";
			cout<<"Author: Michael Degan\n";
			cout<<"Version: 1.0.0\n";
			cout<<endl;
			cout<<"Help message displayed: ";
			if(showHelp)
			{
				cout<<"true"<<"\n";
			}
			else
			{
				cout<<"false"<<"\n";
			}
			cout<<"Max Number of Transitions to perform: "<<numTransitions<<"\n";
			cout<<"Max number of characters to display to left and right of tape head: "<<numCellsShown<<"\n";
			cout<<endl;
			cout<<"Turing Machine name: "<<argv[1]<<"\n";

			//Conditional for if tm ran, running, etc.
			if(!machine.IsUsed())
			{
				cout<<"Turing Machine status: Not yet used on a string\n";
			}
			else
			{
				if(!machine.IsOperating())
				{
					cout<<"Turing Machine status: Not running on a string currently\n";
				}
				else
				{
					cout<<"Turing Machine Status: Running on an input string\n";
				}

				cout<<"Last String used: "<<machine.InputString()<<endl;
				if(machine.IsRejectedInputString())
				{
					cout<<"Status of last string: Rejected\n";
				}
				else if(machine.IsAcceptedInputString())
				{
					cout<<"Status of last string: Accepted\n";
				}
				else
				{
					cout<<"Status of last string: Currently running\n";
				}
				cout<<"Number of transitions to arrive at status: "<<machine.TotalNumberOfTransitions()<<"\n";
			}
		}

		else if(userInput == "T")
		{
			if(showHelp)
			{
				cout<<"\nEnter an integer, or hit \"enter\" to not change current setting\n";
			}

			cout<<"\nSelect max number of cells to show on the isntantaneous description <Current: "<<numCellsShown<<">: ";

			string changeNum;
			getline(cin, changeNum);
			cout<<endl;
			bool number = true;

			for(int i = 0; i < (int)changeNum.length(); i++)
			{
				if(!isdigit(changeNum[i]))
				{
					number = false;
				}
			}

			if(changeNum == "")
			{
				//Do nothing
			}
			else if(number)
			{
				numCellsShown = atoi(changeNum.c_str());
				cout<<"\nNumber of cells to show in the instantaneous description "<<numCellsShown<<endl;;
			}
			else
			{
				cout<<"\nError: Requires an integer value.\nSetting unchanged"<<endl;
			}
		}

		else if(userInput == "D")
		{
			if(showHelp)
			{
				cout<<"\nEnter the number of the string to remove, or hit \"enter\" to not change input string list\n";
			}

			if(inputList.size() == 0)
			{
				cout<<"\nNo strings to delete from the list\n";
			}
			else
			{
			cout<<"\nSelect number of input string to remove: ";

			string changeNum;
			getline(cin, changeNum);
			cout<<endl;
			bool number = true;
			int index;
			if(changeNum == "")
			{
				//do nothing
			}
			else
			{
				for(int i = 0; i < (int)changeNum.length(); i++)
				{
					if(!isdigit(changeNum[i]))
					{
						number = false;
					}
				}
				if(number)
				{
					index = atoi(changeNum.c_str());
					index--;
					if((index > (int)inputList.size()) || (index < 0))
					{
						cout<<"\nError: Integer needs to be between 1 and "<<inputList.size()<<endl;
					}
					else
					{
						vector<string> temp;
						for(int i = 0; i < (int)inputList.size(); i++)
						{
							if(i != index)
							{
								temp.push_back(inputList[i]);
							}
							else
							{
								listChange = true;
								cout<<"\nRemoved "<<inputList[i]<<" from the input string list\n";
							}
						}
						inputList.clear();
						for(int i = 0; i < (int)temp.size(); i++)
						{
							inputList.push_back(temp[i]);
						}
					}
				}
				else
				{
					cout<<"\nError: Requires an integer value.\nInput list unchanged"<<endl;
				}
			}
			}
		}

		else
		{
			cout<<"\n Error: Unrecognized command\n";
			if(!showHelp)
			{
				cout<<"\nType \"H\" to enable help and show the list of commands\n";
			}
		}

		//Get next command!

		if(showHelp == true)
		{
			cout<<"\n";
			cout<<"<D>elete      Delete input string from list\n";
			cout<<"E<x>it        Exit the application\n";
			cout<<"<H>elp        Toggle to help user with prompts or not\n";
			cout<<"<I>nsert      Insert input string into list\n";
			cout<<"<L>ist        List all of the available input strings\n";
			cout<<"<Q>uit        Quit operation of Turing Machine on current input string\n";
			cout<<"<R>un         Run the Turing Machine on input string\n";
			cout<<"S<e>t         Set the maximum number of transitions to\n";
			cout<<"              perform each time \"Run\" is called\n";
			cout<<"Sho<w>        Show status of the Turing Machine application\n";
			cout<<"<T>runcate    Truncate instatnaneous descriptions\n";
			cout<<"<V>iew        View the information of the Turing Machine\n";
		}

		cout<<"\nCommand: ";
		getline(cin, userInput);

		for(int i = 0; i < (int) userInput.length(); i++)
		{
			userInput[i] = toupper(userInput[i]);
		}
	}

	//if input list changed, write to string list
	if(listChange)
	{
		ofstream outputFile(strFile.c_str());
		if(outputFile.is_open())
		{
			for(int i = 0; i < (int) inputList.size(); i++)
			{
				outputFile<<inputList[i]<<endl;
				if(inputList[i] == "")
				{
					outputFile<<"\\"<<endl;
				}
			}
			cout<<"\nInput string file \""<<strFile<<"\" overwritten correctly\n";
		}
		else
		{
			cout<<"\nError overwriting input string file. Input string list not saved\n";
		}
	}

	return success;
}
