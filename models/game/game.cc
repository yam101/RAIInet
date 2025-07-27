#include "game.h"
#include <iostream>

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

void Game::endTurn()
{
    turnHandler.nextTurn();
}

bool Game::isOver() const
{
    // game is over if there's a winner OR if all but one player is a loser
    if (getWinnerId().has_value()) {
        return true;
    }
    
    std::vector<int> losers = getLoserIds();
    return losers.size() >= players.size() - 1;
}

std::optional<int> Game::getWinnerId() const
{
    for (const Player &p : players)
    {
        if (p.getDownloadCount(LinkType::Data) >= 4)
        {
            return p.getId(); // Sole winner
        }
    }
    return std::nullopt;
}

std::vector<int> Game::getLoserIds() const
{
    std::vector<int> losers;
    std::optional<int> winnerId = getWinnerId();

    for (const Player &p : players)
    {
        // loser if they’ve downloaded 4 viruses, or someone else has already won
        bool virusLoss = p.getDownloadCount(LinkType::Virus) >= 4;
        bool lostByOpponentWin = winnerId.has_value() && p.getId() != winnerId.value();

        if (virusLoss || lostByOpponentWin)
        {
            losers.push_back(p.getId());
        }
    }

    return losers;
}

void Game::printGameOver() const
{
    if (auto winnerOpt = getWinnerId())
    {
        std::cout << "Player " << (*winnerOpt + 1) << " wins!" << std::endl;
    }
    else
    {
        std::vector<int> losers = getLoserIds();
        if (!losers.empty())
        {
            std::cout << "Player";
            if (losers.size() > 1) std::cout << "s";
            for (size_t i = 0; i < losers.size(); ++i)
            {
                if (i > 0) std::cout << ",";
                std::cout << " " << (losers[i] + 1);
            }
            std::cout << " lost" << std::endl;
        }
        else
        {
            std::cout << "Game ended without a winner." << std::endl;
        }
    }
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

void Game::useAbility(int index, const std::vector<std::string> &args)
{
    if (turnHandler.getAbilityPlayed())
    {
        throw std::runtime_error("Ability has already been used this turn.");
    }

    Player &user = getCurrentPlayer();
    user.getAbility(index).use(args, abilityContextProvider);
    turnHandler.setAbilityPlayed(true);
}

const std::vector<Player> &Game::getPlayers() const
{
    return players;
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
