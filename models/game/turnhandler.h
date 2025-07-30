#ifndef TURN_HANDLER_H
#define TURN_HANDLER_H

class TurnHandler
{
private:
    int activePlayer = 0; // idx of current player (0 for player 1, 1 for player 2)
    bool skipTurn = false; // flag to skip next player's turn
    bool abilityPlayed = false; // flag indicating if ability was used this turn

public:
    int getCurrentPlayerIndex() const;

    // incrments turn, skipping 1 if skipTurn is true
    void nextTurn();

    // flags next player's turn to be skipped
    void skipNextTurn();

    // flags ability played
    void setAbilityPlayed(bool played);

    // returns true if ability was played this turn
    bool getAbilityPlayed() const;
};

#endif
