//
//  blockControl.h
//  a5Second
//
//  Created by Felix Chen on 2014-07-21.
//  Copyright (c) 2014 Felix Chen. All rights reserved.
//
//  Description: This class is responsible for controlling all movements of a
//  block, including moving right, left and down, droping, rotating. It's
//  also responsible for obtaining the next block once the current block is
//  droped and updateing the score. Since this class contains a pointer to
//  levelControll object. It is also responsible for passing the command to
//  change levels.

#ifndef __a5Second__blockControl__
#define __a5Second__blockControl__

#include <iostream>
#include "grid.h"
#include "block.h"
#include "displayControl.h"
#include "levelControl.h"
#include <map>

class BlockControl{
    
    Grid *g; // the grid object representing the board
    Block *currentBlock; // current block that the user is controlling
    Block *nextBlock; // the next block coming up
    DisplayControl *theDisplay; // an displayControl object that is responsible for display the game board
    LevelControll *levelctrl; // levelControll is responsible for creating block objects according to the current level the game is in
    bool isOver; // whether the game is over
    int score; // track the score
    int blockSequence; // the sequence number of current block. The first block's sequence number is 1, the second block is 2
    std::map<int, int> fallenBlock; //first int is block sequence, second int is the level in which the block was created.
    
public:
    
    BlockControl(DisplayControl *dp, std::string fileName, int startLevel, int seed);// initialize the blockControl
    void setCurrentBlock(Block *b); // set current block to b. if b cannot be placed, set isOver to true. The notify the display
    bool checkMovable(int dir); // check whether the block can move one unit to the specified direction
    void moveNorth(int times); // move upwards in number of units specified by times
    void moveSouth(int times); // move downwards in number of units specified by times
    void moveWest(int times); // move left in number of units specified by times
    void moveEast(int times); // move right in number of units specified by times
    bool checkRotatable(std::string dir); // check whether the block can rotate one unit in the specified direction
    void rotateCW(int times); // rotate the block clockwise in number of times specified by times
    void rotateCCW(int times); // rotate the block counterclockwise in number of times specified by times
    void drop(); // drop the block
    void levelup(int times); // increase the level by one
    void leveldown(int times); // decrease the level by one
    bool getState(); // return whether the game has ended or not
    void showDisplay(); // call the displayControl objects << operator display the game
    void displayNextBlock(); // display the next block
    int getLevel(); // get the current level
    int getScore(); // get the current score
    void restart(); // restart the game, reset all relevant objects and fields
    void setSeed(int seed); // set the seed of rand()
    ~BlockControl();
};

#endif /* defined(__a5Second__blockControl__) */
