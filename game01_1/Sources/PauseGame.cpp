#include "../Headers/PauseGame.h"

PauseGame::PauseGame(std::shared_ptr<Context>& context)
	: context(context)
{
	view.setSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	view.setCenter(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
}

PauseGame::~PauseGame()
{
}

void PauseGame::Init()
{
	font_holder.loadResource(Fonts::ID::Score, "Resources/fonts/mc_regular.otf");
	pause_game_title.setFont(font_holder.getResource(Fonts::ID::Score));
	pause_game_title.setString("Paused");
	pause_game_title.setCharacterSize(150);
	pause_game_title.setOutlineColor(sf::Color::Black);
	pause_game_title.setOutlineThickness(1
	);
	pause_game_title.setOrigin(pause_game_title.getLocalBounds().width / 2,
		pause_game_title.getLocalBounds().height / 2);
	pause_game_title.setPosition(context->m_window->getSize().x / 2,
		context->m_window->getSize().y / 2);

	context->m_window->setView(view);
}

void PauseGame::ProcessInput()
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
				context->m_states->PopCurrent();
				break;
			}
			default:
			{
				break;
			}
			}
		}
	}
}

void PauseGame::Update(sf::Time deltaTime)
{
}

void PauseGame::Draw()
{
	context->m_window->draw(pause_game_title);
	context->m_window->display();
}