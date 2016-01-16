//
//  block.h
//  a5Second
//
//  Created by Felix Chen on 2014-07-20.
//  Copyright (c) 2014 Felix Chen. All rights reserved.
//
// This is the parent class for all blocks generated.
// It contains properties that are common among all blocks

#ifndef __a5Second__block__
#define __a5Second__block__

#include <iostream>

class Block{
    
    char blockType; // char indicating the type of the block
    int x, y; // x, y coordinates for the lower left corner of the block
    int direction; // direction of a block, which changes when block rotates
    bool isDrew; // is this block drew onto the display
    
protected:
    int getDirection(); // get the current facing of the block
    void setDirection(int dir); // set the direction of the block(rotate)
    void setXY(int x, int y); // set the position of the block
    
public:
    
    Block(char type);
    void setCoord(int x, int y); // set the position of the block
    int getX(); //get a block's x coordinate
    int getY(); //  get a block's y coordinate
    bool getDrew(); // check whether a block is drew onto the display
    void setDrew(bool b); // set the isDrew status
    char getType(); // check what type the block is
    
    // Since each block is made up of a unique 4x4 char array, that array is placed in the block's subclass. The following method requires access to such array and thus are declared virtual.
    virtual char getCharAt(int x, int y) = 0; // get a char at specified x, y coords of the block's array
    virtual void setCurrentBlock(int dir) = 0; // change a block's facing
    virtual void rotateCW() = 0; // rotate clockwise
    virtual void rotateCCW() = 0; // rotate counterclockwise
    virtual int getWidth() = 0; // get the width of the smallest rectangle enclosing the block
    virtual int getHeight() = 0; // get the height of the smallest rectangle enclosing the block
    virtual int getColor() = 0; // get the block's color
    virtual ~Block();
};

#endif /* defined(__a5Second__block__) */
