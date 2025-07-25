#include "game.h"
#include "player/player.h"
#include "turnhandler.h"
#include "board/downloadedge.h"
#include "link/link.h"
#include "link/movementstrategy.h"

Link &Game::getUserLink(char label)
{
    Player &user = players.at(turnHandler.getCurrentPlayerIndex());
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

    Link &winnerLink = attackerWins ? attacker : defender;
    Link &loserLink = attackerWins ? defender : attacker;

    Player &winner = winnerLink.getOwner();

    // winner downloads the link of the loser
    winner.downloadLink(loserLink);

    // remove attacker link from original position
    board->removeLink(from);

    if (attackerWins)
    {
        board->removeLink(to);           // remove defender
        board->placeLink(attacker, to); // attacker moves in
    }
    // else: attacker loses, it was removed and defender stays put
}

bool Game::handleDownloadEdge(Link &link, const Position &from, const Direction &moveDir)
{
    const Cell &fromCell = board->at(from);
    try {
        const DownloadEdge& edge = fromCell.getFeature<DownloadEdge>();

        if (moveDir != edge.getDirection())
        {
            throw std::invalid_argument("Invalid direction for download edge.");
        }
        edge.getDownloader().downloadLink(link);
        board->removeLink(from);
    } catch (const std::runtime_error&) {
        throw std::invalid_argument("Cannot move off board in this direction.");
    }
    
    endTurn(); 
    return true;
} 

void Game::moveLinkHelper(Link &link, const Direction& direction)
{   
    Player &user = getCurrentPlayer();
    Position from = board->findLinkPosition(link);

    if (from == Position{-1, -1}) // Link not found
    {
        throw std::runtime_error("Link not found on board->");
    }

    Position to = link.getMovementStrategy().getNewPos(from, direction);

    // check if link moves off the board
    if (handleDownloadEdge(link, from, direction))
        return; // skip the actual cell moving logic
    
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
    if(!destCell.hasLink())
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

Direction Game::parseDirection(const std::string &dirStr) {
    std::string d = dirStr;
    std::transform(d.begin(), d.end(), d.begin(), ::tolower); // wtf

    if (d == "up") return Direction::Up;
    if (d == "down") return Direction::Down;
    if (d == "left") return Direction::Left;
    if (d == "right") return Direction::Right;

    throw std::invalid_argument("Invalid direction: " + dirStr);
}

void Game::moveLink(char label, const std::string &direction)
{
    Direction dir = parseDirection(direction);
    moveLinkHelper(getUserLink(label), dir);
    endTurn();
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



Board &Game::getBoard() {
    return *board;
}

TurnHandler &Game::getTurnHandler() {
    return turnHandler;
}

Player &Game::getCurrentPlayer() {
    return players.at(turnHandler.getCurrentPlayerIndex());
}

void Game::useAbility(int index, const std::vector<std::string> &args){
    int abilityIndex = std::stoi(args[0]);
    Player &user = getCurrentPlayer();
    user.getAbility(abilityIndex).use(std::vector<std::string>(args.begin() + 1, args.end()), abilityContextProvider);
}

const std::vector<Player> &Game::getPlayers() const{
    return players;
}
