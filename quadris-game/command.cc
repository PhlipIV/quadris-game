//
//  command.cpp
//  a5Second
//
//  Created by Felix Chen on 2014-07-22.
//  Copyright (c) 2014 Felix Chen. All rights reserved.
//

#include "command.h"

// initialize the array of proper commands
std::string Command::properCommand[] = {"left","right","down","clockwise","counterclockwise","drop","levelup","leveldown","restart", "renameCmd"};

Command::Command(): timesOfExecution(1), errorOccurred(true), errorCause("No Command Received"), commandReceived(""), validCmd(""){
    
    // initialize the mapping between user's command and the proper command
    commandList["left"] = "left";
    commandList["right"] = "right";
    commandList["down"] = "down";
    commandList["clockwise"] = "clockwise";
    commandList["counterclockwise"] = "counterclockwise";
    commandList["drop"] = "drop";
    commandList["levelup"] = "levelup";
    commandList["leveldown"] = "leveldown";
    commandList["restart"] = "restart";
    commandList["renameCmd"] = "renameCmd";
}


void Command::processCommand(std::string cmd){
    
    std::vector<int> numHolder; // vector to hold the number seperated from the text input
    errorOccurred = false;
    
    // seperate all prefixing digits from the input text
    // the loop ends as soon as it hits a char
    while ( true ) {
        char temp = cmd[0];
        int i = temp - '0';
        if ((i >= 0) && (i <= 9)) {
            numHolder.push_back(i);
            cmd.erase(cmd.begin());
        }
        else{
            break;
        }
    }
    
    // If there is any prefixing number, reconstruct the number from the digits in
    // numHolder
    if (numHolder.size() != 0) {
        timesOfExecution = 0;
        for (int i = 0; i < numHolder.size(); i++) {
            timesOfExecution += numHolder[i] * pow(10, numHolder.size()-i-1);
        }
    }
    // else set the number of execution to 1
    else{
        timesOfExecution = 1;
    }
    checkAutocompletion(cmd);
}


void Command::checkAutocompletion(std::string cmd){
    
    int possibleCmd = 0; // number of  potential commands
    std::string potentialCmd = ""; // holds the matching proper command
    
    // loop through the command list and find all possible match
    std::map<std::string, std::string>::iterator it;
    for (it = commandList.begin(); it != commandList.end(); it++) {
        std::string temp  = it->first;
        // if a user command is a potential match, increment the possibleCmd count
        // then update the potentialCmd
        if (cmd == temp.substr(0,cmd.length())) {
            potentialCmd = it->second;
            possibleCmd++;
        }
    }
    
    // If no potential match is found
    if (possibleCmd == 0) {
        errorOccurred = true;
        errorCause = "Command not found";
    }
    // If multiple match is found
    else if (possibleCmd > 1){
        errorOccurred = true;
        errorCause = "Ambiguous";
    }
    // If only once matching is found
    else if (possibleCmd == 1){
        errorOccurred = false;
        validCmd = potentialCmd;
    }
}


int Command::getTimesOfExecute(){
    
    return timesOfExecution;
}


std::string Command::getValidCmd(){
    
    // if an error occurred, return the error message
    if (errorOccurred) {
        return errorCause;
    }
    else{
        return validCmd;
    }
}


std::string Command::renameCommand(std::string newcmd, std::string oldcmd){
    
    std::string actualCmd; // hold the proper command that the oldcmd maps to
    std::map<std::string, std::string>::iterator it;
    bool cmdfound = false;
    
    // loop through to find the oldcmd
    for (it = commandList.begin(); it != commandList.end(); it++) {
        if (it->first == oldcmd) {
            actualCmd = it->second;
            cmdfound = true;
            break;
        }
    }
    
    if (cmdfound) {
        commandList.erase(oldcmd);
        commandList[newcmd] = actualCmd;
        return "Successfully renamed";
    }
    else{
        return "Command not found";
    }
}


std::string Command::getProperCmd(int index){
    
    return properCommand[index];
}



