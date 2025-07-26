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
        views.push_back(std::make_unique<GraphicDisplay>(game->getBoard().getSize())); // use board size to set window dimensions
    }

    currentInput = commandLineInput.get();
    notifyViews(); // initial state
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
                // check 1st parameter is a digit
                if (!std::all_of(cmd.params[0].begin(), cmd.params[0].end(), ::isdigit)) {
                    throw std::runtime_error("Ability ID must be a number");
                }
                
                int index = std::stoi(cmd.params[0]) - 1;
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
