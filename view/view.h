#ifndef VIEW_H
#define VIEW_H

#include <vector>
#include "../models/player/player.h"
#include "../models/game/board/board.h"
#include "../models/game/link/link.h"

class Player;
class Board;

class View
{
public:
    void notify(const std::vector<Player> &players, const Board &board, int currentPlayer) const
    {
        display(players, board, currentPlayer);
    };
    virtual ~View() = default;

protected:
    virtual void display(const std::vector<Player> &players, const Board &board, int currentPlayer) const = 0;
};

#endif
