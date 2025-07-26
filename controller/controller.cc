#include "controller.h"

Controller::Controller(int argc, char **argv) : game{std::make_unique<Game>()},
                                                views{std::vector<std::unique_ptr<View>>{}},
                                                commandLineInput{std::make_unique<TextInputHandler>(std::cin)},
                                                fileInput{nullptr},
                                                currentInput{commandLineInput.get()} // initialize directly here

{
    parseArgs(argc, argv);

    game->setup(
        playerAbilities[0],
        playerAbilities[1],
        linkFiles[0] ? &*linkFiles[0] : nullptr,
        linkFiles[1] ? &*linkFiles[1] : nullptr);

    views.push_back(std::make_unique<TextDisplay>(std::cout));

    if (graphics)
    {
        views.push_back(std::make_unique<GraphicDisplay>());
    }

    currentInput = commandLineInput.get();
}

void Controller::parseArgs(int argc, char **argv)
{
    for (int i = 1; i < argc; ++i)
    {
        std::string flag = argv[i];
        if (flag == "-graphics")
        {
            graphics = true;
        }

        else if (flag.rfind("-ability", 0) == 0)
        {
            int id = flag.back() - '1';
            if (id < 0 || id > 1)
                throw std::invalid_argument("Invalid player id for ability");
            if (i + 1 >= argc)
                throw std::invalid_argument(flag + " requires a value.");
            playerAbilities[id] = argv[++i];
        }
        else if (flag.rfind("-link", 0) == 0)
        {
            int id = flag.back() - '1';
            if (id < 0 || id > 1)
                throw std::invalid_argument("Invalid player id for link");
            if (i + 1 >= argc)
                throw std::invalid_argument(flag + " requires a file path.");
            linkFiles[id] = argv[++i];
        }
    }
}

// void Controller::loadLinksFromFile(Player &player, const std::string &file)
// {
//     std::ifstream in(file);
//     if (!in.is_open())
//     {
//         throw std::runtime_error("Could not open link file: " + file);
//     }

//     std::vector<std::string> tokens;
//     std::string token;
//     while (in >> token)
//         tokens.push_back(token);

//     if (tokens.size() != 8)
//     {
//         throw std::runtime_error("Link file must contain exactly 8 tokens.");
//     }

//     char label = player.getId() == 0 ? 'a' : 'A';
//     for (const std::string &t : tokens)
//     {
//         LinkType type = (t[0] == 'V') ? LinkType::Virus : LinkType::Data;
//         int strength = t[1] - '0';
//         auto link = std::make_unique<Link>(label++, player, type, strength);
//         player.addLink(std::move(link));
//     }
// }

// void Controller::assignRandomLinks(Player &player)
// {
//     std::vector<std::pair<LinkType, int>> types;
//     for (int i = 1; i <= 4; ++i)
//     {
//         types.emplace_back(LinkType::Virus, i);
//         types.emplace_back(LinkType::Data, i);
//     }

//     std::shuffle(types.begin(), types.end(), std::mt19937{std::random_device{}()});
//     char label = player.getId() == 0 ? 'a' : 'A';

//     for (const auto &[type, strength] : types)
//     {
//         auto link = std::make_unique<Link>(label++, player, type, strength);
//         player.addLink(std::move(link));
//     }
// }

void Controller::run()
{
    while (!game->isOver())
    {
        try
        {
            Command cmd = currentInput->getNextCommand();

            if (cmd.type == CommandType::Quit &&
                currentInput == fileInput.get())
            {
                // Sequence file ended, revert to command line input
                fileInput.reset();
                currentInput = commandLineInput.get();
                continue;
            }

            switch (cmd.type)
            {
            case CommandType::Move:
            {
                char label = cmd.params[0][0];
                const std::string &dir = cmd.params[1];
                game->moveLink(label, dir);
                notifyViews(); // game state changed
                break;
            }

            case CommandType::Ability:
            {
                int index = std::stoi(cmd.params[0]);
                std::vector<std::string> args(cmd.params.begin() + 1, cmd.params.end());
                game->useAbility(index, args);
                notifyViews(); // game state changed
                break;
            }

            case CommandType::Abilities:
            {
                // TODO: change
                std::cout << game->getCurrentPlayer().printAbilities();
                break;
            }

            case CommandType::Board: // done
            {
                std::cout << TextDisplay::boardStateString(game->getBoard().getState()); // ensure the board is printed EXACTLY as is done for display
                break;
            }

            case CommandType::Sequence:
            {
                std::ifstream file(cmd.params[0]);
                if (!file.is_open())
                {
                    std::cerr << "Failed to open sequence file: " << cmd.params[0] << "\n";
                    break;
                }
                fileInput = std::make_unique<TextInputHandler>(file);
                currentInput = fileInput.get();
                break;
            }

            case CommandType::Quit:
                std::cout << "Quitting game.\n";
                return;
            }

            // onGameUpdate();
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error: " << e.what() << "\n";
        }
    }

    if (auto winnerOpt = game->getWinnerId())
    {
        std::cout << "Player " << (*winnerOpt + 1) << " wins!\n";
    }
    else
    {
        std::cout << "Game ended without a winner.\n";
    }
}

void Controller::notifyViews()
{
    // create a new gameState object - used to decouple model interfaces from Views
    GameState state{game->getBoard(), game->getPlayers(), game->getCurrentPlayer().getId()};

    for (const auto &view : views)
    {
        view->notify(state);
    }
}

// void Controller::onGameUpdate()
// {
//     notifyViews();
// }
