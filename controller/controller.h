#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <fstream>
#include "../models/game/game.h"
#include "../view/view.h"
#include "../view/graphicdisplay.h"
#include "../view/textdisplay.h"
#include "../view/coloredTextDisplay.h"
#include "../view/playerSpecificTextDisplay.h"
#include "inputhandler.h"
#include "textinputhandler.h"
#include "eninputhandler.h"
#include "frinputhandler.h"
#include <iostream>

class Controller
{
    std::unique_ptr<Game> game;
    std::vector<std::unique_ptr<View>> views;

    // Controller owns streams and passes references to handlers/views
    std::unique_ptr<std::ifstream> fileStream;               // owned file stream, created when needed
    std::vector<std::unique_ptr<std::ofstream>> outputFiles; // owned output file streams
    std::unique_ptr<TextInputHandler> commandLineInput;
    std::unique_ptr<TextInputHandler> fileInput;

    // either commandLineInput or fileInput depending on which is active
    InputHandler *currentInput; // reference to allow for different input types

    void parseArgs(int argc, char **argv, bool &graphics, bool &dual, bool &french,
                   std::vector<std::string> &playerAbilities,
                   std::vector<std::string> &linkFiles);
    void setupGame(bool graphics, bool dual,
                   const std::vector<std::string> &playerAbilities,
                   const std::vector<std::string> &linkFiles);

    void notifyViews(); // helper to notify all views of game state changes
    void onGameOver();  // helper to notify views when game is over

public:
    Controller();
    void init(int argc, char **argv);
    void run();
};

#endif