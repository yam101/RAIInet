#ifndef TURN_HANDLER_H
#define TURN_HANDLER_H

class TurnHandler
{
private:
    int activePlayer = 0;
    bool skipTurn = false;

public:
    // Returns the ID of the currently active player (e.g., 0 or 1)
    int getCurrentPlayer() const;

    // Advances the turn, optionally skipping one if skipTurn was flagged
    void nextTurn();

    // Flags the next player's turn to be skipped
    void skipNextTurn();
};

#endif
