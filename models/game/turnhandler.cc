#include "turnhandler.h"

int TurnHandler::getCurrentPlayer() const
{
    return activePlayer;
}

void TurnHandler::nextTurn()
{
    if (skipTurn)
    {
        // Skip the next player's turn by advancing twice
        activePlayer = (activePlayer + 2) % 2;
        skipTurn = false;
    }
    else
    {
        // Normal turn
        activePlayer = (activePlayer + 1) % 2;
    }
}

void TurnHandler::skipNextTurn()
{
    skipTurn = true;
}
