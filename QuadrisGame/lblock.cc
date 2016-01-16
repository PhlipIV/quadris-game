//
//  lblock.cpp
//  a5Second
//
//  Created by Felix Chen on 2014-07-21.
//  Copyright (c) 2014 Felix Chen. All rights reserved.
//

#include "lblock.h"
Lblock::Lblock(): Block('L'), width(0), height(0){
    
    color = Xwindow::Blue;
    
    char blocks[4][4][4] = {{{'_','_','_','_'},
                             {'_','_','_','_'},
                             {'_','_','L','_'},
                             {'L','L','L','_'}},
                            {{'_','_','_','_'},
                             {'L','_','_','_'},
                             {'L','_','_','_'},
                             {'L','L','_','_'}},
                            {{'_','_','_','_'},
                             {'_','_','_','_'},
                             {'L','L','L','_'},
                             {'L','_','_','_'}},
                            {{'_','_','_','_'},
                             {'L','L','_','_'},
                             {'_','L','_','_'},
                             {'_','L','_','_'}}};
    
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


void Lblock::setCurrentBlock(int dir){
    currentBlock = blockList[dir];
    if ((dir == 0) || (dir == 2)){
        width = 3;
        height = 2;
    }
    else if ((dir == 1) || (dir == 3)){
        width = 2;
        height = 3;
    }
}

char Lblock::getCharAt(int x, int y){
    return currentBlock[x][y];
}

void Lblock::rotateCW(){
    if (getDirection() == 3) {
        setDirection(0);
    }
    else{
        setDirection(getDirection() + 1);
    }
    
    setCurrentBlock(getDirection());
}

void Lblock::rotateCCW(){
    if (getDirection() == 0) {
        setDirection(3);
    }
    else{
        setDirection(getDirection() - 1);
    }
    
    setCurrentBlock(getDirection());
}

int Lblock::getWidth(){
    return width;
}

int Lblock::getHeight(){
    return height;
}

int Lblock::getColor(){
    return color;
}


Lblock::~Lblock(){
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            delete [] blockList[i][j];
        }
        delete [] blockList[i];
    }
    delete [] blockList;
}