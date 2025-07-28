#include "controller.h"

Controller::Controller() : game{std::make_unique<Game>()},
                           views{std::vector<std::unique_ptr<View>>{}},
                           commandLineInput{nullptr},
                           fileInput{nullptr},
                           currentInput{nullptr}
{
}

void Controller::init(int argc, char **argv)
{
    bool graphics = false;
    bool dual = false;
    bool french = false;
    const std::string defaultAbilities = "BFDSP";
    std::vector<std::string> playerAbilities = {defaultAbilities, defaultAbilities};
    std::vector<std::optional<std::string>> linkFiles = {std::nullopt, std::nullopt};

    parseArgs(argc, argv, graphics, dual, french, playerAbilities, linkFiles);

    if (french)
    {
        commandLineInput = std::make_unique<FrInputHandler>(std::cin);
    }
    else
    {
        commandLineInput = std::make_unique<EnInputHandler>(std::cin);
    }
    currentInput = commandLineInput.get();

    setupGame(graphics, dual, playerAbilities, linkFiles);
    notifyViews();
}

void Controller::parseArgs(int argc, char **argv, bool &graphics, bool &dual, bool &french,
                           std::vector<std::string> &playerAbilities,
                           std::vector<std::optional<std::string>> &linkFiles)
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
        else if (flag == "-fr")
        {
            french = true;
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

void Controller::setupGame(bool graphics, bool dual,
                           const std::vector<std::string> &playerAbilities,
                           const std::vector<std::optional<std::string>> &linkFiles)
{
    game->setup(
        playerAbilities[0],
        playerAbilities[1],
        linkFiles[0] ? &*linkFiles[0] : nullptr,
        linkFiles[1] ? &*linkFiles[1] : nullptr);

    if (dual)
    {
        // create two player-specific displays, each outputting to their own file
        outputFiles.push_back(std::make_unique<std::ofstream>("player1.out"));
        outputFiles.push_back(std::make_unique<std::ofstream>("player2.out"));

        if (!outputFiles[0]->is_open() || !outputFiles[1]->is_open())
        {
            throw std::runtime_error("Failed to open output files for dual display");
        }

        views.push_back(std::make_unique<PlayerSpecificTextDisplay>(0, *outputFiles[0]));
        views.push_back(std::make_unique<PlayerSpecificTextDisplay>(1, *outputFiles[1]));
    }
    else
    {
        views.push_back(std::make_unique<ColoredTextDisplay>(std::cout));
    }

    if (graphics)
    {
        views.push_back(std::make_unique<GraphicDisplay>(game->getBoard().getSize())); // use board size to set window dimensions
    }
}

void Controller::run() // main game loop
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
                game->Move(cmd.params);
                notifyViews();
                break;
            }

            case CommandType::Ability:
            {
                game->Ability(cmd.params);
                notifyViews(); // game state changed
                break;
            }

            case CommandType::Abilities:
            {
                std::cout << game->Abilities();
                break;
            }

            case CommandType::Board:
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

                fileStream = std::make_unique<std::ifstream>(cmd.params[0]);
                if (!fileStream->is_open())
                {
                    throw std::runtime_error("Failed to open file: " + cmd.params[0]);
                }

                // determine language from commandLineInput type
                if (dynamic_cast<FrInputHandler *>(commandLineInput.get()))
                {
                    fileInput = std::make_unique<FrInputHandler>(*fileStream);
                }
                else
                {
                    fileInput = std::make_unique<EnInputHandler>(*fileStream);
                }
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

    onGameOver(); // notify views when game is over
}

void Controller::notifyViews()
{
    // create a new gameState object - used to decouple model interfaces from Views
    GameState state{
        game->getBoard(),
        game->getPlayers(),
        game->getCurrentPlayer().getId(),
    };

    for (const auto &view : views)
    {
        view->notify(state);
    }
}

void Controller::onGameOver()
{
    int winner = game->getWinnerId();
    std::vector<int> losers = game->getLoserIds();

    WinState state{winner, losers};
    for (const auto &view : views)
    {
        view->notifyWin(state);
    }

    // prompt the user to press enter to quit
    std::cout << "Press ENTER to exit...";
    std::string dummy;
    std::getline(std::cin, dummy);
}
