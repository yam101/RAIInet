#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <fstream>
#include "../models/game/game.h"
#include "../view/view.h"
#include "../view/graphicdisplay.h"
#include "../view/textdisplay.h"
#include "inputhandler.h"
#include "textinputhandler.h"

class Controller
{
    std::unique_ptr<Game> game;
    std::unique_ptr<TextInputHandler> commandLineInput;
    std::unique_ptr<TextInputHandler> fileInput;
    TextInputHandler *currentInput; // reference to allow for different input types

    std::vector<std::unique_ptr<View>> views;

    void notifyViews(); // helper to notify all views of game state changes

public:
    Controller(bool graphicsEnabled);
    void run();
    void onGameUpdate(); // public method called by Game to notify views
};

#endif