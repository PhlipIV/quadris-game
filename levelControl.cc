//
//  levelControl.cpp
//  a5Second
//
//  Created by Felix Chen on 2014-07-21.
//  Copyright (c) 2014 Felix Chen. All rights reserved.
//

#include "levelControl.h"

// initialize level arrays
char LevelControll::levelOneArray[] = {'S','Z','I','I','J','J','O','O','T','T','L','L'};
char LevelControll::levelTwoArray[]  = {'I','J','O','S','Z','T','L'};
char LevelControll::levelThreeArray[] = {'S','S','Z','Z','I','J','O','T','L'};


LevelControll::LevelControll(std::string fileName, int startLevel): maximumLevel(3), defaultBlockTrack(0){
    
    // set the starting value for current level
    if (startLevel <= maximumLevel) {
        currentlevel = startLevel;
    }
    else{
        startLevel = 0;
    }
    
    // load up the level zero vector with values in the file
    std::ifstream file(fileName.c_str());
    char t;
    while (file >> t) {
        defaultBlock.push_back(t);
    }
}


LevelControll::LevelControll(std::string fileName, int startLevel, int seed): maximumLevel(3), defaultBlockTrack(0){
    
    // set the starting value for current level
    if (startLevel <= maximumLevel) {
        currentlevel = startLevel;
    }
    else{
        startLevel = 0;
    }
    
    // load up the level zero vector with values in the file
    std::ifstream file(fileName.c_str());
    char t;
    while (file >> t) {
        defaultBlock.push_back(t);
    }
    
    // set the seed
    srand(seed);
}


Block *LevelControll::createBlock(char type){
    if (type == 'I') {
        return new Iblock();
    }
    else if (type == 'J'){
        return new Jblock();
    }
    else if (type == 'O'){
        return new Oblock();
    }
    else if (type == 'S'){
        return new Sblock();
    }
    else if (type == 'Z'){
        return new Zblock();
    }
    else if (type == 'T'){
        return new Tblock();
    }
    else{
        return new Lblock();
    }
}


Block *LevelControll::getBlock(){
    
    if (currentlevel == 0) {
        if (defaultBlockTrack >= defaultBlock.size()) {
            defaultBlockTrack = 0;
        }
        return createBlock(defaultBlock[defaultBlockTrack++]);
        
    }
    
    // use the random number to index the correct level array
    else if (currentlevel == 1){
        int i = rand() % 12;
        return createBlock(levelOneArray[i]);
    }
    else if (currentlevel == 2){
        int i = rand() % 7;
        return createBlock(levelOneArray[i]);
    }
    else{
        int i = rand() % 9;
        return createBlock(levelOneArray[i]);
    }
}


void LevelControll::levelup(){
    
    if (currentlevel < maximumLevel) {
        currentlevel++;
    }
}


void LevelControll::leveldown(){
    
    if (currentlevel > 0) {
        currentlevel--;
    }
}


int LevelControll::getlevel(){
    
    return currentlevel;
}

void LevelControll::reset(){
    
    currentlevel = 0;
    defaultBlockTrack = 0;
}

void LevelControll::setSeed(int seed){
    
    srand(seed);
}




