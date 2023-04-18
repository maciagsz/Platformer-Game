#include "../Headers/Game.h"
#include "../Headers/World.h"
#include "../Headers/MainMenu.h"
#include "../Headers/PauseGame.h"
#include "../Headers/GameOver.h"
#include "../Headers/GameFinished.h"

const sf::Time Game::time_per_frame = sf::seconds(1.f / 120.f);

Game::Game(std::shared_ptr<Context>& context)
	: context(context),
	tile_size(TILE_SIZE + 1, TILE_SIZE + 1)
{
}

Game::~Game()
{
}

void Game::Init()
{
	view.setSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	world.worldInitialize();
	worldobjectInitialize();
}

void Game::ProcessInput()
{
	sf::Event event;
	while (context->m_window->pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::KeyPressed:
			player.handlePlayerInput(event.key.code, true);
			break;
		case sf::Event::KeyReleased:
			player.handlePlayerInput(event.key.code, false);
			break;
		case sf::Event::GainedFocus:
			is_paused = false;
			break;
		case sf::Event::LostFocus:
			player.resetMovement();
			is_paused = true;
			break;
		case sf::Event::Closed:
			context->m_window->close();
			break;
		}
	}
}

void Game::playerCollisionCheck()
{
	player.move();
	auto collision = new Collision(player, world, worldobject);
	collision->checkCollision();
	delete collision;
	player.updatePos(time_per_frame);
}

void Game::viewFollow()
{
	int offset = 0;

	if (player.is_moving_right && player.movement.x != 0)
		offset = 10;

	if (player.is_moving_left && player.movement.x != 0)
		offset = -10;

	if (player.is_moving_right && player.is_moving_left)
		offset = 0;

	float camera_x = std::lerp(view.getCenter().x + offset, player.player_sprite.getPosition().x, 0.05f);

	if (camera_x < static_cast<float>(WINDOW_WIDTH) / 2)
		camera_x = static_cast<float>(WINDOW_WIDTH) / 2;

	if (camera_x > 15744)
		camera_x = 15744;

	view.setCenter(round(camera_x), static_cast<float>(WINDOW_HEIGHT) / 2);
	world.background_sprite.setPosition(camera_x * 0.5 - 512, 0);
}

void Game::Update(sf::Time deltaTime)
{
	if (player.is_paused or is_paused)
	{
		is_paused = false;
		player.is_paused = false;
		context->m_states->Add(std::make_unique<PauseGame>(context), false);
	}

	if (world.is_finished)
		close(); //todo: add level finish

	score.update(player, sf::Vector2f(view.getCenter().x, 0));
	if (player.is_dead)
		context->m_states->Add(std::make_unique<GameOver>(context), true);
	playerCollisionCheck();
	player.update();
	viewFollow();
}

void Game::Draw()
{
	context->m_window->clear(sf::Color(220, 247, 255));
	context->m_window->draw(world);
	context->m_window->draw(worldobject);
	context->m_window->draw(player);
	context->m_window->draw(score);
	context->m_window->setView(view);
	context->m_window->display();
}

void Game::close()
{
	if (!player.is_dead)
	{
		std::ofstream file;
		file.open("scores.txt", std::ios::app);
		file << score.integer_score << " " << *variables::getPlayerName() << "\n";
		file.close();
	}

	std::stringstream s_score;
	s_score << score.integer_score;
	std::string _tempscore = s_score.str();
	variables::setPlayerScore(_tempscore);

	context->m_states->Add(std::make_unique<GameFinished>(context), true);
}

void Game::worldobjectInitialize()
{
	using namespace Textures;

	worldobject.create(Bush1, sf::Vector2f(TILE_SIZE * 0, TILE_SIZE * 3));
	worldobject.create(Bush1, sf::Vector2f(TILE_SIZE * 11, TILE_SIZE * 4));
	worldobject.create(Bush1, sf::Vector2f(TILE_SIZE * 20, TILE_SIZE * 4));
	worldobject.create(Bush1, sf::Vector2f(TILE_SIZE * 44, TILE_SIZE * 2));
	worldobject.create(Bush1, sf::Vector2f(TILE_SIZE * 102, TILE_SIZE * 2));
	worldobject.create(Bush1, sf::Vector2f(TILE_SIZE * 123, TILE_SIZE * 4));
	worldobject.create(Bush2, sf::Vector2f(TILE_SIZE * 23, TILE_SIZE * 2));
	worldobject.create(Bush2, sf::Vector2f(TILE_SIZE * 46, TILE_SIZE * 1));
	worldobject.create(Bush2, sf::Vector2f(TILE_SIZE * 91, TILE_SIZE * 1));
	worldobject.create(Bush2, sf::Vector2f(TILE_SIZE * 116, TILE_SIZE * 3));
	worldobject.create(Crate, sf::Vector2f(TILE_SIZE * 18, TILE_SIZE));
	worldobject.create(Crate, sf::Vector2f(TILE_SIZE * 37, TILE_SIZE * 3));
	worldobject.create(Crate, sf::Vector2f(TILE_SIZE * 58, TILE_SIZE * 4));
	worldobject.create(Crate, sf::Vector2f(TILE_SIZE * 74, TILE_SIZE * 4));
	worldobject.create(Crate, sf::Vector2f(TILE_SIZE * 98, TILE_SIZE * 3));
	worldobject.create(Mushroom, sf::Vector2f(TILE_SIZE * 14, TILE_SIZE * 3));
	worldobject.create(Mushroom, sf::Vector2f(TILE_SIZE * 19, TILE_SIZE * 1));
	worldobject.create(Mushroom, sf::Vector2f(TILE_SIZE * 34, TILE_SIZE * 4));
	worldobject.create(Mushroom, sf::Vector2f(TILE_SIZE * 5, TILE_SIZE * 3));
	worldobject.create(Mushroom, sf::Vector2f(TILE_SIZE * 53, TILE_SIZE * 3));
	worldobject.create(Mushroom, sf::Vector2f(TILE_SIZE * 63, TILE_SIZE * 3));
	worldobject.create(Mushroom, sf::Vector2f(TILE_SIZE * 89, TILE_SIZE * 1));
	worldobject.create(Mushroom, sf::Vector2f(TILE_SIZE * 106, TILE_SIZE * 1));
	worldobject.create(Mushroom, sf::Vector2f(TILE_SIZE * 119, TILE_SIZE * 2));
	worldobject.create(Sign, sf::Vector2f(TILE_SIZE * 1, TILE_SIZE * 3));
	worldobject.create(Sign, sf::Vector2f(TILE_SIZE * 125, TILE_SIZE * 4));
	worldobject.create(Stone, sf::Vector2f(TILE_SIZE * 32, TILE_SIZE * 4));
	worldobject.create(Stone, sf::Vector2f(TILE_SIZE * 50, TILE_SIZE * 4));
	worldobject.create(Stone, sf::Vector2f(TILE_SIZE * 67, TILE_SIZE * 3));
	worldobject.create(Stone, sf::Vector2f(TILE_SIZE * 85, TILE_SIZE * 4));
	worldobject.create(Tree1, sf::Vector2f(TILE_SIZE * 9, TILE_SIZE * 3));
	worldobject.create(Tree1, sf::Vector2f(TILE_SIZE * 27, TILE_SIZE * 2));
	worldobject.create(Tree1, sf::Vector2f(TILE_SIZE * 54, TILE_SIZE * 2));
	worldobject.create(Tree1, sf::Vector2f(TILE_SIZE * 72, TILE_SIZE * 3));
	worldobject.create(Tree1, sf::Vector2f(TILE_SIZE * 79, TILE_SIZE * 4));
	worldobject.create(Tree1, sf::Vector2f(TILE_SIZE * 112, TILE_SIZE * 1));
	worldobject.create(Tree2, sf::Vector2f(TILE_SIZE * 33, TILE_SIZE * 3));
	worldobject.create(Tree2, sf::Vector2f(TILE_SIZE * 42, TILE_SIZE * 1));
	worldobject.create(Tree2, sf::Vector2f(TILE_SIZE * 56, TILE_SIZE * 3));
	worldobject.create(Tree2, sf::Vector2f(TILE_SIZE * 15, TILE_SIZE * 1));
	worldobject.create(Tree2, sf::Vector2f(TILE_SIZE * 88, TILE_SIZE * 0));
	worldobject.create(Tree2, sf::Vector2f(TILE_SIZE * 96, TILE_SIZE * 2));
}

void Game::Pause()
{
}

void Game::Start()
{
}