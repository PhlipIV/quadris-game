//
//  block.cpp
//  a5Second
//
//  Created by Felix Chen on 2'O'14-'O'7-2'O'.
//  Copyright (c) 2'O'14 Felix Chen. All rights reserved.
//

#include "block.h"

Block::Block(char type):blockType(type), direction(0), x(4), y(0), isDrew(false){
}


int Block::getDirection(){
    return direction;
}

void Block::setDirection(int dir){
    direction = dir;
}

void Block::setCoord(int x, int y){
    this->x = x;
    this->y = y;
}

int Block::getX(){
    return x;
}

int Block::getY(){
    return y;
}

bool Block::getDrew(){
    return isDrew;
}

void Block::setDrew(bool b){
    isDrew = b;
}

char Block::getType(){
    return blockType;
}

void Block::setXY(int x, int y){
    this->x = x;
    this->y = y;
}

Block::~Block(){}