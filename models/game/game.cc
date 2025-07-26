#include "game.h"
#include <iostream>

Game::Game()
    : board(std::make_unique<Board>()),
      turnHandler{},
      abilityFactory{},
      abilityContextProvider(*this) // *this is safe here bc init order is defined
{
}

Link &Game::getUserLink(char label)
{
    Player &user = players.at(turnHandler.getCurrentPlayerIndex());
    int userId = user.getId();
    // std::cout << "User ID: " << userId << std::endl;
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

bool Game::handleDownloadEdge(Player &user, Link &link, const Position &from, const Direction &moveDir)
{
    const Cell &fromCell = board->at(from);
    // std::cout << "Checking download edge at " << from.row << ", " << from.col << std::endl;
    if (!fromCell.hasFeature<DownloadEdge>())
    {
        return false; // not a download edge, normal move
    }

    const DownloadEdge &edge = fromCell.getFeature<DownloadEdge>();

    if (user.getId() == edge.getDownloader().getId() && moveDir == edge.getDirection())
    {
        edge.getDownloader().downloadLink(link);
        board->removeLink(from);
        endTurn();
        return true;
    }
    return false;

    endTurn();
    return true;
}

void Game::moveLinkHelper(Link &link, const Direction &direction)
{
    Player &user = getCurrentPlayer();
    // std::cout << "Moving link " << link.getLabel() << std::endl;
    Position from = board->findLinkPosition(link);

    if (from == Position{-1, -1}) // Link not found
    {
        throw std::runtime_error("Link not found on board->");
    }

    // check if link moves off the board
    if (handleDownloadEdge(user, link, from, direction))
        return; // skip the actual cell moving logic

    Position to = link.getMovementStrategy().getNewPos(from, direction);
    if (!board->isValidPosition(to))
    {
        throw std::out_of_range("Invalid move destination: " + std::to_string(to.row) + ", " + std::to_string(to.col));
    }

    // get destination cell and link (if it exists)
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
    std::transform(d.begin(), d.end(), d.begin(), ::tolower); // wtf

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
    return getWinnerId().has_value();
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
