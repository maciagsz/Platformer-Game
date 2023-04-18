#include "../Headers/MainMenu.h"
#include "../Headers/InputName.h"
#include "../Headers/HallOfFame.h"

MainMenu::MainMenu(std::shared_ptr<Context>& context)
	: context(context), is_play_button_selected(true),
	is_play_button_pressed(false), is_exit_button_selected(false),
	is_exit_button_pressed(false), is_hall_of_fabe_button_pressed(false),
	is_hall_of_fabe_button_selected(false), selected_option(0)
{
	view.setSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	view.setCenter(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
}

MainMenu::~MainMenu()
{
}

void MainMenu::Init()
{
	font_holder.loadResource(Fonts::ID::MenuFont, "Resources/fonts/love_glitch.ttf");
	font_holder.loadResource(Fonts::ID::TitleFont, "Resources/fonts/ugly_byte.otf");
	menu_textures.loadResource(Textures::ID::TitleScreenBackground, "Resources/textures/menu/title_screen_background.png");
	sf::Texture& background_texture = menu_textures.getResource(Textures::ID::TitleScreenBackground);
	background_texture.setRepeated(true);
	background_sprite.setTexture(menu_textures.getResource(Textures::ID::TitleScreenBackground));
	background_sprite.setTextureRect(sf::IntRect(0, 0, TILE_SIZE * WORLD_WIDTH, TILE_SIZE * WORLD_HEIGHT));

	// Title
	game_title.setFont(font_holder.getResource(Fonts::ID::TitleFont));
	game_title.setString("Game");
	game_title.setCharacterSize(350);
	game_title.setOutlineThickness(3);
	game_title.setOutlineColor(sf::Color::Black);
	game_title.setOrigin(game_title.getLocalBounds().width / 2,
		game_title.getLocalBounds().height / 2);
	game_title.setPosition(context->m_window->getSize().x / 2,
		context->m_window->getSize().y / 2 - 400.f);

	// Play Button
	play_button.setFont(font_holder.getResource(Fonts::ID::MenuFont));
	play_button.setString("Play");
	play_button.setCharacterSize(120);
	play_button.setOrigin(play_button.getLocalBounds().width / 2,
		play_button.getLocalBounds().height / 2);
	play_button.setPosition(context->m_window->getSize().x / 2,
		context->m_window->getSize().y / 2 - 50.f);

	// Exit Button
	exit_button.setFont(font_holder.getResource(Fonts::ID::MenuFont));
	exit_button.setString("Exit");
	exit_button.setCharacterSize(120);
	exit_button.setOrigin(exit_button.getLocalBounds().width / 2,
		exit_button.getLocalBounds().height / 2);
	exit_button.setPosition(context->m_window->getSize().x / 2,
		context->m_window->getSize().y / 2 + 100.f);

	// Hall Of Fame
	hall_of_fame_button.setFont(font_holder.getResource(Fonts::ID::MenuFont));
	hall_of_fame_button.setString("Hall of Fame");
	hall_of_fame_button.setCharacterSize(120);
	hall_of_fame_button.setOrigin(hall_of_fame_button.getLocalBounds().width / 2,
		hall_of_fame_button.getLocalBounds().height / 2);
	hall_of_fame_button.setPosition(context->m_window->getSize().x / 2,
		context->m_window->getSize().y / 2 + 250.f);
}

void MainMenu::ProcessInput()
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
				if (selected_option > 0)
					selected_option--;

				break;
			}
			case sf::Keyboard::Down:
			{
				if (selected_option < 2)
					selected_option++;

				break;
			}
			case sf::Keyboard::Return:
			{
				is_play_button_pressed = false;
				is_exit_button_pressed = false;

				if (is_play_button_selected)
				{
					is_play_button_pressed = true;
				}
				else if (is_exit_button_selected)
				{
					is_exit_button_pressed = true;
				}
				else
				{
					is_hall_of_fabe_button_pressed = true;
				}

				break;
			}
			default:
			{
				break;
			}
			}

			switch (selected_option)
			{
			case 0:
				if (!is_play_button_selected)
				{
					is_play_button_selected = true;
					is_exit_button_selected = false;
					is_hall_of_fabe_button_selected = false;
				}
				break;

			case 1:
				if (!is_exit_button_selected)
				{
					is_play_button_selected = false;
					is_exit_button_selected = true;
					is_hall_of_fabe_button_selected = false;
				}
				break;

			case 2:
				if (!is_hall_of_fabe_button_selected)
				{
					is_play_button_selected = false;
					is_exit_button_selected = false;
					is_hall_of_fabe_button_selected = true;
				}
				break;
			default:
				break;
			}
		}
	}
}

void MainMenu::Update(sf::Time deltaTime)
{
	background_sprite.move(deltaTime.asMilliseconds() * -0.1, 0);

	if (is_play_button_selected)
	{
		play_button.setFillColor(sf::Color::Black);
		exit_button.setFillColor(sf::Color::White);
		hall_of_fame_button.setFillColor(sf::Color::White);
	}
	else if (is_exit_button_selected)
	{
		exit_button.setFillColor(sf::Color::Black);
		play_button.setFillColor(sf::Color::White);
		hall_of_fame_button.setFillColor(sf::Color::White);
	}
	else
	{
		hall_of_fame_button.setFillColor(sf::Color::Black);
		exit_button.setFillColor(sf::Color::White);
		play_button.setFillColor(sf::Color::White);
	}

	if (is_play_button_pressed)
	{
		is_play_button_pressed = false;
		context->m_states->Add(std::make_unique<InputName>(context), true);
	}
	else if (is_exit_button_pressed)
	{
		is_exit_button_pressed = false;
		context->m_window->close();
	}
	else if (is_hall_of_fabe_button_pressed)
	{
		is_hall_of_fabe_button_pressed = false;
		context->m_states->Add(std::make_unique<HallOfFame>(context), true);
	}
}

void MainMenu::Draw()
{
	context->m_window->clear(sf::Color(220, 247, 255));
	context->m_window->draw(background_sprite);
	context->m_window->draw(game_title);
	context->m_window->draw(play_button);
	context->m_window->draw(exit_button);
	context->m_window->draw(hall_of_fame_button);
	context->m_window->setView(view);
	context->m_window->display();
}