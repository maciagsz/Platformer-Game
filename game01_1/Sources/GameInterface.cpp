#include "../Headers/GameInterface.h"
#include "../Headers/MainMenu.h"

const sf::Time GameInterface::time_per_frame = sf::seconds(1.f / 120.f);

GameInterface::GameInterface() : context(std::make_shared<Context>())
{
    context->m_window->create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Game v01", sf::Style::Default);
    context->m_window->setKeyRepeatEnabled(false);
    if (!context->m_window->hasFocus())
        context->m_window->requestFocus();
    context->m_states->Add(std::make_unique<MainMenu>(context));
}

GameInterface::~GameInterface()
{
}

void GameInterface::Run()
{
    sf::Clock clock;
    sf::Time timeSinceLastFrame = sf::Time::Zero;

    while (context->m_window->isOpen())
    {
        timeSinceLastFrame += clock.restart();

        while (timeSinceLastFrame > time_per_frame)
        {
            timeSinceLastFrame -= time_per_frame;

            context->m_states->ProcessStateChange();
            context->m_states->GetCurrent()->ProcessInput();
            context->m_states->GetCurrent()->Update(time_per_frame);
            context->m_states->GetCurrent()->Draw();
        }
    }
}