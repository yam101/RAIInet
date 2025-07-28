#ifndef VIEW_H
#define VIEW_H

#include "../controller/gameState.h"

class View
{
public:
    void notify(const GameState &state)
    {
        display(state);
    }
    virtual ~View() = default;
    // Notify when game is over
    void notifyWin(const WinState &state)
    {
        displayWin(state);
    }

protected:
    virtual void display(const GameState &state) = 0;
    virtual void displayWin(const WinState &state) = 0;
};

#endif
