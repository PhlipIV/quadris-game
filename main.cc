//
//  main.cpp
//  a5Second
//
//  Created by Felix Chen on 2014-07-20.
//  Copyright (c) 2014 Felix Chen. All rights reserved.
//

#include <iostream>
#include "quadris.h"
#include "sstream"


int main(int argc, const char * argv[])
{
    // initial values for command line arguemnts
    bool isTextOnly = false;
    std::string fileName = "sequence.txt";
    int initialLevel = 0;
    int seed = -1;
    bool quitGame = false;
    
    // modify the variables if corresponding command line argument is present
    for (int i = 0; i < argc; i++) {
        std::string s = argv[i];
        if (s == "-text") {
            isTextOnly = true;
        }
        else if (s == "-scriptfile"){
            fileName = argv[++i];
        }
        else if (s == "-startlevel"){
            s = argv[++i];
            std::stringstream ss(s);
            ss >> initialLevel;
        }
        else if (s == "-seed"){
            s = argv[++i];
            std::stringstream ss(s);
            ss >> seed;
        }
    }
    
    // create pointer to game object
    Quadris *game = Quadris::getInstance(isTextOnly, fileName, initialLevel, seed);
    std::string userinput;
    
    while (!quitGame) {
        if (!quitGame) {
            game->runGame();
        }
        if  (std::cin.eof()){
            break;
        }
        
        /*****************************************************/
        // after game ends, ask the user whether to quit or not and proceed base on user's response
        std::cout << "Do you want to play again? (y/n)" << std::endl;
        while (std::cin >> userinput) {
            if (userinput == "y") {
                game->restart();
                break;
            }
            else if (userinput == "n"){
                quitGame = true;
                break;
            }
            else{
                std::cout << "Invalid Input, please enter again" << std::endl;
            }
        }
        /*****************************************************/
    }
    return 0;
}

