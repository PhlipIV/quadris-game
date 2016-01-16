//
//  grid.cpp
//  a5Second
//
//  Created by Felix Chen on 2014-07-20.
//  Copyright (c) 2014 Felix Chen. All rights reserved.
//

#include "grid.h"

Grid::Grid():width(10), height(18), highestPoint(17){
    
    //initialize the grid
    landed = new char*[height];
    blockSequence = new int*[height];
    for (int i = 0; i < height; i++) {
        landed[i] = new char[width];
        blockSequence[i] = new int[width];
        for (int j = 0; j < width; j++){
            landed[i][j] = '_';
            blockSequence[i][j] = 0;
        }
    }
}


int Grid::getHeight(){
    
    return height;
}


int Grid::getWidth(){
    
    return width;
}


char Grid::getChar(int x, int y){
    
    return landed[x][y];
}


bool Grid::isAvailable(int x, int y){
    
    return landed[x][y] == '_';
}


void Grid::landCell(int x, int y, char c){
    
    landed[x][y] = c;
}


void Grid::landSequence(int x, int y, int c){
    
    blockSequence[x][y] = c;
}


bool Grid::isLineFilled(int lineIndex){
    
    for (int i = 0; i < width; i++) {
        if (landed[lineIndex][i] == '_') {
            return false;
        }
    }
    
    return true;
}


int Grid::removeFilledLine(){
    
    int lineRemoved = 0; // count number of filled lines
    for (int i = 0; i < height; i++) {
        if (isLineFilled(i)) {
            shiftDown(i);
            lineRemoved++;
        }
    }
    
    return lineRemoved;
}


void Grid::shiftDown(int lineIndex){
    
    // shift lines down by one unit
    for (int i = lineIndex-1; i >= 0; i--) {
        clearLine(i+1);
        for (int j = 0; j < width; j++) {
            landed[i+1][j] = landed[i][j];
            blockSequence[i+1][j] = blockSequence[i][j];
        }
    }
    
    // add a blank line at top
    for (int i = 0; i < width; i++) {
        landed[0][i] = '_';
        blockSequence[0][i] = 0;
    }
}


void Grid::clearLine(int lineIndex){
    
    for (int i = 0; i < width; i++) {
        landed[lineIndex][i] = '_';
        blockSequence[lineIndex][i] = 0;
    }
}


void Grid::clearGrid(){
    
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++){
            landed[i][j] = '_';
            blockSequence[i][j] = 0;
        }
    }
}


bool Grid::doesBlockSequenceContain(int num){
    
    // starting at the bottom for quicker find
    for (int i = 17; i >= 0; i--) {
        for (int j = 0; j < 10; j++) {
            if (blockSequence[i][j] == num) {
                return true;
            }
        }
    }
    
    return false;
}


void Grid::removeBlock(int sequenceNum){
    
    for (int i = 17; i >= 0; i--) {
        for (int j = 0; j < 10; j++) {
            if (blockSequence[i][j] == sequenceNum) {
                blockSequence[i][j] = 0;
                landed[i][j] = '_';
            }
        }
    }
}


int Grid::getHighest(){
    
    return highestPoint;
}


void Grid::setHighest(int high){
    
    highestPoint = high;
}


Grid::~Grid(){
    
    for (int i = 0; i < 18; i++) {
        delete [] landed[i];
        delete [] blockSequence[i];
    }
    delete [] landed;
    delete [] blockSequence;
}

/*
std::ostream &operator<<(std::ostream &out, const Grid &g){
    
    for (int i = 0; i < 18; i++) {
        if (i < 10) {
            out << i << ":  ";
        }else{
            out << i << ": ";
        }
        for (int j = 0; j < 10; j++) {
            out << g.blockSequence[i][j];
            if (j == 10 - 1) {
                out << std::endl;
            }
        }
        
    }
    //std::cout << "loop exited" << std::endl;
    
    return out;
}
*/