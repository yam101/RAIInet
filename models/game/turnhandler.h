#ifndef TURN_HANDLER_H
#define TURN_HANDLER_H

class TurnHandler
{
private:
    int activePlayer = 0;
    bool skipTurn = false;

public:
    // teturns the index of the currently active player (0 or 1)
    int getCurrentPlayerIndex() const;

    // incrments turn, skipping 1 if skipTurn is true
    void nextTurn();

    // flags next player's turn to be skipped
    void skipNextTurn();
};

#endif
