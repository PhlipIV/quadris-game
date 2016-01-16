//
//  command.h
//  a5Second
//
//  Created by Felix Chen on 2014-07-22.
//  Copyright (c) 2014 Felix Chen. All rights reserved.
//
//  This class implements the command processing function.

#ifndef __a5Second__command__
#define __a5Second__command__

#include <iostream>
#include <map>
#include <vector>
#include <sstream>
#include <math.h>

class Command{
    
    static std::string properCommand[]; // array of proper commands that would trigger funtions
    std::map<std::string, std::string> commandList; // a dictionary that tracks the mapping between the user's command and the actual command
    int timesOfExecution; //  number of times a command is executed
    std::string commandReceived; // text input received
    std::string validCmd; // processed text that is to be compared with the proper commands
    bool errorOccurred; // whether an error has occurred
    std::string errorCause; // the error message
    void checkAutocompletion(std::string cmd); // check whether a text input has an autocompletion matching
    
public:
    
    Command();
    std::string renameCommand(std::string newcmd, std::string oldcmd); // rename a command
    void processCommand(std::string cmd); // process a input text(seperate the text from number at the front is there is any)
    int getTimesOfExecute(); // get the number of execution
    std::string getValidCmd(); // get the processed text
    std::string getProperCmd(int index); // get the proper command to compare
};

#endif /* defined(__a5Second__command__) */
