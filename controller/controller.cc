#include "controller.h"

Controller::Controller(int argc, char **argv) : game{std::make_unique<Game>()},
                                                views{std::vector<std::unique_ptr<View>>{}},
                                                commandLineInput{std::make_unique<TextInputHandler>(std::cin)},
                                                fileInput{nullptr},
                                                currentInput{commandLineInput.get()}
{
    parseArgs(argc, argv);

    game->setup(
        playerAbilities[0],
        playerAbilities[1],
        linkFiles[0] ? &*linkFiles[0] : nullptr,
        linkFiles[1] ? &*linkFiles[1] : nullptr);

    if (dual)
    {
        // create two player-specific displays, each outputting to their own file
        views.push_back(std::make_unique<PlayerSpecificTextDisplay>(0, "player1.out"));
        views.push_back(std::make_unique<PlayerSpecificTextDisplay>(1, "player2.out"));
    }
    else
    {
        views.push_back(std::make_unique<ColoredTextDisplay>());
    }

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
        std::string arg = argv[i];

        if (arg == "-graphics")
        {
            graphics = true;
        }
        else if (arg == "-text")
        {
            dual = true;
        }
        else if (arg == "-ability1")
        {
            if (i + 1 < argc)
            {
                playerAbilities[0] = argv[++i]; // Get the next argument as the abilities for player 1
            }
        }
        else if (arg == "-ability2")
        {
            if (i + 1 < argc)
            {
                playerAbilities[1] = argv[++i]; // Get the next argument as the abilities for player 2
            }
        }
        else if (arg == "-link1")
        {
            if (i + 1 < argc)
            {
                linkFiles[0] = argv[++i]; // Link file for player 1
            }
        }
        else if (arg == "-link2")
        {
            if (i + 1 < argc)
            {
                linkFiles[1] = argv[++i]; // Link file for player 2
            }
        }
    }
}

void Controller::run()
{
    notifyViews();

    while (!game->isOver())
    {
        try
        {
            Command cmd = currentInput->getNextCommand();

            switch (cmd.type)
            {
            case CommandType::Move:
            {
                if (cmd.params.size() != 2)
                {
                    throw std::invalid_argument("move requires a link and a direction");
                }
                game->moveLink(cmd.params[0][0], cmd.params[1]);
                notifyViews();
                break;
            }

            case CommandType::Abilities:
            {
                std::cout << game->getCurrentPlayer().printAbilities() << "\n";
                break;
            }

            case CommandType::Ability:
            {
                if (cmd.params.size() < 1)
                {
                    throw std::invalid_argument("ability requires at least an index");
                }

                int index = std::stoi(cmd.params[0]) - 1; // user gives 1-indexed
                std::vector<std::string> abilityArgs(cmd.params.begin() + 1, cmd.params.end());
                game->useAbility(index, abilityArgs);
                notifyViews();
                break;
            }

            case CommandType::Board:
            {
                notifyViews();
                break;
            }

            case CommandType::Sequence:
            {
                if (cmd.params.size() != 1)
                {
                    throw std::invalid_argument("sequence requires a filename");
                }

                if (currentInput == fileInput.get())
                {
                    throw std::runtime_error("Already running sequence file.");
                    break;
                }

                std::cout << "Running sequence file: " << cmd.params[0] << "\n";

                // Controller owns the file stream
                fileStream = std::make_unique<std::ifstream>(cmd.params[0]);
                if (!fileStream->is_open()) {
                    throw std::runtime_error("Failed to open file: " + cmd.params[0]);
                }
                
                // Create TextInputHandler with reference to owned file stream
                fileInput = std::make_unique<TextInputHandler>(*fileStream);
                currentInput = fileInput.get();
                notifyViews();
                break;
            }

            case CommandType::Quit:
            {
                std::cout << "Quitting game.\n";
                return;
            }
            }

        }
        catch (const std::exception &e)
        {
            std::cerr << "Error: " << e.what() << "\n";
        }
    }

    game->printGameOver();
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
