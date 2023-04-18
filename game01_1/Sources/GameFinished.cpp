#include "../Headers/GameFinished.h"
#include "../Headers/Game.h"
#include "../Headers/MainMenu.h"

GameFinished::GameFinished(std::shared_ptr<Context>& context)
	: context(context), is_retry_button_selected(true),
	is_retry_button_pressed(false), is_exit_button_selected(false),
	is_exit_button_pressed(false)
{
	view.setSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	view.setCenter(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
}

GameFinished::~GameFinished()
{
}

void GameFinished::Init()
{
	font_holder.loadResource(Fonts::ID::MenuFont, "Resources/fonts/love_glitch.ttf");
	font_holder.loadResource(Fonts::ID::TitleFont, "Resources/fonts/ugly_byte.otf");
	font_holder.loadResource(Fonts::ID::Score, "Resources/fonts/mc_regular.otf");
	// Title
	game_over_title.setFont(font_holder.getResource(Fonts::ID::TitleFont));
	game_over_title.setString("You won!");
	game_over_title.setCharacterSize(350);
	game_over_title.setFillColor(sf::Color::Black);
	game_over_title.setOrigin(game_over_title.getLocalBounds().width / 2,
		game_over_title.getLocalBounds().height / 2);
	game_over_title.setPosition(context->m_window->getSize().x / 2,
		context->m_window->getSize().y / 2 - 400.f);

	//Score
	player_score.setFont(font_holder.getResource(Fonts::ID::Score));
	player_score.setString("Your score: " + *variables::getPlayerScore());
	player_score.setCharacterSize(50);
	player_score.setFillColor(sf::Color::Black);
	player_score.setOrigin(retry_button.getLocalBounds().width / 2,
		retry_button.getLocalBounds().height / 2);
	player_score.setPosition(context->m_window->getSize().x / 2 - 250,
		context->m_window->getSize().y / 2);

	// Play Button
	retry_button.setFont(font_holder.getResource(Fonts::ID::MenuFont));
	retry_button.setString("Play again");
	retry_button.setCharacterSize(120);
	retry_button.setOrigin(retry_button.getLocalBounds().width / 2,
		retry_button.getLocalBounds().height / 2);
	retry_button.setPosition(context->m_window->getSize().x / 2,
		context->m_window->getSize().y / 2 + 100.f);

	// Exit Button
	exit_button.setFont(font_holder.getResource(Fonts::ID::MenuFont));
	exit_button.setString("Return to main menu");
	exit_button.setCharacterSize(120);
	exit_button.setOrigin(exit_button.getLocalBounds().width / 2,
		exit_button.getLocalBounds().height / 2);
	exit_button.setPosition(context->m_window->getSize().x / 2,
		context->m_window->getSize().y / 2 + 250.f);
}

void GameFinished::ProcessInput()
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
			case sf::Keyboard::Up:
			{
				if (!is_retry_button_selected)
				{
					is_retry_button_selected = true;
					is_exit_button_selected = false;
				}
				break;
			}
			case sf::Keyboard::Down:
			{
				if (!is_exit_button_selected)
				{
					is_retry_button_selected = false;
					is_exit_button_selected = true;
				}
				break;
			}
			case sf::Keyboard::Return:
			{
				is_retry_button_pressed = false;
				is_exit_button_pressed = false;

				if (is_retry_button_selected)
				{
					is_retry_button_pressed = true;
				}
				else
				{
					is_exit_button_pressed = true;
				}

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

void GameFinished::Update(sf::Time deltaTime)
{
	if (is_retry_button_selected)
	{
		retry_button.setFillColor(sf::Color::Black);
		exit_button.setFillColor(sf::Color::White);
	}
	else
	{
		exit_button.setFillColor(sf::Color::Black);
		retry_button.setFillColor(sf::Color::White);
	}

	if (is_retry_button_pressed)
	{
		context->m_states->Add(std::make_unique<InputName>(context), true);
	}
	else if (is_exit_button_pressed)
	{
		context->m_states->Add(std::make_unique<MainMenu>(context), true);
	}
}

void GameFinished::Draw()
{
	context->m_window->clear(sf::Color(220, 247, 255));
	context->m_window->draw(game_over_title);
	context->m_window->draw(retry_button);
	context->m_window->draw(exit_button);
	context->m_window->draw(player_score);
	context->m_window->setView(view);
	context->m_window->display();
}