//
//  oblock.cpp
//  a5Second
//
//  Created by Felix Chen on 2014-07-20.
//  Copyright (c) 2014 Felix Chen. All rights reserved.
//

#include "oblock.h"



Oblock::Oblock(): Block('O'), width(0), height(0){
    
    color = Xwindow::Cyan;
    
    char blocks[4][4][4] = {{{'_','_','_','_'},
                             {'_','_','_','_'},
                             {'O','O','_','_'},
                             {'O','O','_','_'}},
                            {{'_','_','_','_'},
                             {'_','_','_','_'},
                             {'O','O','_','_'},
                             {'O','O','_','_'}},
                            {{'_','_','_','_'},
                             {'_','_','_','_'},
                             {'O','O','_','_'},
                             {'O','O','_','_'}},
                            {{'_','_','_','_'},
                             {'_','_','_','_'},
                             {'O','O','_','_'},
                             {'O','O','_','_'}}};
    
    blockList = new char**[4];
    for (int i = 0; i < 4; i++) {
        blockList[i] = new char*[4];
        for (int j = 0; j < 4; j++) {
            blockList[i][j] = new char[4];
            for (int k = 0; k < 4; k++) {
                blockList[i][j][k] = blocks[i][j][k];
            }
        }
    }
    
    
    setCurrentBlock(getDirection());
    
}


void Oblock::setCurrentBlock(int dir){
    currentBlock = blockList[dir];
    width = 2;
    height = 2;
}

char Oblock::getCharAt(int x, int y){
    return currentBlock[x][y];
}

void Oblock::rotateCW(){
    if (getDirection() == 3) {
        setDirection(0);
    }
    else{
        setDirection(getDirection() + 1);
    }
    
    setCurrentBlock(getDirection());
}

void Oblock::rotateCCW(){
    if (getDirection() == 0) {
        setDirection(3);
    }
    else{
        setDirection(getDirection() - 1);
    }
    
    setCurrentBlock(getDirection());
}

int Oblock::getWidth(){
    return width;
}

int Oblock::getHeight(){
    return height;
}

int Oblock::getColor(){
    return color;
}

Oblock::~Oblock(){
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            delete [] blockList[i][j];
        }
        delete [] blockList[i];
    }
    delete [] blockList;
}