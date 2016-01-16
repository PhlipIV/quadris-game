//
//  displayControl.cpp
//  a5Second
//
//  Created by Felix Chen on 2014-07-24.
//  Copyright (c) 2014 Felix Chen. All rights reserved.
//

#include "displayControl.h"
#define blockPixelSize 20


DisplayControl::DisplayControl(bool isText): isTextOnly(isText), window(NULL){
    
    // if not text only
    if (!isTextOnly) {
        window = new Xwindow(200, 540); // initialize Xwindow
        
        // draw the black line that seperate the gameplay area from the game stat area
        for (int j = 0; j < 10; j++) {
            window->fillRectangle(j*blockPixelSize, 360, blockPixelSize, blockPixelSize, Xwindow::Black);
        }
        // draw the labels for the stats
        window->drawString(10, 400, "Level:      ", Xwindow::Black);
        window->drawString(10, 420, "Score:      ", Xwindow::Black);
        window->drawString(10, 440, "Hi Score:   ", Xwindow::Black);
        window->drawString(10, 460, "Next:       ", Xwindow::Black);
    }
    
    // initialize the 2d char array
    theDisplay = new char*[18];
    for (int x = 0; x < 18; x++) {
        theDisplay[x] = new char[10];
        for (int y = 0; y < 10; y++) {
            theDisplay[x][y] = '_';
        }
    }
    
    //initialize the colormap dictionary
    colorMap['I'] = Xwindow::Red;
    colorMap['J'] = Xwindow::Green;
    colorMap['L'] = Xwindow::Blue;
    colorMap['O'] = Xwindow::Cyan;
    colorMap['S'] = Xwindow::Yellow;
    colorMap['T'] = Xwindow::Magenta;
    colorMap['Z'] = Xwindow::Orange;
    colorMap['_'] = Xwindow::White;
}


void DisplayControl::notify(Block *b){
    
    // if a block is not yet drawn, draw the block
    if (!b->getDrew()) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (b->getCharAt(i, j) != '_') {
                    theDisplay[b->getX() + i - 3 ][b->getY() + j] = b->getCharAt(i,j);
                    if (!isTextOnly) {
                        //window->fillRectangle((b->getY() + j)*blockPixelSize, (b->getX() + i - 3)*blockPixelSize, blockPixelSize, blockPixelSize, b->getColor());
                        window->fillRectangle((b->getY() + j)*blockPixelSize, (b->getX() + i - 3)*blockPixelSize, 19, 19, b->getColor());
                    }
                }
            }
        }
        b->setDrew(true);
    }
    // if the block is drew, then clear the block
    else{
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (b->getCharAt(i, j) != '_') {
                    theDisplay[b->getX() + i - 3 ][b->getY() + j] = '_';
                }
            }
        }
        // draw a white rectangle to clear the block
        if (!isTextOnly) {
            window->fillRectangle(b->getY()*blockPixelSize, (b->getX() - b->getHeight() + 1)*blockPixelSize, b->getWidth()*blockPixelSize, b->getHeight()*blockPixelSize, Xwindow::White);
        }
        b->setDrew(false);
    }
}


void DisplayControl::notify(Grid *g){
    
    // match the display with the grid
    for (int i = 17; i >= g->getHighest(); i--) {
        for (int j = 0; j < 10; j++) {
            theDisplay[i][j] = g->getChar(i, j);
            if (!isTextOnly) {
                //window->fillRectangle(j*blockPixelSize, i*blockPixelSize, blockPixelSize, blockPixelSize, colorMap[g->getChar(i, j)]);
                window->fillRectangle(j*blockPixelSize, i*blockPixelSize, 19, 19, colorMap[g->getChar(i, j)]);
            }
        }
    }
}


void DisplayControl::notify(std::string level, std::string score, std::string hiScore){
    
    // draw the game stats in graphical display
    if (!isTextOnly) {
        window->fillRectangle(100, 380, 20, 20, Xwindow::White);
        window->fillRectangle(100, 400, 20, 20, Xwindow::White);
        window->fillRectangle(100, 420, 20, 20, Xwindow::White);
        
        window->drawString(100, 400, level, Xwindow::Black);
        window->drawString(100, 420, score, Xwindow::Black);
        window->drawString(100, 440, hiScore, Xwindow::Black);
    }
}


void DisplayControl::displayNextBlock(Block *b){
    
    // draw the next block both in text display and graphical display
    if (!isTextOnly) {
        window->fillRectangle(0, 465, 200, 75, Xwindow::White);
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (b->getCharAt(i, j) != '_') {
                    //window->fillRectangle( 60 + j*blockPixelSize, 440 + i*blockPixelSize, blockPixelSize, blockPixelSize, b->getColor());
                    window->fillRectangle( 60 + j*blockPixelSize, 440 + i*blockPixelSize, 19, 19, b->getColor());
                }
            }
        }
    }
}

void DisplayControl::reset(){
    
    for (int i = 0; i < 18; i++) {
        for (int j = 0; j < 10; j++) {
            theDisplay[i][j] = '_';
        }
    }
    // draw a big white rectangle to clear board
    if (!isTextOnly) {
        window->fillRectangle(0, 0, 200, 360, Xwindow::White);
    }
}


void DisplayControl::displayOver(){
    
    // the the pre-constructed array to draw the game over message
    if (!isTextOnly) {
        char overMessage[11][21] = {{'_','O','O','_','_','_','O','_','_','_','O','_','_','_','O','_','_','O','O','O','O'},
                                    {'O','_','_','_','_','O','_','O','_','O','_','O','_','O','_','O','_','O','_','_','_'},
                                    {'O','_','O','_','_','O','O','O','_','O','_','O','_','O','_','O','_','O','O','O','_'},
                                    {'O','_','_','O','_','O','_','O','_','O','_','_','O','_','_','O','_','O','_','_','_'},
                                    {'_','O','O','_','_','O','_','O','_','O','_','_','_','_','_','O','_','O','O','O','O'},
                                    {'_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_'},
                                    {'_','O','O','_','_','O','_','_','_','O','_','O','O','O','O','_','O','O','O','O','_'},
                                    {'O','_','_','O','_','O','_','_','_','O','_','O','_','_','_','_','O','_','_','_','O'},
                                    {'O','_','_','O','_','_','O','_','O','_','_','O','O','O','_','_','O','O','O','O','_'},
                                    {'O','_','_','O','_','_','O','_','O','_','_','O','_','_','_','_','O','_','O','_','_'},
                                    {'_','O','O','_','_','_','_','O','_','_','_','O','O','O','O','_','O','_','_','O','O'}};
        int x = 200;
        int y = 40;
        for (int i = 0; i < 11; i++) {
            for (int j = 0; j < 21; j++) {
                if (overMessage[i][j] != '_') {
                    window->fillRectangle( y + j*5, x + i*5, 5, 5, Xwindow::Red);
                }
            }
        }
    }
}


DisplayControl::~DisplayControl(){
    
    for (int i = 0; i < 18; i++) {
        delete [] theDisplay[i];
    }
    delete [] theDisplay;
    delete window;
}


std::ostream &operator<<(std::ostream &out, const DisplayControl &td){
    
    for (int i = 0; i < 18; i++) {
        //for Debugging
        /*
        if (i < 10) {
            out << i << ":  ";
        }else{
            out << i << ": ";
        }
         */
        for (int j = 0; j < 10; j++) {
            if (td.theDisplay[i][j] == '_') {
                out << ' ';
            }
            else{
                out << td.theDisplay[i][j];
            }
            if (j == 10 - 1) {
                out << std::endl;
            }
        }
    }
    
    return out;
}
