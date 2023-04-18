#ifndef GAME_H
#define GAME_H

import Headers;
#include "Player.h"
#include "World.h"
#include "WorldObject.h"
#include "Collision.h"
#include "Score.h"
#include "StateMan.h"
#include "State.h"
#include "GameInterface.h"
#include "InputName.h"

constexpr auto TILE_SIZE = 128;

class Game : public World, public Player, public Engine::State
{
    std::shared_ptr<Context> context;
    sf::View view;
    sf::Text score_text;
    World world;
    Player player;
    WorldObject worldobject;
    Score score;
    sf::Vector2f tile_size;
    friend InputName;

public:
    static const sf::Time time_per_frame;
    Game(std::shared_ptr<Context>& context);
    ~Game();

    void worldobjectInitialize();
    void playerCollisionCheck();
    void viewFollow();
    void close();

    void Init() override;
    void ProcessInput() override;
    void Update(sf::Time) override;
    void Draw() override;
    void Pause() override;
    void Start() override;
};

#endif // !GAME_H
