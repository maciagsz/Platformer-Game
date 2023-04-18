#include "../Headers/Player.h"
#include "../Headers/Game.h"

Player::Player()
{
    player_textures.loadResource(Textures::ID::PlayerDefault, "Resources/textures/player.png");
    player_sprite.setTexture(player_textures.getResource(Textures::ID::PlayerDefault));
    player_sprite.setPosition(128, 300);
    player_sprite.setScale(0.5, 0.5);
    player_speed = 800;
    is_moving_up = false;
    is_moving_down = false;
    is_moving_left = false;
    is_moving_right = false;
    is_falling = false;
    is_jumping = false;
    is_dead = false;
    is_on_the_ground = false;
    jump_time = jump_clock.restart();
    passed_distance = 0;
    mushrooms_collected = 0;
    is_paused = false;
}

void Player::setDead()
{
    is_dead = true;
}

void Player::resetMovement()
{
    is_moving_up = false;
    is_moving_down = false;
    is_moving_left = false;
    is_moving_right = false;
}

void Player::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
    if (is_on_the_ground)
        if (key == sf::Keyboard::Space)
            is_jumping = isPressed;
    //else if (key == sf::Keyboard::S)
    //	is_moving_down = isPressed;
    if (key == sf::Keyboard::A)
        is_moving_left = isPressed;
    else if (key == sf::Keyboard::D)
        is_moving_right = isPressed;
    else if (key == sf::Keyboard::Escape)
        is_paused = isPressed;
}

void Player::jumping()
{
    jump_time = jump_clock.getElapsedTime();
    if (jump_time.asMilliseconds() > 220)
    {
        if (is_jumping)
        {
            is_moving_down = false;
            is_moving_up = true;
            jump_time = jump_clock.restart();
            is_on_the_ground = false;
        }
        else
        {
            is_moving_down = true;
            is_moving_up = false;
        }
    }
    else
    {
        is_jumping = false;
    }
}

void Player::updateDistance()
{
    if (player_sprite.getGlobalBounds().left > passed_distance)
        passed_distance = player_sprite.getGlobalBounds().left;
}

void Player::move()
{
    movement.x = 0.f;
    movement.y = 0.f;

    if (is_moving_up)
        movement.y -= 1.35 * player_speed;
    if (is_moving_down)
        movement.y += 1.1 * player_speed;
    if (is_moving_left)
        movement.x -= player_speed;
    if (is_moving_right)
        movement.x += player_speed;
}

void Player::updatePos(sf::Time dt)
{
    movement_offset = movement * dt.asSeconds();
    player_sprite.move(movement_offset);
}

void Player::update()
{
    jumping();
    updateDistance();
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    //states.texture = &player_textures.getResource(Textures::ID::PlayerDefault);
    target.draw(player_sprite, states);
}