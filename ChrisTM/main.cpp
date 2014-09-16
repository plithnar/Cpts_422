/*
    Module: Main
    File: main.cpp
    Application: TuringMachineApplication
    Language: C++
    Computer: Macbook Air
    Operating System: Ubuntu 14.10
    Course: CptS 322
    Author: Christopher Wilkins
    Date: 5/5/2014
    Description:
    main.cpp contains the code implementation for main module.
    The Main class contains the methods that the user interacts with
    to use the Turing Machine Application.
*/
#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <climits>
#include "TuringMachine.h"
#include "Configuration.h"

using namespace std;

/*
    The HelpCommand method uses the Configuration object to check whether
    or not the help configuration setting of the application is enabled.
    If it is, it displays a list of commands available in the application
    and help text regarding each one.
*/
void CommandHelp(Configuration& config)
{
    if (config.Help())
    {
        cout << endl;
        cout << "(D)elete\tDelete input string from list"  << endl;
        cout << "E(x)it\t\tExit application" << endl;
        cout << "(H)elp\t\tHelp user with prompts" << endl;
        cout << "(I)nsert\tInsert a input string into list" << endl;
        cout << "(L)ist\t\tList input strings" << endl;
        cout << "(Q)uit\t\tQuit operation of the Turing Machine on input string" << endl;
        cout << "(R)un\t\tRun the Turing Machine on an input string" << endl;
        cout << "S(e)t\t\tSet maximum number of transitions to perform" << endl;
        cout << "(T)runcate\tTruncate instantaneous description" << endl;
        cout << "Sho(w)\t\tShow status of application" << endl;
        cout << "(V)iew\t\tView Turing Machine" << endl << endl;
    }
}

/*
    The show method displays detailed information about the Turing Machine application
    and the currently loaded turing machine definition. It displays the applications author,
    version number, class name, instructor, and date of creation. It also shows the name of
    the current turing machine definition, the status of the turing machine (whether or not
    t is or has run on an input string), the number of transitions performed (if any), and
    finally the configuration settings of the Turing Machine. It uses the tm parameter to
    get information about the turing machine. The tmDef string is the name of the current
    turing machine. The config parameter stores the information about the configuration settings.
*/
void Show(TuringMachine& tm, string tmDef, Configuration& config)
{
    cout << endl;
    if (config.Help())
    {
        cout << "The Sho(w) command shows information about the application, the currently loaded " << endl
            << "turing machine defintion, and the current configuration settings." << endl << endl;
    }
    cout << "Turing Machine Application" << endl;
    cout << "\tVersion: 1.0" << endl;
    cout << "\tAuthor: Chris Wilkins" << endl;
    cout << "\tSpring 2014" << endl;
    cout << "\tCourse: Computer Science 322 - Software Engineering Principles" << endl;
    cout << "\tProfessor Neil Corrigan" << endl << endl;

    cout << "Application Status" << endl;
    cout << "\tTuring Machine Name: " << tmDef << endl;
    cout << "\tStatus: ";
    if (tm.IsOperating())
    {
        cout << "The turing machine is running on " << tm.InputString() << "." << endl;
    }
    else if (tm.IsUsed())
    {
        cout << "The turing machine is not currently running on an input string." << endl;
        if (tm.IsAcceptedInputString())
        {
            cout << "\t" << tm.InputString() << " was accepted in " << tm.TotalNumberOfTransitions()
                << " transitions" << endl;
        }
        else
        {
            cout << "\t" << tm.InputString() << " was rejected in " << tm.TotalNumberOfTransitions()
                 << " transitions" << endl;
        }
    }
    else
    {
        cout << "Turing machine has never been run on an input string." << endl;
    }
    cout << "\tTotal number of transitions performed: " << tm.TotalNumberOfTransitions() << endl;

    cout << endl;
    cout << "Configuration" << endl;
    cout << "\tHelp: ";
    if (config.Help()) cout << "On" << endl;
    else cout << "Off" << endl;
    cout << "\tMaximum transitions: " << config.NumberOfTransitions() << endl;
    cout << "\tTruncation: " << config.Truncation() << endl;
    cout << endl;
}

/*
    The list method shows the list of input strings that are currently loaded into the Turing
    Machine application. It displays an enumerated list (beginning at 1) of all input strings
    is displayed. This list consists of all input strings that have either been read from the
    input string file or added by the user by using the “insert” command. This list is read from
    the inputStrings stringVector parameter. The number of each input string represents the number
    that the input string is accessed by when using the “run” and “delete” commands. The method
    retrieves the value of the help command from the config paramter. It uses this to determine
    whether or not help is displayed.
*/
void List(vector<string>& inputStrings, Configuration& config)
{
    cout << endl;
    if (config.Help())
    {
        cout << "The (L)ist command displays input strings currently in the application's input string list. " << endl
            << "These are the strings that have been inserted either by the (I)nsert command or the input string file. " << endl
            << "The index of each item is the index used by the run and delete commands." << endl << endl;
    }
    for (unsigned int i=0; i<inputStrings.size(); i++)
    {
        if (inputStrings[i] == "")
        {
            cout << i+1 << ". " << "\\" << endl;
        }
        else
            cout << i+1 << ". " << inputStrings[i] << endl;
    }
    cout << endl;
}

/*
    The insert method allows the user to enter a new input string. The method will prompt for an input
    string, which reads “Enter input string: ”. The user must then type the input string that he or
    she wishes to enter. After typing the input string, the user will press enter on their keyboard to
    submit the input string for validation.
	The Insert method validates the input string by checking to see if each character in the input string
	is present in the input alphabet of the Turing Machine, as defined in the Turing Machine definition file.
	The input string is validated to ensure that it does not contain reserved characters or characters that are
	not in the turing machine's input alphabet. This method uses the tm parameter to check whether or not the
	input string entered by the user is valid. If an empty input string is entered (ie pressing “enter” at the
	input string prompt without typing anything else), the method will return instantly.
	If the input string passes validation, it will be inserted into the Turing Machine and a positive message
	affirming that it has been added will appear onscreen. This message is: “Input string has successfully been
	inserted.” and the input string will be inserted into the inputStrings stringVector. If the input string does
	not pass validation, the user will be given a negative message notifying them that it is an invalid input string,
	and the input string will not be inserted into the input string list. This message is “Input string was not valid
	and has not been inserted.”
	The Insert method uses the config parameter to determine whether or not it should display help information before
	prompting the user for an input string.
*/
void Insert(vector<string>& inputStrings, TuringMachine& turingMachine, Configuration& config)
{
    cout << endl;
    if (config.Help())
    {
        cout << "The (I)nsert command allows you to insert an input string into this application's input string list. " << endl
            << "To use this command, enter a valid input string consisting of characters in the turing machine defintion's " << endl
            << "input alphabet. The application will validate this string and attempt to insert it into the input string list."
            << endl << endl;
    }
    cout << "Insert input string: ";
    string inputString("");
//    cin.clear();
//    cin.ignore(INT_MAX, '\n');
    getline(cin, inputString);
    if (inputString.empty())
        return;
    if (inputString == "") return;
    if (inputString == "\\") inputString = "";
    if (turingMachine.IsValidInputString(inputString))
    {
        for (unsigned int i=0; i<inputStrings.size(); i++)
        {
            if (inputStrings[i] == inputString)
            {
                if (inputString == "") inputString = "\\";
                cout << inputString << " is already in the input string list." << endl << endl;
                return;
            }
        }
        inputStrings.push_back(inputString);
        cout << "Inserted " << inputString << endl << endl;
    }
    else if (inputString == "")
    {
        inputStrings.push_back("");
        cout << "Inserted \\" << endl << endl;
    }
    else
    {
        cout << "Invalid input string." << endl << endl;
    }
}

/*
    The delete method allows the user to delete an input string from the application. The user will be prompted for
    the index of the input string to delete. This prompt is “Delete input string index: ”. If the user types nothing
    and presses enter at this prompt, the method will immediately exit. The index is the number of the input string
    as shown in the List command. Once the user enters an integer for the input string, the application will then
    validate the index to check to see if it is correct. If the index entered is greater than the maximum number of
    strings in the input string list, or if it is less than 0, or the index entered is not an integer, then a message
    will be displayed notifying the user that he or she entered an invalid index number. The message displayed will be
    “Invalid input string index.” If the index entered passes validation, the input string will be removed from the
    inputStrings stringVector. The inputStrings stringVector contains all of the input string of stored in the application.
    A message will appear on the screen informing the user that the input string has been deleted. This message will be
    “Input string [input string] has been removed from the input string list.” The config parameter is used to check
    whether or not help messages should be displayed before prompting the user for an input string index.
*/
void Delete(vector<string>& inputStrings, Configuration& config)
{
    cout << endl;
    if (config.Help())
    {
        cout << "Enter the index of the input string that you wish " << endl
            << "to delete. The index of the all input strings stored in " << endl
            << "this application can be found by using the (L)ist command."
            << endl << endl;
    }
    if (inputStrings.size() == 0)
    {
        cout << "Input string list is empty. Nothing to delete." << endl << endl;
        return;
    }
    cout << "Delete input string at index: ";
    string input("");
    stringstream inputConv;
    int index = 0;
//    cin.clear();
//    cin.ignore(INT_MAX, '\n');
    getline(cin, input);
    if (input.empty())
        return;
    inputConv << input;
    inputConv >> index;
    string inputString("");
    if ((index == 0 && input != "0") || index <= 0 || (unsigned int) index > inputStrings.size())
    {
        cout << "Invalid input string index." << endl << endl;;
    }
    else
    {
        inputString = inputStrings[index-1];
        inputStrings.erase(inputStrings.begin() + (index-1));
        if (inputString == "") inputString = "\\";
        cout << "Deleted " << inputString << endl << endl;
    }
}

/*
    The set method allows the user to set the maximum transitions to run configuration setting of the Turing
    Machine application. This setting is stored in the config parameter. This command allows the user to change
    the maximum number of transitions configuration setting. On entering this command, the user will be prompted
    for the maximum transitions to perform. If the user presses enter at this prompt without entering anything,
    he or she will be taken immediately back to the command prompt without further input. It will also show the
    current value that this configuration setting is set to. This prompt is “Maximum number of transitions to be
    performed (currently: [current maximum transitions]: ”. At this prompt, the user will enter a number which is
    the maximum number of transitions to perform. The input from the user will then be checked to ensure that it
    is a valid number of transitions that can be performed. The input to this prompt form the user consists of an
    integer greater than 1. If the user entered a number less than 1, or anything that is not an integer, the setting
    will not be changed and the user will receive a message informing he or she of this. The message displayed will be:
    “That is an invalid number of transitions.” If the user enters a value that is equal to the current number value of
    the configuration setting, no message will be displayed and the user will be taken immediately back to the command
    prompt without requiring any further input. If the input passes validation, the maximumtransitions setting will be
    changed in the config parameter and a message will be displayed notifying the user of this. The message displayed is:
    “Maximum number of transitions to perform has been changed to [user input]”. The set method also uses the config parameter
    to determine whether or not it should display a help message before the maximum number of transitions prompt.
*/
void Set(Configuration& configuration)
{
    cout << endl;
    if (configuration.Help())
    {
        cout << "The S(e)t command allows you to change the number of " << endl
            << "transitions that the Turing Machine executes per " << endl
            << "use of the Run command. To use this command, enter " << endl
            << "the number of transitions  as a positive integer at the prompt below." << endl << endl;
    }
    cout << "Maximum transitions (current = " <<  configuration.NumberOfTransitions() << "): ";
    string input("");
//    cin.clear();
//    cin.ignore(INT_MAX, '\n');
    getline(cin, input);
    if (input.empty())
        return;
    int value = 0;
    stringstream readInt(input);
    readInt >> value;
    if (value < 1)
    {
        cout << "Invalid number of transitions." << endl << endl;
    }
    else
    {
        configuration.SetNumberOfTransitions(value);
        cout << "Maximum transitions set to " << value << endl << endl;
    }
}

/*
    The truncate method allows the user to change the configuration setting for the maximum number of tape
    characters to be displayed to the left and the right of the tape head when an instantaneous description
    is displayed. This configuration setting is stored in the config parameter. The user will be prompted for
    the maximum number of transitions to perform. It will also show the current value that this configuration
    setting is set to. The prompt displayed is: “Number of characters in instantaneous description (current=[current number]):
    ” The input from the user to this prompt consists of an integer representing the number of characters that should be
    shown to the left and the right of the tape head on the instantaneous description. After the user enters this
    value, it will be validated to ensure it is a valid number of characters to be displayed. If the user enters
    a number less than 0 or enters non-numeric characters, the setting will not be changed and the user will be
    notified that their input is invalid. This message is: “Invalid truncation value.” If the user enters a value
    that is equal to the current number value of the configuration setting, no message will be displayed and the
    user will be taken immediately back to the command prompt without requiring any further input. If the input
    from the user passes validation, the truncation setting in the config parameter will be changed and the user
    will be informed that is was changed. This message is: “Truncation value has been changed to [user input].”
    The Truncate command also uses the config parameter to determine whether or not it should display a help
    message before the truncate prompt.
*/
void Truncate(Configuration& configuration)
{
    cout << endl;
    if (configuration.Help())
    {
        cout << "The (T)runcate command allows you to change the number of cells that are shown to the left and " << endl
            << "the right of the tape head in the instantaneous description. To use this command, " << endl
            << "enter the number of cells to display as a positive integer at the prompt below." << endl << endl;
    }
    cout << "Show cells in instantaneous description (current = " <<  configuration.Truncation() << "): ";
    string input("");
//    cin.clear();
//    cin.ignore(INT_MAX, '\n');
    getline(cin, input);
    if (input.empty())
        return;
    int value = 0;
    stringstream readInt(input);
    readInt >> value;
    if (value < 1)
    {
        cout << "Invalid truncation length." << endl;
    }
    else
    {
        configuration.SetTruncation(value);
        cout << "Truncation length set to " << value << endl;
    }
    cout << endl;
}

/*
    The View method displays the current turing machine definition. Once the command is entered at the
    command prompt, no further information is requested from the user. This is the definition of the
    Turing Machine as given by the Turing Machine Definition file. The method using the tm parameter
    to display the definition. It displays the description of the turing machine, a list of all states,
    the input alphabet (sigma), the tape alphabet (gamma), and a list of final states, the blank character,
    and a starting state. The View method uses the config parameter to determine whether or not it should
    display a help message before the definition.
*/
void View(TuringMachine& tm, Configuration& config)
{
    cout << endl;
    if (config.Help())
    {
        cout << "The (V)iew command displays the currently loaded turing machine definition. " << endl
            << "It displays the defintion as closely to the standard notation for a theoretical " << endl
            << "turing machine as possible." << endl << endl;
    }
    tm.ViewDefinition();
}


/*
    The run method will cause the turing machine to begin running on an input string. The tm parameter is
    the turing machine to run transitions on. The inputString stringVector parameter contains the list of
    the input string in the application. The config parameter is used to determine whether or not help messages
    should be displayed by the run method. It is also used to determine how many transitions the turing
    machine should run at a time, and how many characters should be shown to the left and the right of the
    ape head in the instantaneous description. If the turing machine is not currently running on an input string,
    the user will be prompted for additional information. The user is prompted for the index of the input string to
    run transitions on. The input string is given by the user as the index of the input string as shown on the listing
    of the List command. This index must be less than or equal to the number of input strings in the input string list
    and greater than zero. The input string index provided by the user is validated to ensure that it is a valid index.
    Once the user enters an integer for the input string, the application will then validate the index to check to see if
    it is correct. If the index entered is greater than the maximum number of strings in the input string list, or if it
    is less than 0, or the index entered is not an integer, then a message will be displayed notifying the user that he or
    she entered an invalid index number. The message displayed will be “Invalid input string index.” If the index entered
    passes validation, the input turing machine will begin running transitions on the input string. If the user has already
    began operation on the input string on a previous execution of the run method, the user will not be prompted for any
    information. The turing proceed will attempt to perform the maximum number of transitions as specified by the maximum
    number of transitions configuration setting.
	When the Turing Machine Application operates on a new input string, it must perform several states to begin operation.
	The turing machine loads the input string onto the tape. The turing machine then sets its current state to the initial
	state as defined in the turing machine definition file. The turing machine tracks the total number of transitions
	performed, so this value is reset to zero. The turing machine then begins to perform transitions. It attempts to
	perform as many transitions as are specified by the maximum number of transitions configuration setting.
	The turing machine performs transitions by reading the character on the tape at the tape head, looking for a
	transition from the current state for this tape character. If there is one, the turing machine writes the write
	character defined in the transition, switches to the transition's destination state, and moves the tape head in
	the direction specified by the transition. If there is not valid transition from the current state given the current
	character on the tape at the tape head, the turing machine will crash and the input string will be rejected. If the
	input string is rejected, a message will be displayed to the user: “Input string rejected in [transitions performed]”
	where “[transitions performed]” is the total number of transitions performed on the turing machine so far. If the turing
	machine reaches a halt state before the maximum number of transitions have occurred, a message will be displayed information
	the user that the input string has been accepted. This message should be “Input string accepted in [transitions performed]”.
	If the input string is not accepted or rejected by the time it has run the maximum number of transitions, nothing will be
	displayed to the user.
*/
void Run(TuringMachine& tm, vector<string>& inputStrings, Configuration& config)
{
    cout << endl;
    if (config.Help())
    {
        cout << "The (R)un command is how you run transitions on an input string. If the turing machine " << endl
            << "isn't currently running on an input string, it will first prompt for an index of an input string " << endl
            << "in the input string list. The input string index can be found using the List command. If the run command " << endl
            << "it will run the number of transitions specified by the maximum number of transitions configuration setting." << endl << endl
            << "When the application operates on an input string, it will show the instantaneous description before any transitions " << endl
            << "are performed, and then again after the specified number of transitions are performed. If the input string accepts " << endl
            << "or rejects the input string before the specified number of transitions has been reached, a message will inform you of this." << endl << endl;
    }
    if (inputStrings.size() == 0)
    {
        cout << "The input string list is empty." << endl <<
        "There are no strings for the turing machine to operate on." << endl << endl;
        return;
    }
    if (!tm.IsOperating())
    {
        cout << "Input string to run: ";
        string input("");
 //       cin.clear();
 //       cin.ignore(INT_MAX, '\n');
        getline(cin, input);
        if (input.empty())
            return;
        int value = 0;
        stringstream readInt(input);
        readInt >> value;
        if (value > 0 && (unsigned int) value < inputStrings.size())
        {
            tm.Initialize(inputStrings[value-1]);
        }
        else
        {
            cout << "Invalid input string index." << endl << endl;
            return;
        }
    }
    cout << tm.TotalNumberOfTransitions() << ". ";
    tm.ViewInstantaneousDescription(config.Truncation());
    tm.PerformTransitions(config.NumberOfTransitions());
    if (!tm.IsOperating())
    {
        if (tm.IsAcceptedInputString())
        {
            cout << tm.TotalNumberOfTransitions() << ". ";
            tm.ViewInstantaneousDescription(config.Truncation());
            tm.PerformTransitions(config.NumberOfTransitions());
            cout << "Input string accepted in " << tm.TotalNumberOfTransitions() << " transitions." << endl;
        }
        else
        {
            cout << "Input string rejected in " << tm.TotalNumberOfTransitions() << " transitions." << endl;
        }
    }
    else
    {
        cout << tm.TotalNumberOfTransitions() << ". ";
        tm.ViewInstantaneousDescription(config.Truncation());
    }
    cout << endl;
//    cout << "0. [s0]AABB" << endl;
//    cout << "1. X[s1]ABB" << endl << endl;
}

/*
    The quit method is used to stop the turing machine from running on an input string. When this command is entered,
    the turing machine will cease to run on the turing machine. This method calls the HaltOperation command on the tm
    parameter to halt operation on the turing machine. The total number of transitions that were performed will be
    displayed on the screen. If the Turing Machine is not currently running on an input string, a message will be
    displayed telling the user that nothing was quit. This message is: “The Turing Machine is not currently running
    on an input string.” The config parameter is used by the Quit method to determine whether or not it should display
    a help message before showing the halt operation text.
*/
void Quit(TuringMachine& tm, Configuration& config)
{
    if (tm.IsOperating())
    {
        tm.TerminateOperation();
        cout << endl << "Operation halted after " << tm.TotalNumberOfTransitions() << " transitions." << endl << endl;
    }
    else
    {
        cout << endl << "Turing machine is not currently running on an input string." << endl << endl;
    }
}

/*
    The ReadInputStringList method reads a list of input strings from a file. The name of the file to read the input
    strings from is specified by the fileName string parameter. The ReadInputStringList uses the tm TuringMachine
    parameter to determine whether or not each string in the list is valid. If an inputstring is valid, the string
    is added to the end of the inputStrings stringVector. The inputStrings stringVector parameter contains the list
    of all the input strings in the input string list.
*/
void ReadInputStringList(vector<string>& inputStrings, TuringMachine& turingMachine, string fileName)
{
    ifstream inputStringFile(fileName.c_str());
    if (!inputStringFile.good())
    {
        cout << "Could not open input string file." << endl;
        return;
    }

    string inputString("");
    while (getline(inputStringFile, inputString))
    {
        if (turingMachine.IsValidInputString(inputString))
        {
            for (unsigned int i=0; i<inputStrings.size(); i++)
            {
                if (inputStrings[i] == inputString)
                {
                    cout << inputString << " is a duplicate input string." << endl << endl;
                    return;
                }
            }
            inputStrings.push_back(inputString);
        }
        else if (inputString == "\\")
        {
            inputStrings.push_back("");
        }
        else
        {
            cout << inputString << " is an invalid input string." << endl << endl;
        }
    }
}

/*
    The WriteInputStringFile accepts a list of input strings as a stringVector. It writes this list to a file,
    the name of which is given by the fileName string parameter. Each element of the inputStrings StringVector
    becomes a line in the input string file. This method attempts to write the file. If it can write the file, it
    prints a message stating that it successfully wrote it. Otherwise, it prints out a message stating that it was
    not able to write the file.
*/
void WriteInputStringFile(vector<string> inputStrings, string fileName)
{
    ofstream inputStringFile(fileName.c_str());
    if (!inputStringFile.good())
    {
        cout << "Could not write input string file." << endl;
        return;
    }
    for (unsigned int i=0; i < inputStrings.size(); i++)
    {
        inputStringFile << inputStrings[i] << endl;
    }
    cout << "Input string file successfully written." << endl;
}

/*
    The ToggleHelp method toggles the state of the help configuration setting in the config parameter. It modifies
    the help setting in the config parameter. If help is currently off, it turns it on and displays a message stating
    that is was turned on. Otherwise, it turns it off and displays a message stating that it was turned off.
*/
void ToggleHelp(Configuration& config)
{
    config.ToggleHelp();
    if (config.Help())
    {
        cout << "Help messages have been turned on." << endl << endl;
    }
    else
    {
        cout << "Help messages have been turned off." << endl << endl;
    }
}

/*
    The Main method is the entry point for the Turing Machine Application. It initializes an object of the
    uring Machine class and passes into it a turing machine definition file as specified by the string argv.
    The argc parameter is checked to make sure that the user entered a name of a turing machine on the command
    line. The Main method reads the input string file and maintains a list of input strings. The Main method sets
    up the command prompt and accepts all the commands in the application. It calls the correct method for each command.
    It returns 0 or 1 as an integer. It returns 0 if the application exits successfully and returns 1 if the application
    does not exit successfully.
*/
int main(int argc, char** argv)
{
    if (argc < 2)
    {
        cout << "Proper usage of Turing Machine Simulator: ./tm [definitionFileName]";
        return 1;
    }

    Configuration config;
    vector<string> inputStrings;
    string defFile = argv[1];
    defFile += ".def";
    string inputStringFile = argv[1];
    inputStringFile += ".str";
    TuringMachine tm(defFile);
    if (!tm.IsValid()) return 1;
    ReadInputStringList(inputStrings, tm, inputStringFile);

    string input("");

    do
    {
        CommandHelp(config);
        string input="";
        cout << "Command: ";
        getline(cin, input);
        std::transform(input.begin(), input.end(), input.begin(), ::tolower);

        if (input.empty()) continue;
        if (input.size() > 1)
        {
            cout << "Invalid command." << endl << endl;
            continue;
        }

        switch (input[0])
        {
            case 'h':   // help
                ToggleHelp(config);
                break;
            case 'i':   // insert
                Insert(inputStrings, tm, config);
                break;
            case 'l':
                List(inputStrings, config); // List
                break;
            case 'd':   // delete
                Delete(inputStrings, config);
                break;
            case 'r':   // run
                Run(tm, inputStrings, config);
                break;
            case 'e':   // set
                Set(config);
                break;
            case 'w':   // show
                Show(tm, argv[1], config);
                break;
            case 'v':   // view
                View(tm, config);
                break;
            case 't':   // truncate
                Truncate(config);
                break;
            case 'q':   // quit
                Quit(tm, config);
                break;
            case 'x':   // exit
                WriteInputStringFile(inputStrings, inputStringFile);
                return 0;
                break;
            default:
                cout << "Invalid command." << endl << endl;
        }

    } while (input[0] != 'x');

    return 0;
}
