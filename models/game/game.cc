#include "game.h"
#include "player/player.h"
#include "turnhandler.h"
#include "board/downloadedge.h"
#include "link/link.h"

Link &Game::getUserLink(char label)
{
    Player &user = turnHandler->getCurrentPlayer();
    int userId = user.getId();
    Link &link = user.getLink(label);
}

void Game::battle(Link &attacker, Link &defender, const Position &from, const Position &to)
{
    attacker.reveal();
    defender.reveal();

    int atkStrength = attacker.getStrength();
    int defStrength = defender.getStrength();

    bool attackerWins = (atkStrength > defStrength) || (atkStrength == defStrength); // tie goes to attacker

    Link *winnerLink = attackerWins ? &attacker : &defender;
    Link *loserLink = attackerWins ? &defender : &attacker;

    Player &winner = *winnerLink->getOwner();

    // 2. Download the defeated link
    winner.download(*loserLink);

    // 3. Update board
    board.removeLink(from); // attacker's old position

    if (attackerWins)
    {
        board.removeLink(to);           // remove defender
        board.placeLink(&attacker, to); // attacker moves in
    }
    // else: attacker loses, do not place
}

bool Game::handleDownloadEdge(Link &link, const Position &from, const Position &to)
{
    if (board.isValidPosition(to))
        return false;

    Cell &fromCell = board.at(from);
    auto *edge = dynamic_cast<DownloadEdge *>(fromCell.getFeature());

    if (!edge)
    {
        throw std::invalid_argument("Cannot move off board from a non-download edge cell.");
    }

    // Get direction of the attempted move
    Direction moveDir;
    if (to.row < from.row)
        moveDir = Direction::Up;
    else if (to.row > from.row)
        moveDir = Direction::Down;
    else if (to.col < from.col)
        moveDir = Direction::Left;
    else
        moveDir = Direction::Right;

    if (moveDir != edge->getDirection())
    {
        throw std::invalid_argument("Invalid direction for download edge.");
    }

    edge->getDownloader().downloadLink(link);
    board.removeLink(from);
    endTurn();
    return true;
}

void Game::moveLinkHelper(Link &link, const std::string &direction)
{
    Position from = board.findLinkPosition(link);
    if (from == Position{-1, -1}) // Link not found
    {
        throw std::runtime_error("Link not found on board.");
    }

    Position to = link.getMovementStrategy().getNewPos(from, direction);

    // Check if link moves off the board
    if (handleDownloadEdge(link, from, to))
        return;

    // 3. Get destination cell and link
    Cell &destCell = board.at(to);
    Link *destLink = destCell.getLink();

    // 4. Cannot move onto your own link
    if (destLink && destLink->getOwnerId() == userId)
    {
        throw std::invalid_argument("Cannot move onto your own link.");
    }

    // 5. Apply cell effects BEFORE anything else
    destCell.onEnter(link, user);

    if (link.isDownloaded())
    {
        board.removeLink(from); // original position
        endTurn();
        return;
    }

    // 5. Combat if opponent's link is present
    if (destLink && destLink->getOwnerId() != userId)
    {
        battle(link, *destLink, from, to);
        endTurn();
        return;
    }

    // 6. Normal movement to empty or feature cell
    board.moveLink(link, to);
    endTurn();
}

void Game::moveLink(char label, const std::string &direction)
{
    moveLinkHelper(getUserLink(label), direction);
}

void Game::endTurn()
{
}

bool Game::isOver() const
{
    return getWinnerId().has_value();
}

std::optional<int> Game::getWinnerId() const
{
    // if (players.size() < 2)
    //     return std::nullopt;

    const Player &p1 = *players[0];
    const Player &p2 = *players[1];

    if (p1.getDownloadCount(LinkType::Data) >= 4 ||
        p2.getDownloadCount(LinkType::Virus) >= 4)
    {
        return p1.getId(); // player 1 wins
    }

    if (p2.getDownloadCount(LinkType::Data) >= 4 ||
        p1.getDownloadCount(LinkType::Virus) >= 4)
    {
        return p2.getId(); // player 2 wins
    }

    return std::nullopt;
}