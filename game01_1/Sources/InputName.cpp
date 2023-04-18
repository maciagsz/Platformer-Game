#include "../Headers/InputName.h"
#include "../Headers/Game.h"
#include "../Headers/MainMenu.h"

InputName::InputName(std::shared_ptr<Context>& context)
    : context(context)
{
    view.setSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    view.setCenter(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
}

InputName::~InputName()
{
}

void InputName::Init()
{
    font_holder.loadResource(Fonts::ID::Score, "Resources/fonts/mc_regular.otf");
    m_enterName.setFont(font_holder.getResource(Fonts::ID::Score));
    m_enterName.setString("Enter your name");
    m_enterName.setCharacterSize(50);
    m_enterName.setFillColor(sf::Color::Black);
    //m_enterName.setOutlineColor(sf::Color::Black);
    //m_enterName.setOutlineThickness(1);
    m_enterName.setOrigin(m_enterName.getLocalBounds().width / 2,
        m_enterName.getLocalBounds().height / 2);
    m_enterName.setPosition(context->m_window->getSize().x / 2,
        context->m_window->getSize().y / 2 - 300);

    player_text.setFont(font_holder.getResource(Fonts::ID::Score));
    player_text.setCharacterSize(50);
    player_text.setFillColor(sf::Color::Black);
}

void InputName::ProcessInput()
{
    sf::Event event;
    while (context->m_window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            context->m_window->close();
        }
        else if (event.type == sf::Event::KeyPressed)
        {
            switch (event.key.code)
            {
            case sf::Keyboard::Escape:
            {
                context->m_states->Add(std::make_unique<MainMenu>(context));
                break;
            }
            case sf::Keyboard::Enter:
            {
                variables::setPlayerName(player_text.getString());
                context->m_states->Add(std::make_unique<Game>(context), true);
            }
            default:
            {
                break;
            }
            }
        }
        else if (event.type == sf::Event::TextEntered)
        {
            if (player_input.getSize() < 8)
            {
                std::string tempchar;
                tempchar.push_back((char)event.text.unicode);
                std::regex pattern("([a-zA-Z]{1})");
                if (std::regex_match(tempchar, pattern))
                {
                    player_input += event.text.unicode;
                    player_text.setString(player_input);
                }
            }
            if (event.text.unicode == 8)
            {
                if (player_input.getSize() > 0)
                {
                    player_input.erase(player_input.getSize() - 1);
                    player_text.setString(player_input);
                }
            }
        }
    }
}

void InputName::Update(sf::Time deltaTime)
{
    player_text.setOrigin(m_enterName.getLocalBounds().width / 2,
        m_enterName.getLocalBounds().height / 2);
    player_text.setPosition(context->m_window->getSize().x / 2,
        context->m_window->getSize().y / 2);
}

void InputName::Draw()
{
    context->m_window->clear(sf::Color(220, 247, 255));
    context->m_window->draw(m_enterName);
    context->m_window->draw(player_text);
    context->m_window->setView(view);
    context->m_window->display();
}