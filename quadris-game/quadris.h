//
//  quadris.h
//  a5Second
//
//  Created by Felix Chen on 2014-07-23.
//  Copyright (c) 2014 Felix Chen. All rights reserved.
//

#ifndef __a5Second__quadris__
#define __a5Second__quadris__

#include <iostream>
#include "grid.h"
#include "blockControl.h"
#include "command.h"
#include "levelControl.h"
#include "displayControl.h"
#include <sstream>
#include <cstdlib>


class Quadris{
    
    static Quadris *instance; // the only instance of Quadris object
    static void cleanup(); // clean up at the end of the program
    Quadris(bool isTextOnly, std::string fileName, int initialLevel, int seed); // constructor the Quadris
    int score; // user's score
    int highestScore; // the highest score
    int currentLevel; // current level
    Command *cmd; // pointer to command object
    BlockControl *blockControl; // pointer to blockControl object
    DisplayControl *theDisplay; // pointer to theDisplay object
    
public:
    static Quadris *getInstance(bool isTextOnly, std::string fileName, int initialLevel, int seed); // return an instance of Quadris
    void runGame(); // start the game
    void updateDisplay(); // update the display
    void restart(); // restart the game
    ~Quadris();
};
#endif /* defined(__a5Second__quadris__) */
