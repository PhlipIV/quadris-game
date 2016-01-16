//
//  quadris.cpp
//  a5Second
//
//  Created by Felix Chen on 2014-07-23.
//  Copyright (c) 2014 Felix Chen. All rights reserved.
//

#include "quadris.h"

Quadris *Quadris::instance = 0; // set the instance to null at first


Quadris *Quadris::getInstance(bool isTextOnly, std::string fileName, int initialLevel, int seed){
    
    if (!instance) {
        instance = new Quadris(isTextOnly, fileName, initialLevel, seed);
        atexit(cleanup);
    }
    
    return instance;
}


void Quadris::cleanup(){
    
    delete instance;
}


Quadris::Quadris(bool isTextOnly, std::string fileName, int initialLevel, int seed): score(0), highestScore(0){
    
    // initialize all necessary objects
    cmd = new Command();
    theDisplay = new DisplayControl(isTextOnly);
    blockControl = new BlockControl(theDisplay, fileName,initialLevel, seed);
    currentLevel = blockControl->getLevel();
}


void Quadris::runGame(){
    
    std::string s; // string holding user input
    updateDisplay(); // show the display
    
    
    // Enter game cycle, it runs as long as game is not ended or eof encountered
    while (!blockControl->getState() && std::cin >> s) {
        cmd->processCommand(s); // process the user input
        std::string cmdMessage = cmd->getValidCmd(); // get the proper command
        int repeatTimes = cmd->getTimesOfExecute(); // get the number of repeating time
        // compare the proper command obtained with the proper commands in command class to
        // determine what action to carry out
        if (cmdMessage == cmd->getProperCmd(0)) {
            blockControl->moveWest(repeatTimes);
        }
        else if (cmdMessage == cmd->getProperCmd(1)){
            blockControl->moveEast(repeatTimes);
        }
        else if (cmdMessage == cmd->getProperCmd(2)){
            blockControl->moveSouth(repeatTimes);
        }
        else if (cmdMessage == cmd->getProperCmd(3)){
            blockControl->rotateCW(repeatTimes);
        }
        else if (cmdMessage == cmd->getProperCmd(4)){
            blockControl->rotateCCW(repeatTimes);
        }
        else if (cmdMessage == cmd->getProperCmd(5)){
            blockControl->drop();
            
            // if a block is dropped, update the score
            score = blockControl->getScore();
            if (score > highestScore) {
                highestScore = score;
            }
        }
        else if (cmdMessage == cmd->getProperCmd(6)){
            blockControl->levelup(repeatTimes);
            currentLevel =  blockControl->getLevel();
        }
        else if (cmdMessage == cmd->getProperCmd(7)){
            blockControl->leveldown(repeatTimes);
            currentLevel =  blockControl->getLevel();
        }
        else if (cmdMessage == cmd->getProperCmd(8)){
            restart();
        }
        else if (cmdMessage == cmd->getProperCmd(9)){
            std::string oldcmd;
            std::string newcmd;
            std::cout << "Enter the command that you want to rename:" << std::endl;
            std::cin >> oldcmd;
            std::cout << "Enter the new name that you want for the command" << std::endl;
            std::cin >> newcmd;
            std::cout << cmd->renameCommand(newcmd, oldcmd) << std::endl;
        }
        else{ // if no matching command is found, then an error occurred, display the error
              // message
            std::cout << cmdMessage << std::endl;
        }
        updateDisplay(); // update the display after each cycle
    }
}


void Quadris::updateDisplay(){
    
    // game stat area of the text display
    std::cout << "Level:      " << currentLevel << std::endl;
    std::cout << "Score:      " << score << std::endl;
    std::cout << "Hi Score:   " << highestScore << std::endl;
    std::cout << "----------" << std::endl;
    blockControl->showDisplay();
    std::cout << "----------" << std::endl;
    std::cout << "Next:" << std::endl;
    
    /*****************************************************/
    // update the game stat area of the graphical display
    // convert all stats from int to string
    // then call the notify function in displayControl
    std::string levelStr;
    std::string scoreStr;
    std::string hiscoreStr;
    std::ostringstream convert;
    
    convert << currentLevel;
    levelStr = convert.str();
    convert.str("");
    
    convert << score;
    scoreStr = convert.str();
    convert.str("");
    
    
    convert << highestScore;
    hiscoreStr = convert.str();
    convert.str("");
    
    theDisplay->notify(levelStr, scoreStr, hiscoreStr);
    blockControl->displayNextBlock();
    /*****************************************************/
}


void Quadris::restart(){
    
    blockControl->restart();
    score = blockControl->getScore();
    currentLevel = blockControl->getLevel();
}


Quadris::~Quadris(){
    
    delete cmd;
    delete blockControl;
}