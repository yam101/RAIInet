#ifndef PLAYER_SPECIFIC_TEXT_DISPLAY_H
#define PLAYER_SPECIFIC_TEXT_DISPLAY_H

#include "textdisplay.h"

class PlayerSpecificTextDisplay : public TextDisplay
{
    const int povPlayer;  // the player whose perspective this display shows

public:
    PlayerSpecificTextDisplay(int playerIndex, std::ostream& stream); 

protected:
    void display(const GameState &state) override;
    
    // override static constants for file output (no ANSI codes)
    static constexpr const char* BASE_COLOUR = "";
    static constexpr const char* RESET = "";
    static constexpr const char* RED = "";
    static constexpr const char* GREEN = "";
    static constexpr const char* GRAY = "";
    static constexpr const char* REVERSE = "";
    static constexpr const char* UNREVERSE = "";
};

#endif 