#ifndef PLAYER_SPECIFIC_TEXT_DISPLAY_H
#define PLAYER_SPECIFIC_TEXT_DISPLAY_H

#include "textdisplay.h"

class PlayerSpecificTextDisplay : public TextDisplay
{
    const int povPlayer;  // player whose perspective this display shows

public:
    PlayerSpecificTextDisplay(int playerIndex, std::ostream& stream); 

protected:
    void display(const GameState &state) override;
};

#endif 