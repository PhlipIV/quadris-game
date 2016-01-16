//
//  grid.h
//  a5Second
//
//  Created by Felix Chen on 2014-07-20.
//  Copyright (c) 2014 Felix Chen. All rights reserved.
//

#ifndef __a5Second__grid__
#define __a5Second__grid__

#include <iostream>


class Grid{
    
    const int width; // width of the board
    const int height; // height of the board
    char **landed; // 2d array tracks landed blocks
    int **blockSequence; // landed sequence representation of the landed blocks
    // Example of difference between landed and blockSequence
    // suppose an O block has fallen
    // in landed it would look like
    // {{'O','O'},
    //  {'O','O'}}
    // int blockSequence it would look like
    // {{1, 1},
    //  {1, 1}}
    int highestPoint; // the x value of the highest occupied point
public:
    
    Grid();
    int getWidth(); // get the width of the grid
    int getHeight(); // get the height of the grid
    char getChar(int x, int y); // get the char at x,y from landed
    bool isAvailable(int x, int y); // check in landed whether point at x,y is occupied
    void landCell(int x, int y, char c); // change the cell at x, y in landed to c
    void landSequence(int x, int y, int c); // change the number at x, y in blockSequence to c
    bool isLineFilled(int lineIndex); // check whether a line is filled
    int removeFilledLine(); // remove all filled lines, return the number of lines removed
    void shiftDown(int lineIndex); // shift all line above lineIndex down one unit
    void clearLine(int lineIndex); // clear the line at lineIndex
    void clearGrid(); // clear the grid
    bool doesBlockSequenceContain(int num); // check whether blockSequence contains num
    void removeBlock(int sequenceNum); // get rid of num in blockSequence
    int getHighest(); // get the highest point occupied
    void setHighest(int high); // set the highest point occupied
    ~Grid();
    //friend std::ostream &operator<<(std::ostream &out, const Grid &g);
    
};


#endif /* defined(__a5Second__grid__) */
