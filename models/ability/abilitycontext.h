#ifndef ABILITY_CONTEXT_H
#define ABILITY_CONTEXT_H

class Link;
class Board;
class Player;
class TurnHandler;
class Game;

// provides only requested game objects to abilities
struct AbilityContext
{
    Board *board = nullptr;
    Player *user = nullptr;
    Link *linkA = nullptr;     // primary target link
    Link *linkB = nullptr;     // secondary target link for tunnel ability
    TurnHandler *turnHandler = nullptr;
    Game *game = nullptr; // only provide this if there are NO other options
};

#endif
