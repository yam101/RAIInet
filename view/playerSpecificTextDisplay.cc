#include "playerSpecificTextDisplay.h"

PlayerSpecificTextDisplay::PlayerSpecificTextDisplay(int playerIndex, std::ostream& stream) 
    : TextDisplay(stream), povPlayer(playerIndex) {}

void PlayerSpecificTextDisplay::display(const GameState &state)
{
    // create a modified state with povPlayer as the current player for display purposes
    GameState povState = state;
    povState.currentPlayer = povPlayer;
    
    // call the parent class display method with the modified state
    TextDisplay::display(povState);
} 