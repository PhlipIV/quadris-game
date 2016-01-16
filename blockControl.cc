//
//  blockControl.cpp
//  a5Second
//
//  Created by Felix Chen on 2014-07-21.
//  Copyright (c) 2014 Felix Chen. All rights reserved.
//

#include "blockControl.h"

#define dirNorth 0
#define dirSouth 1
#define dirWest 2
#define dirEast 3
#define blockArraySize 4
#define gridHeight 18
#define gridWidth 10


BlockControl::BlockControl(DisplayControl *dp, std::string fileName, int startLevel, int seed): isOver(false), score(0), blockSequence(1){
    
    g = new Grid(); //initialize grid object
    
    //call different constructor for LevelControll according to the seed received.
    // negative seed is invalid
    if (seed < 0) {
        levelctrl = new LevelControll(fileName, startLevel);
    }
    else{
        levelctrl = new LevelControll(fileName, startLevel,seed);
    }
    
    theDisplay = dp; // initialize displayControll object
    setCurrentBlock(levelctrl->getBlock()); // set the current block
    nextBlock = levelctrl->getBlock(); // get the next block
}


void BlockControl::setCurrentBlock(Block *b){
    
    currentBlock = b;
    
    // if current block cannot be placed in the default position, then game is over
    if (!checkMovable(4)) {
        isOver = true;
        theDisplay->displayOver();
    }
    // otherwise update the block in display
    else{
        theDisplay->notify(currentBlock);
    }
}


//N:0 S:1 W:2 E:3 Original Position: 4
bool BlockControl::checkMovable(int dir){
    
    ///////////////////////////////////////////////////
    // This block first gets the potential new position for the block
    // the check whether the new pisition is within bound of the board
    int potentialX = currentBlock->getX();
    int potentialY = currentBlock->getY();
    if (dir == dirNorth){
        potentialX--;
    }
    else if (dir == dirSouth){
        potentialX++;
    }
    else if (dir == dirWest){
        potentialY--;
    }
    else if (dir == dirEast){
        potentialY++;
    }
    if ((potentialX < currentBlock->getHeight()-1) || (potentialY < 0) || (potentialX > gridHeight - 1) || ( potentialY > gridWidth - currentBlock->getWidth())) {
        return false;
    }
    ///////////////////////////////////////////////////
    
    // check whether the spot is avaiable by mapping each index in block's array to an index in the grid
    // 4 because every block is of size 4x4
    for (int i = 0; i < blockArraySize; i++) {
        for (int j = 0; j < blockArraySize; j++) {
            if (currentBlock->getCharAt(i, j) != '_') {
                if (!(g->isAvailable(potentialX + i - 3, potentialY + j))) {
                    return false;
                }
            }
        }
    }
    
    return true;
}


//N:0 S:1 W:2 E:3
void BlockControl::moveNorth(int times){
    
    if (times) { // if times != 0
        theDisplay->notify(currentBlock); // undraw the block if it is already in display
        for (int i = 0; i < times; i++) {
            if (checkMovable(dirNorth)) {
                currentBlock->setCoord(currentBlock->getX() - 1, currentBlock->getY());
            }
        }
        theDisplay->notify(currentBlock); // update the display
    }
}


void BlockControl::moveSouth(int times){
    if (times) { // if times != 0
        theDisplay->notify(currentBlock); // undraw the block if it is already in display
        for (int i = 0; i < times; i++) {
            if (checkMovable(dirSouth)) {
                currentBlock->setCoord(currentBlock->getX() + 1, currentBlock->getY());
            }
        }
        theDisplay->notify(currentBlock); // update the display
    }
}


void BlockControl::moveWest(int times){
    if (times) { // if times != 0
        theDisplay->notify(currentBlock); // undraw the block if it is already in display
        for (int i = 0; i < times; i++) {
            if (checkMovable(dirWest)) {
                currentBlock->setCoord(currentBlock->getX(), currentBlock->getY() - 1);
            }
        }
        theDisplay->notify(currentBlock); // update the display
    }
}


void BlockControl::moveEast(int times){
    if (times) { // if times != 0
        theDisplay->notify(currentBlock); // undraw the block if it is already in display
        for (int i = 0; i < times; i++) {
            if (checkMovable(dirEast)) {
                currentBlock->setCoord(currentBlock->getX(), currentBlock->getY() + 1);
            }
        }
        theDisplay->notify(currentBlock); // update the display
    }
}


bool BlockControl::checkRotatable(std::string dir){
    
    if (dir == "CW") {
        currentBlock->rotateCW(); // first rotate the block
        for (int i = 0; i < blockArraySize; i++) {
            for (int j = 0; j < blockArraySize; j++) {
                if (currentBlock->getCharAt(i, j) != '_') {
                    // check if block is out of bound after rotation
                    int potentialX = currentBlock->getX() + i - 3;
                    int potentialY = currentBlock->getY() + j;
                    if ((potentialX < 0) || (potentialX > gridHeight - 1) || (potentialY < 0) || (potentialY > gridWidth - 1)) {
                        currentBlock->rotateCCW(); // rotate the block back
                        return false;
                    }
                    // check whether spots are avaible
                    else if (!(g->isAvailable(potentialX, potentialY))) {
                        currentBlock->rotateCCW(); // rotate the block back
                        return false;
                    }
                }
            }
        }
        currentBlock->rotateCCW(); // rotate the block back
        return true;
    }
    else{
        currentBlock->rotateCCW(); // first rotate the block
        for (int i = 0; i < blockArraySize; i++) {
            for (int j = 0; j < blockArraySize; j++) {
                if (currentBlock->getCharAt(i, j) != '_') {
                    // check if block is out of bound after rotation
                    int potentialX = currentBlock->getX() + i - 3;
                    int potentialY = currentBlock->getY() + j;
                    if ((potentialX < 0) || (potentialX > gridHeight - 1) || (potentialY < 0) || (potentialY > gridWidth - 1)) {
                        currentBlock->rotateCW(); // rotate the block back
                        return false;
                    }
                    // check whether spots are avaible
                    else if (!(g->isAvailable(potentialX, potentialY))) {
                        currentBlock->rotateCW(); // rotate the block back
                        return false;
                    }
                }
            }
        }
        currentBlock->rotateCW();// rotate the block back

        return true;
    }
}


void BlockControl::rotateCW(int times){
    
    if (times) {
        theDisplay->notify(currentBlock);
        for (int i = 0; i < times; i++) {
            if (checkRotatable("CW")) {
                currentBlock->rotateCW();
            }
        }
        theDisplay->notify(currentBlock);
    }
}


void BlockControl::rotateCCW(int times){
    
    if (times) {
        theDisplay->notify(currentBlock);
        for (int i = 0; i < times; i++) {
            if (checkRotatable("CCW")) {
                currentBlock->rotateCCW();
            }
        }
        theDisplay->notify(currentBlock);
    }
}


void BlockControl::drop(){
    
    theDisplay->notify(currentBlock); // first undraw the block
    
    //move the block to the lowest position possible
    while (checkMovable(dirSouth)) {
        currentBlock->setCoord(currentBlock->getX() + 1, currentBlock->getY());
    }
    theDisplay->notify(currentBlock);
    for (int i = 0; i < blockArraySize; i++) {
        for (int j = 0; j < blockArraySize; j++) {
            if (currentBlock->getCharAt(i, j) != '_') {
                // The the coordinate of the highest occupied point
                if ((currentBlock->getX() + i - 3) < g->getHighest()) {
                    g->setHighest(currentBlock->getX() + i - 3);
                }
                // add the char representation of the block into the grid's landCell array
                g->landCell(currentBlock->getX() + i - 3, currentBlock->getY() + j, currentBlock->getType());
                // add the int representation of the block into the grid's landSequence array
                g->landSequence(currentBlock->getX() + i - 3, currentBlock->getY() + j, blockSequence);
            }
        }
    }
    
    // record the block sequence # and the level
    fallenBlock[blockSequence] = levelctrl->getlevel();
    
    blockSequence++; // increment the sequence number
    delete currentBlock; // delete current block
    
    // if there is any line removed
    int lineRemoved = g->removeFilledLine();
    if (lineRemoved != 0) {
        std::cout << "Fantistic!!!!!!" << std::endl;
        score += (lineRemoved+levelctrl->getlevel())*(lineRemoved+levelctrl->getlevel()); // update the score
        
        /********************************************************/
        // if there is any block that is complete removed( the blocksequence array inside grid does not contain the block's sequence number)
        // then update the score again
        std::map<int,int>::iterator it;
        std::vector<int> erasingItem;
        for (it = fallenBlock.begin(); it != fallenBlock.end(); it++) {
            if (!g->doesBlockSequenceContain(it->first)) {
                score += (it->second + 1)*(it->second + 1);
                erasingItem.push_back(it->first);
            }
        }
        
        // remove the sequence number from the fallenBlock vector so we wont be
        // looking for these block next time
        for (std::vector<int>::iterator it = erasingItem.begin(); it != erasingItem.end(); it++) {
            fallenBlock.erase(*it);
        }
        /********************************************************/
        
        theDisplay->notify(g); // update the display
    }
    
    /********************************************************/
    // following implements the feature that some block will disappear after the 10th
    // block has fallen in higher level games
    if (levelctrl->getlevel() > 1) {
        if (blockSequence > 10) {
            int i = rand() % 2;
            if (i) {
                g->removeBlock(blockSequence-10);
                fallenBlock.erase(blockSequence-10);
                theDisplay->notify(g);
            }
        }
    }
    /********************************************************/
    
    // update currentBlock and get the next block
    setCurrentBlock(nextBlock);
    nextBlock = levelctrl->getBlock();
}


void BlockControl::levelup(int times){
    
    if (times) {
        for (int i = 0; i < times; i++) {
            levelctrl->levelup();
        }
        delete nextBlock;
        nextBlock = levelctrl->getBlock();
    }
}


void BlockControl::leveldown(int times){
    
    if (times) {
        for (int i = 0; i < times; i++) {
            levelctrl->leveldown();
        }
        delete nextBlock;
        nextBlock = levelctrl->getBlock();
    }
}


bool BlockControl::getState(){
    
    return isOver;
}


void BlockControl::showDisplay(){
    std::cout << *theDisplay;
    
    //Following codes are for debugging
    //std::cout << blockSequence << std::endl;
    /*
    std::cout << *g;
    std::cout << "sequence check" <<std::endl;
    std::map<int, int>::iterator it;
    for (it = fallenBlock.begin(); it != fallenBlock.end(); it++) {
        std::cout << it->first << ":" << it->second <<" ";
    }
    std::cout << std::endl;
     */
}


void BlockControl::displayNextBlock(){
    
    // print the char representation of the block onto st::out
    for (int i = 0; i < blockArraySize; i++) {
        for (int j = 0; j < blockArraySize; j++) {
            if ((i >= (4 - nextBlock->getHeight())) && (j < nextBlock->getWidth())) {
                if (j+1 == nextBlock->getWidth()) {
                    std::cout << nextBlock->getCharAt(i, j) << std::endl;
                }
                else{
                    std::cout << nextBlock->getCharAt(i, j);
                }
            }
        }
    }
    theDisplay->displayNextBlock(nextBlock);
}


int BlockControl::getLevel(){
    
    return levelctrl->getlevel();
}


int BlockControl::getScore(){
    
    return score;
}

void BlockControl::restart(){
    
    g->clearGrid(); // clear the grid first
    theDisplay->reset(); // the reset the display as well
    delete currentBlock; // delete current block
    delete nextBlock; // delete the next block as well
    levelctrl->reset(); // reset the level
    setCurrentBlock(levelctrl->getBlock()); // get a new current block
    nextBlock = levelctrl->getBlock(); // get a new next block
    isOver = false;
    score = 0; // reset score
    fallenBlock.clear(); // remove all records of fallen block
    blockSequence = 1; // reset block sequence track
    
}

void BlockControl::setSeed(int seed){
    
    levelctrl->setSeed(seed);
}




BlockControl::~BlockControl(){
    
    delete g;
    delete currentBlock;
    delete nextBlock;
    delete theDisplay;
    delete levelctrl;
}
