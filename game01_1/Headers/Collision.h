#ifndef COLLISION_H
#define COLLISION_H

import Headers;

#include "player.h"
#include "World.h"
#include "Game.h"

class World;
class Player;

class Collision
{
    sf::Vector2f tile_size;
    sf::FloatRect rect_vector[9];
    sf::FloatRect next_pos;
    Player& _player;
    World& _world;
    WorldObject& _worldobject;

public:

    Collision(Player&, World&, WorldObject&);
    ~Collision();

    void calculateTiles();
    void xCollisionCheck(sf::FloatRect&, sf::FloatRect&);
    void yCollisionCheck(sf::FloatRect&, sf::FloatRect&);
    void checkScreenCollision();
    void checkTileCollision();
    void checkObjectCollision();
    void checkCollision();
};

#endif //!COLLISION_H
