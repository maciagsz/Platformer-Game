#ifndef GAMEINTERFACE_H
#define GAMEINTERFACE_H

import Headers;
#include "StateMan.h"

extern std::string playername;

constexpr auto WINDOW_WIDTH = 1280;
constexpr auto WINDOW_HEIGHT = 1024;

struct Context
{
    std::unique_ptr<Engine::StateMan> m_states;
    std::unique_ptr<sf::RenderWindow> m_window;

    Context()
    {
        m_states = std::make_unique<Engine::StateMan>();
        m_window = std::make_unique<sf::RenderWindow>();
    }
};

class GameInterface
{
    std::shared_ptr<Context> context;
    static const sf::Time time_per_frame;

public:
    GameInterface();
    ~GameInterface();

    void Run();
};

#endif //!GAMEINTERFACE_H