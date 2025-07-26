#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <fstream>
#include "../models/game/game.h"
#include "../view/view.h"
#include "../view/graphicdisplay.h"
#include "../view/textdisplay.h"
#include "inputhandler.h"
#include "textinputhandler.h"
#include <iostream>

class Controller
{
    std::unique_ptr<Game> game;
    std::vector<std::unique_ptr<View>> views;
    std::unique_ptr<TextInputHandler> commandLineInput;
    std::unique_ptr<TextInputHandler> fileInput;

    // either commandLineInput or fileInput depending on which is active
    TextInputHandler *currentInput = commandLineInput.get(); // reference to allow for different input types

    // Setup
    bool graphics = false;
    const std::string defaultAbilities = "LFDSP"; // default abilities for both players
    std::vector<std::string> playerAbilities = {defaultAbilities, defaultAbilities};
    std::vector<std::optional<std::string>> linkFiles = {std::nullopt, std::nullopt};

    void parseArgs(int argc, char **argv);
    std::unique_ptr<Player> setupPlayer(int id);
    void setupViews(std::vector<std::unique_ptr<View>> &views);
    // void loadLinksFromFile(Player &player, const std::string &file);
    // void assignRandomLinks(Player &player);

    void notifyViews(); // helper to notify all views of game state changes

public:
    Controller(int argc, char **argv);
    void run();
    // void onGameUpdate(); // public method called by Game to notify views
};

#endif