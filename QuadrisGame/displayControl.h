//
//  displayControl.h
//  a5Second
//
//  Created by Felix Chen on 2014-07-24.
//  Copyright (c) 2014 Felix Chen. All rights reserved.
//
//  This class controlls both the text and graphical display of the game

#ifndef __a5Second__displayControl__
#define __a5Second__displayControl__


#include <iostream>
#include "block.h"
#include "grid.h"
#include "window.h"
#include <map>

class DisplayControl{
    
    char **theDisplay; // 2d array of char that is to be outputted
    Xwindow *window; // Xwindow object that is used for graphical display
    bool isTextOnly; // controls whether display is text only
    std::map<char, int> colorMap; // tracks the color for each block
    
public:
    
    DisplayControl(bool isText);
    void notify(Block *b); // draw or undraw a block on the display
    void notify(Grid *g); // match the display with the grid
    void notify(std::string level, std::string score, std::string hiScore); // displaying game stats
    void displayNextBlock(Block *b); // display the next block
    void reset(); // reset the display
    void displayOver(); // display the over message
    ~DisplayControl(); 
    friend std::ostream &operator<<(std::ostream &out, const DisplayControl &td);
};
#endif /* defined(__a5Second__displayControl__) */
