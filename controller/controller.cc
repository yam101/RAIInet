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
        // Controller owns the output file streams
        outputFiles.push_back(std::make_unique<std::ofstream>("player1.out"));
        outputFiles.push_back(std::make_unique<std::ofstream>("player2.out"));
        
        if (!outputFiles[0]->is_open() || !outputFiles[1]->is_open()) {
            throw std::runtime_error("Failed to open output files for dual display");
        }
        
        views.push_back(std::make_unique<PlayerSpecificTextDisplay>(0, *outputFiles[0]));
        views.push_back(std::make_unique<PlayerSpecificTextDisplay>(1, *outputFiles[1]));
    }
    else
    {
        // Controller passes reference to cout (lives forever, safe to reference)
        views.push_back(std::make_unique<ColoredTextDisplay>(std::cout));
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
        std::string flag = argv[i];
        if (flag == "-graphics")
        {
            graphics = true;
        }
        else if (flag == "-dual")
        {
            dual = true;
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
                std::cout << "Sequence file ended, reverting to command line input.\n";
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
