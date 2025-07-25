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

protected:
    virtual void display(const GameState &state) = 0;
};

#endif
