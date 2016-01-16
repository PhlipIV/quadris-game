//
//  levelControl.h
//  a5Second
//
//  Created by Felix Chen on 2014-07-21.
//  Copyright (c) 2014 Felix Chen. All rights reserved.
//
//  This class tracks level and generate random blocks in
//  accordance with the level

#ifndef __a5Second__levelControl__
#define __a5Second__levelControl__

#include <iostream>
#include "block.h"
#include "oblock.h"
#include "jblock.h"
#include "lblock.h"
#include "sblock.h"
#include "zblock.h"
#include "tblock.h"
#include "iblock.h"
#include <vector>
#include <fstream>
#include <cstdlib>


class LevelControll{
    
    // probability of block's appearance represented by its char's
    // number of appearance in the levelarray divided by the
    // array's size
    
    static char levelOneArray[]; // probability array for level one
    static char levelTwoArray[]; // probability array for level two
    static char levelThreeArray[]; // probability array for level three
    int currentlevel; // current level
    std::vector<char> defaultBlock; // vector holding the level zero block sequence
    int defaultBlockTrack; // index tracking the next block in level zero
    Block *createBlock(char type); // generate a block with type
    int const maximumLevel; // the maximum level allowed
public:
    
    LevelControll(std::string fileName, int startLevel);// constructor with no seed for random number
    LevelControll(std::string fileName, int startLevel, int seed);// constructor with seed for random number
    void levelup(); // increase the level by one
    void leveldown(); // decrease the level by one
    Block *getBlock(); // return a pointer to a randomly generated block
    int getlevel(); // get the current level
    void reset(); // reset the level
    void setSeed(int seed); // set the seed
};

#endif /* defined(__a5Second__levelControl__) */
