#ifndef GAMEFINISHED_H
#define GAMEFINISHED_H

import Headers;
#include "GameInterface.h"
#include "ResourceHolder.h"
#include "ResourceIdentifiers.h"
#include "State.h"

class GameFinished : public Engine::State
{
    std::shared_ptr<Context> context;
    sf::Text game_over_title;
    sf::Text retry_button;
    sf::Text exit_button;
    sf::Text player_score;

    sf::View view;

    FontHolder font_holder;

    bool is_retry_button_selected;
    bool is_retry_button_pressed;

    bool is_exit_button_selected;
    bool is_exit_button_pressed;

public:
    GameFinished(std::shared_ptr<Context>& context);
    ~GameFinished();

    void Init() override;
    void ProcessInput() override;
    void Update(sf::Time deltaTime) override;
    void Draw() override;
};

#endif //!GAMEFINISHED_H
