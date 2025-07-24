#ifndef GRAPHICDISPLAY_H
#define GRAPHICDISPLAY_H

#include "view.h"

class GraphicDisplay : public View
{
protected:
    void display(std::vector<Player> &players, Board &board, int currentPlayer) override;
};

#endif
