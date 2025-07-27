#include "playerSpecificTextDisplay.h"

PlayerSpecificTextDisplay::PlayerSpecificTextDisplay(int playerIndex) 
    : TextDisplay(), povPlayer(playerIndex) {}

PlayerSpecificTextDisplay::PlayerSpecificTextDisplay(int playerIndex, const std::string &filepath)
    : TextDisplay(filepath), povPlayer(playerIndex) 
{
    // For file output, we need to disable ANSI color codes
    // Since we can't override static constexpr, we'll handle this in the display method
}

void PlayerSpecificTextDisplay::display(const GameState &state)
{
    // create a modified state with povPlayer as the current player for display purposes
    GameState povState = state;
    povState.currentPlayer = povPlayer;
    
    // call the parent class display method with the modified state
    TextDisplay::display(povState);
} 