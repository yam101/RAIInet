#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H

#include "view.h"
#include <iostream>
#include <fstream>
#include <memory>

class TextDisplay : public View
{
protected:
    std::unique_ptr<std::ostream> out;

protected:
    void printDownloads(const PlayerState &player) const;
    void printLinks(const GameState &state, int ownerIndex, int viewerIndex) const;
    void printPlayer(const GameState &state, int playerIndex) const;
    char linkTypeString(LinkType type) const;

public:
    static std::string boardStateString(const std::vector<std::vector<char>> &state);
    
    TextDisplay();  // default constructor - uses cout
    explicit TextDisplay(const std::string &filepath);  // filepath constructor
    ~TextDisplay() = default;  // virtual destructor for proper cleanup

protected:
    void display(const GameState &state) override;
};

#endif
