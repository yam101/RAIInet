#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H

#include "view.h"
#include <iostream>
#include <fstream>
#include <memory>

class TextDisplay : public View
{
protected:
    std::ostream& out; // reference, no ownership - stream managed elsewhere

protected:
    void printDownloads(const PlayerState &player) const;
    void printLinks(const GameState &state, int ownerIndex, int viewerIndex) const;
    void printPlayer(const GameState &state, int playerIndex) const;
    char linkTypeString(LinkType type) const;

public:
    static std::string boardStateString(const std::vector<std::vector<char>> &state);
    
    explicit TextDisplay(std::ostream& stream); // dependency injection
    ~TextDisplay() = default;  // virtual destructor for proper cleanup

protected:
    void display(const GameState &state) override;
};

#endif
