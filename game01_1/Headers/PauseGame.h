#pragma once

import Headers;
#include "GameInterface.h"
#include "ResourceHolder.h"
#include "ResourceIdentifiers.h"
#include "State.h"

class PauseGame : public Engine::State
{
    std::shared_ptr<Context> context;
    sf::Text pause_game_title;
    FontHolder font_holder;
    sf::View view;

public:
    PauseGame(std::shared_ptr<Context>& context);
    ~PauseGame();

    void Init() override;
    void ProcessInput() override;
    void Update(sf::Time deltaTime) override;
    void Draw() override;
};
