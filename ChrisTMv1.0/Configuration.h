/*
    Module: Configuration
    File: Configuration.h
    Application: TuringMachineApplication
    Language: C++
    Computer: Macbook Air
    Operating System: Ubuntu 14.10
    Course: CptS 322
    Author: Christopher Wilkins
    Date: 5/5/2014
    Description:
    Configuration.h contains the code declaration and implementation for Configuration module.
    The Configuration class stores the configuration settings for the Turing Machine Application.
    These settings are: Help on/off, maximum number of transitions to perform, and maximum truncation width.
*/
#ifndef CONFIGURATION_H
#define CONFIGURATION_H

class Configuration
{
    private:
    int truncation;
    bool helpOn;
    int numTransitions;

    public:
    /*
        The Configuration method is the constructor for the Configuration class. It initializes the
        configuration settings to their default values. These values are truncation: 3, HelpOn: false,
        NumTransitions: 1.
    */
    Configuration() : truncation(3), helpOn(false), numTransitions(1) {}

    /*
        The Truncation method is a getter method for the truncation attribute. It returns the maximum
        number of cells to be shown to the left and right of the tape head when the Turing Machine Application
        displays and instantaneous description as an integer.
    */
    int Truncation() { return truncation; }

    /*
        The Help method is a getter method for the HelpOn attribute. It returns whether or not help messages
        are turned on within the Turing Machine Application as a boolean. If it returns true if help messages
        are currently turned on, and returns false if help messages are currently turned off.
    */
    bool Help() { return helpOn; }

    /*
        The NumberOfTransitions method is a getter for the NumTransitions attribute. It returns the maximum
        number of transitions that the Turing Machine Application performs each time a run command is executed
        as an integer.
    */
    int NumberOfTransitions() { return numTransitions; }

    /*
        The SetTruncation method is a setter method for the truncation attribute. It accepts an integer parameter
        called truncatinCells and sets the truncation attribute with this value.
    */
    void SetTruncation(int truncationCells) { truncation = truncationCells; }

    /*
        The HelpOn method sets the HelpOn boolean attribute to true. This means that it turns on help messages
        in the Turing Machine Application.
    */
    void HelpOn() { helpOn = true; }

    /*
        The HelpOff method sets the HelpOn boolean attribute to false. This means that it turns off help messages
        in the Turing Machine Application.
    */
    void HelpOff() { helpOn = false; }

    /*
        The ToggleHelp method toggles the HelpOn boolean attribute. If the HelpOn attribute is currently set to
        true, it sets it to false, turning off help messages in the application. If the HelpOn attribute is currently
        set to false, it sets it to true, turning on help messages in the application.
    */
    void ToggleHelp() { helpOn = !helpOn; }

    /*
        The SetNumberOfTransitions method is a setter method for the NumTransitions integer attribute. It accepts an
        integer parameter called transitions and sets the NumTransitions attribute to this value.
    */
    void SetNumberOfTransitions(int transitions) { numTransitions = transitions; }
};

#endif // CONFIGURATION_INCLUDED
