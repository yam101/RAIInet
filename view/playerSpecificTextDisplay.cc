#include "playerSpecificTextDisplay.h"

PlayerSpecificTextDisplay::PlayerSpecificTextDisplay(int playerIndex, std::ostream& stream) 
    : TextDisplay(stream), povPlayer(playerIndex) {}

void PlayerSpecificTextDisplay::display(const GameState &state)
{
    // inject pov player as currentPlayer
    GameState povState = state;
    povState.currentPlayer = povPlayer;
    
    // reuse display logic
    TextDisplay::display(povState);
} 