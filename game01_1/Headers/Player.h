#ifndef PLAYER_H
#define PLAYER_H

import Headers;
#include "ResourceHolder.h"
#include "ResourceIdentifiers.h"

class Player : public sf::Drawable, public sf::Transformable
{
public:
    Player();

    sf::Sprite player_sprite;
    TextureHolder player_textures;

    float player_speed;

    bool is_moving_up;
    bool is_moving_down;
    bool is_moving_left;
    bool is_moving_right;

    bool is_jumping;
    bool is_falling;
    bool is_dead;
    bool is_on_the_ground;

    bool is_paused;

    sf::Clock jump_clock;
    sf::Time jump_time;

    sf::Vector2f movement;
    sf::Vector2f movement_offset;

    int passed_distance;
    int mushrooms_collected;

    void setDead();
    void resetMovement();
    void handlePlayerInput(sf::Keyboard::Key, bool);
    void jumping();
    void updateDistance();
    void move();
    void updatePos(sf::Time);
    void update();
    void draw(sf::RenderTarget&, sf::RenderStates) const override;
};

#endif // !PLAYER_H
