//
//  iblock.cpp
//  a5Second
//
//  Created by Felix Chen on 2014-07-21.
//  Copyright (c) 2014 Felix Chen. All rights reserved.
//

#include "iblock.h"
Iblock::Iblock(): Block('I'), width(0), height(0){
    
    color = Xwindow::Red;
    
    char blocks[4][4][4] = {{{'_','_','_','_'},
                             {'_','_','_','_'},
                             {'_','_','_','_'},
                             {'I','I','I','I'}},
                            {{'I','_','_','_'},
                             {'I','_','_','_'},
                             {'I','_','_','_'},
                             {'I','_','_','_'}},
                            {{'_','_','_','_'},
                             {'_','_','_','_'},
                             {'_','_','_','_'},
                             {'I','I','I','I'}},
                            {{'I','_','_','_'},
                             {'I','_','_','_'},
                             {'I','_','_','_'},
                             {'I','_','_','_'}}};
    
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
    setXY(3, 0);
}


void Iblock::setCurrentBlock(int dir){
    currentblock = blockList[dir];
    if ((dir == 0) || (dir == 2)){
        width = 4;
        height = 1;
    }
    else if ((dir == 1) || (dir == 3)){
        width = 1;
        height = 4;
    }
}

char Iblock::getCharAt(int x, int y){
    return currentblock[x][y];
}

void Iblock::rotateCW(){
    if (getDirection() == 3) {
        setDirection(0);
    }
    else{
        setDirection(getDirection() + 1);
    }
    
    setCurrentBlock(getDirection());
}

void Iblock::rotateCCW(){
    if (getDirection() == 0) {
        setDirection(3);
    }
    else{
        setDirection(getDirection() - 1);
    }
    
    setCurrentBlock(getDirection());
}

int Iblock::getWidth(){
    return width;
}

int Iblock::getHeight(){
    return height;
}

int Iblock::getColor(){
    return color;
}

Iblock::~Iblock(){
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            delete [] blockList[i][j];
        }
        delete [] blockList[i];
    }
    delete [] blockList;
}