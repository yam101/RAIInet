#include "controller.h"

Controller::Controller(bool graphicsEnabled)
{
    game = std::make_unique<Game>();
    commandLineInput = std::make_unique<TextInputHandler>(std::cin);
    currentInput = commandLineInput.get();

    views.push_back(std::make_unique<TextDisplay>());
    if (graphicsEnabled)
    {
        views.push_back(std::make_unique<GraphicDisplay>());
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
                break;
            }

            case CommandType::Ability:
            {
                int index = std::stoi(cmd.params[0]);
                std::vector<std::string> args(cmd.params.begin() + 1, cmd.params.end());
                game->useAbility(index, args);
                break;
            }

            case CommandType::Abilities:
            {
                // TODO: change
                std::cout << game->getCurrentPlayer().printAbilities();
                break;
            }

            case CommandType::Board:
            {
                // TODO: change
                std::cout << game->getBoard().printBoard();
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

            onGameUpdate();
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
    for (const auto &view : views)
    {
        // view->notify(game->getPlayers(), game->getBoard(), game->getCurrentPlayer().getId());
    }
}

void Controller::onGameUpdate()
{
    notifyViews();
}
