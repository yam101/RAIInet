#ifndef GRAPHICDISPLAY_H
#define GRAPHICDISPLAY_H

#include "view.h"

class GraphicDisplay : public View
{
protected:
    void display(const std::vector<Player> &players, const Board &board, int currentPlayer) const override;
};

#endif
