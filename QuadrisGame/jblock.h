//
//  jblock.h
//  a5Second
//
//  Created by Felix Chen on 2014-07-21.
//  Copyright (c) 2014 Felix Chen. All rights reserved.
//

#ifndef __a5Second__jblock__
#define __a5Second__jblock__

#include <iostream>
#include "block.h"
#include "window.h"

class Jblock: public Block{
    
    // this array must be be ordered as N:0 E:1 S:2 W:3
    
    char ***blockList;// 4x4x4 array of char representing all possible facings of a block
    char **currentBlock;// pointer to an element in the blockList indicating the block's current facing
    int width, height;// width and heigh of the smallest rectange encloseing the block
    int color;
    
    
public:
    Jblock();
    void setCurrentBlock(int dir);
    char getCharAt(int x, int y);
    void rotateCW();
    void rotateCCW();
    int getWidth();
    int getHeight();
    int getColor();
    ~Jblock();
    
};

#endif /* defined(__a5Second__jblock__) */
