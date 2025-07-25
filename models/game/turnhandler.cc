#include "turnhandler.h"

int TurnHandler::getCurrentPlayerIndex() const
{
    return activePlayer;
}

void TurnHandler::nextTurn()
{
    if (skipTurn)
    {
        // skip the next player's turn by advancing 2x
        activePlayer = (activePlayer + 2) % 2;
        skipTurn = false;
    }
    else
    {
        activePlayer = (activePlayer + 1) % 2;
    }
}

void TurnHandler::skipNextTurn()
{
    skipTurn = true;
}
