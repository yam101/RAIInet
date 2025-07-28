#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H

#include "view.h"
#include <iostream>
#include <fstream>
#include <map>

class TextDisplay : public View
{
protected:
    std::ostream &out; // reference, no ownership

    // virtual formatting methods - overridden by colored displays
    virtual std::string formatBaseText(const std::string& text) const { return text; }
    virtual std::string formatServerPort(const std::string& text) const { return text; }
    virtual std::string formatFirewall(const std::string& text) const { return text; }
    virtual std::string formatRevealedData(const std::string& text) const { return text; }
    virtual std::string formatRevealedVirus(const std::string& text) const { return text; }
    virtual std::string formatCurrentPlayerHeader(const std::string& text) const { return text; }
    virtual std::string formatWinMessage(const std::string& text) const { return text; }
    virtual std::string formatReset() const { return ""; }

protected:
    void printDownloads(const PlayerState &player) const;
    void printLinks(const GameState &state, int ownerIndex, int viewerIndex) const;
    void printPlayer(const GameState &state, int playerIndex) const;
    char linkTypeString(LinkType type) const;
    std::string boardStateString(const std::vector<std::vector<char>> &state,
                                const std::map<char, LinkState> &linkStates,
                                int currentPlayer) const;

public:
    static std::string boardStateString(const std::vector<std::vector<char>> &state);

    explicit TextDisplay(std::ostream &stream);
    ~TextDisplay() = default; // must define virtual destructor

protected:
    void display(const GameState &state) override;
    void displayWin(const WinState &state) override;
};

#endif
