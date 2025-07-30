#include "game.h"
#include <iostream>
#include <algorithm>

Game::Game()
    : board(std::make_unique<Board>()),
      turnHandler{},
      abilityFactory{},
      abilityContextProvider(*this) // using "*this" is safe here bc of init order
{
}

Link &Game::getUserLink(char label)
{
    Player &user = players.at(turnHandler.getCurrentPlayerIndex());
    int userId = user.getId();
    Link &link = user.getLink(label);
    return link;
}

void Game::battle(Link &attacker, Link &defender, const Position &from, const Position &to)
{
    attacker.reveal();
    defender.reveal();

    int atkStrength = attacker.getStrength();
    int defStrength = defender.getStrength();

    bool attackerWins = (atkStrength > defStrength) || (atkStrength == defStrength); // tie goes to attacker

    Link &winnerLink = attackerWins ? attacker : defender;
    Link &loserLink = attackerWins ? defender : attacker;

    Player &winner = winnerLink.getOwner();

    // winner downloads the link of the loser
    winner.downloadLink(loserLink);

    // remove attacker link from original position
    board->removeLink(from);

    if (attackerWins)
    {
        board->removeLink(to);          // remove defender
        board->placeLink(attacker, to); // attacker moves in
    }
    // else: attacker loses, it was removed and defender stays put
}

bool Game::tryDownload(const std::vector<Position> &path,
                       const Position &from,
                       Link &link,
                       const Direction &dir)
{
    Position lastValid = from;
    for (const Position &stepPos : path)
    {
        if (!board->isValidPosition(stepPos))
        {
            // stepped off the board
            if (board->at(lastValid).hasFeature<DownloadEdge>())
            {
                const DownloadEdge &edge = board->at(lastValid).getFeature<DownloadEdge>();

                if (dir != edge.getDirection())
                {
                    throw std::invalid_argument("Invalid direction for download edge.");
                }
                if (&link.getOwner() != &edge.getDownloader())
                {
                    throw std::invalid_argument("Cannot move off the board in that direction.");
                }

                edge.getDownloader().downloadLink(link);
                board->removeLink(from);
                return true; // download handled
            }
            // no download edge, illegal off board move
            throw std::invalid_argument("Cannot move off the board in that direction.");
        }
        lastValid = stepPos;
    }
    return false; // path walked entirely in‑bounds
}

void Game::moveLinkHelper(Link &link, const Direction &direction)
{
    Player &user = getCurrentPlayer();
    Position from = board->findLinkPosition(link);

    if (from == Position{-1, -1})
        throw std::runtime_error("Link not found on board.");

    // get the movement path
    auto path = link.getMovementStrategy().getPath(from, direction);

    if (tryDownload(path, from, link, direction))
        return;

    /* move is in bounds */
    // get the final destination
    Position to = path.back();
    const Cell &destCell = board->at(to);

    // apply special cell feature (like firewall) first
    destCell.onEnter(link, user);

    // if special feature caused link to be downloaded
    if (link.isDownloaded())
    {
        board->removeLink(from); // remove from original position if downloaded
        return;
    }

    // if cell doesn't have link, move normally
    // std::cout << "Destination has link? " << destCell.hasLink() << std::endl;
    if (!destCell.hasLink())
    {
        board->moveLink(link, to);
        return;
    }

    // if cell has link, either invalid move or battle
    Link &destLink = destCell.getLink();

    // cannot move onto your own link
    if (&destLink.getOwner() == &user)
    {
        throw std::invalid_argument("Cannot move onto your own link.");
    }

    // battle if we move onto an opponent link
    battle(link, destLink, from, to);
}

Direction Game::parseDirection(const std::string &dirStr)
{
    std::string d = dirStr;
    std::transform(d.begin(), d.end(), d.begin(), ::tolower);

    if (d == "up")
        return Direction::Up;
    if (d == "down")
        return Direction::Down;
    if (d == "left")
        return Direction::Left;
    if (d == "right")
        return Direction::Right;

    throw std::invalid_argument("Invalid direction: " + dirStr);
}

void Game::moveLink(char label, const std::string &direction)
{
    Direction dir = parseDirection(direction);
    Link &link = getUserLink(label);
    if (link.isDownloaded())
    {
        throw std::runtime_error("Downloaded link cannot move.");
    }
    moveLinkHelper(link, dir);
    endTurn();
}

void Game::Move(const std::vector<std::string> &params)
{

    if (params[0].empty())
    {
        throw std::runtime_error("Link label cannot be empty.");
    }

    char label = params[0][0];
    const std::string &direction = params[1];
    moveLink(label, direction);
}

void Game::endTurn()
{
    turnHandler.nextTurn();
}

bool Game::isOver() const
{
    // data‑win: check if any player has 4 data links downloaded, game is over
    for (const auto &p : players)
    {
        if (p.getDownloadCount(LinkType::Data) >= 4)
        {
            return true;
        }
    }

    // virus-loss: count how many players have 4 virus links
    int virusLosers = 0;
    for (const auto &p : players)
    {
        if (p.getDownloadCount(LinkType::Virus) >= 4)
        {
            ++virusLosers;
        }
    }

    // game is over if EVERYONE except one has lost by virus
    return (virusLosers >= players.size() - 1);
}

int Game::getWinnerId() const
{
    // precondition: isOver()==true
    // winner can have 4 data links downloaded
    for (const Player &p : players)
    {
        if (p.getDownloadCount(LinkType::Data) >= 4)
        {
            return p.getId();
        }
    }

    // if we go through all the players and none has 4 data links,
    // then we assume that the game is over through a virus loss by all but one player
    for (const Player &p : players)
    {
        if (p.getDownloadCount(LinkType::Virus) < 4)
        {
            return p.getId();
        }
    }
    return -1; // no winner found, should not happen if isOver() is true
}

std::vector<int> Game::getLoserIds() const
{
    // precondition: isOver()==true
    int winner = getWinnerId();
    std::vector<int> losers;
    for (const auto &p : players)
    {
        if (p.getId() != winner)
        {
            losers.push_back(p.getId());
        }
    }
    return losers;
}

Board &Game::getBoard()
{
    return *board;
}

TurnHandler &Game::getTurnHandler()
{
    return turnHandler;
}

Player &Game::getCurrentPlayer()
{
    return players.at(turnHandler.getCurrentPlayerIndex());
}

void Game::Ability(const std::vector<std::string> &params)
{
    if (turnHandler.getAbilityPlayed())
    {
        throw std::runtime_error("Ability has already been used this turn.");
    }

    if (params.empty())
    {
        throw std::runtime_error("Ability command requires parameters.");
    }

    // parse ability index - provide custom error for invalid input
    int index;
    try
    {
        index = std::stoi(params[0]) - 1;
    }
    catch (const std::exception &)
    {
        throw std::runtime_error("Ability ID must be a number");
    }

    std::vector<std::string> args(params.begin() + 1, params.end());

    Player &user = getCurrentPlayer();
    user.getAbility(index).use(args, abilityContextProvider);
    turnHandler.setAbilityPlayed(true);
}

const std::vector<Player> &Game::getPlayers() const
{
    return players;
}

std::string Game::Abilities() const
{
    return players.at(turnHandler.getCurrentPlayerIndex()).printAbilities();
}

void Game::setup(const std::string &abilities1,
                 const std::string &abilities2,
                 const std::string *linkFile1,
                 const std::string *linkFile2)
{
    // setup players
    players.clear();
    players.emplace_back();
    players.emplace_back();
    players[0].setup(0, abilities1, abilityFactory, linkFile1);
    players[1].setup(1, abilities2, abilityFactory, linkFile2);

    board->setup(players);
}
