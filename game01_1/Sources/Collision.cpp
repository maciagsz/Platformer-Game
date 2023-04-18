#include "../Headers/Collision.h"

Collision::Collision(Player& entity, World& world, WorldObject& worldobject)
    : tile_size(TILE_SIZE, TILE_SIZE)
    , _player(entity)
    , _world(world)
    , _worldobject(worldobject)
{
    //rect_vector = new sf::FloatRect[9];
}

Collision::~Collision()
{
    //delete[]rect_vector;
    //rect_vector = nullptr;
}

void Collision::calculateTiles()
{
    int y_pos = (_player.player_sprite.getPosition().y / TILE_SIZE);
    int x_pos = (_player.player_sprite.getPosition().x / TILE_SIZE);

    if (y_pos < 1)
        y_pos = 1;

    if (x_pos < 1)
        x_pos = 1;

    //if (x_pos > 126) {
    //	world.setFinish();
    //	x_pos = 126;
    //}

    //std::cout << x_pos << " " << y_pos << "\n";

    int counter = 0;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
        {
            int vertice_id = ((x_pos - 1 + j) + (y_pos - 1 + i) * WORLD_WIDTH) * 4;
            sf::Vector2f vertice_pos = _world.world_vertices[vertice_id].position;
            sf::FloatRect rect(vertice_pos, tile_size);
            rect_vector[counter] = rect;
            counter++;
        }
}

void Collision::yCollisionCheck(sf::FloatRect& player_bounds, sf::FloatRect& rect)
{
    //Bottom collision
    if (player_bounds.top < rect.top
        && player_bounds.top + player_bounds.height < rect.top + rect.height
        && player_bounds.left < rect.left + rect.width
        && player_bounds.left + player_bounds.width > rect.left
        )
    {
        _player.movement.y = 0.f;
        _player.is_on_the_ground = true;
        _player.player_sprite.setPosition(player_bounds.left, rect.top - player_bounds.height);
    }

    //Top collision
    else if (player_bounds.top > rect.top
        && player_bounds.top + player_bounds.height > rect.top + rect.height
        && player_bounds.left < rect.left + rect.width
        && player_bounds.left + player_bounds.width > rect.left
        )
    {
        _player.movement.y = 0.f;
        _player.player_sprite.setPosition(player_bounds.left, rect.top + rect.height);
    }
}

void Collision::xCollisionCheck(sf::FloatRect& player_bounds, sf::FloatRect& rect)
{
    //Right collision
    if (player_bounds.left < rect.left
        && player_bounds.left + player_bounds.width < rect.left + rect.width
        && player_bounds.top < rect.top + rect.height
        && player_bounds.top + player_bounds.height > rect.top
        )
    {
        _player.movement.x = 0.f;
        _player.player_sprite.setPosition(rect.left - player_bounds.width, player_bounds.top);
    }

    //Left collision
    else if (player_bounds.left > rect.left
        && player_bounds.left + player_bounds.width > rect.left + rect.width
        && player_bounds.top < rect.top + rect.height
        && player_bounds.top + player_bounds.height > rect.top
        )
    {
        _player.movement.x = 0.f;
        _player.player_sprite.setPosition(rect.left + rect.width, player_bounds.top);
    }
}

void Collision::checkTileCollision()
{
    for (int i = 0; i < 9; i++)
    {
        int y_pos = (_player.player_sprite.getPosition().y / TILE_SIZE);
        int x_pos = (_player.player_sprite.getPosition().x / TILE_SIZE);

        if (y_pos < 1)
            y_pos = 1;

        if (x_pos < 1)
            x_pos = 1;

        int counter = 0;
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
            {
                int vertice_id = ((x_pos - 1 + j) + (y_pos - 1 + i) * (WORLD_WIDTH)) * 4;
                sf::Vector2f vertice_pos = _world.world_vertices[vertice_id].position;
                sf::FloatRect rect(vertice_pos, tile_size);
                rect_vector[counter] = rect;
                counter++;
            }

        for (int i = 0; i < 9; i++)
        {
            auto rect = rect_vector[i];
            sf::FloatRect player_bounds = _player.player_sprite.getGlobalBounds();

            next_pos = player_bounds;
            next_pos.left += _player.movement.x * Game::time_per_frame.asSeconds();
            next_pos.top += _player.movement.y * Game::time_per_frame.asSeconds();

            if (rect.intersects(next_pos))
            {
                //std::jthread t1(&Collision::yCollisionCheck, *this, std::ref(player_bounds), std::ref(rect));
                //std::jthread t2(&Collision::xCollisionCheck, *this, std::ref(player_bounds), std::ref(rect));
                yCollisionCheck(player_bounds, rect);
                xCollisionCheck(player_bounds, rect);
            }
        }
    }
}

void Collision::checkObjectCollision()
{
    int id = 0;
    for (auto& object : _worldobject.worldobject_sprites)
    {
        if ((object.getTexture()->getSize().x == 129) && (object.getGlobalBounds().intersects(next_pos)))
        {
            _worldobject.worldobject_sprites.erase(_worldobject.worldobject_sprites.begin() + id);
            _player.mushrooms_collected += 10000;
        }

        id++;
    }
}

void Collision::checkScreenCollision()
{
    if (_player.player_sprite.getPosition().x < 0)
        _player.player_sprite.setPosition(0, _player.player_sprite.getPosition().y);

    if (_player.player_sprite.getPosition().x + _player.player_sprite.getGlobalBounds().width > 16384) {
        _player.player_sprite.setPosition(16384 - _player.player_sprite.getGlobalBounds().width, _player.player_sprite.getPosition().y);
        _world.is_finished = true;
    }

    if (_player.player_sprite.getPosition().y > 1024 - 128 - TILE_SIZE) //Bottom collision detection
        _player.setDead();
}

void Collision::checkCollision()
{
    calculateTiles();
    checkTileCollision();
    checkObjectCollision();
    checkScreenCollision();
}