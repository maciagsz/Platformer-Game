#ifndef HALLOFFAME_H
#define HALLOFFAME_H

import Headers;
#include "GameInterface.h"
#include "ResourceHolder.h"
#include "ResourceIdentifiers.h"
#include "State.h"

class HallOfFame : public Engine::State
{
private:
    std::shared_ptr<Context> context;
    sf::Text hall_of_fame_title;
    sf::Text back_button;
    sf::Text no_scores;
    sf::View view;
    FontHolder font_holder;
    std::vector<std::pair<int, std::string>> scores;
    std::vector<sf::Text> displayscores;

    bool is_exit_button_selected;
    bool is_exit_button_pressed;

    bool scores_file_exists;

public:
    HallOfFame(std::shared_ptr<Context>& context);
    ~HallOfFame();

    void Init() override;
    void ProcessInput() override;
    void Update(sf::Time deltaTime) override;
    void Draw() override;
};

#endif//!HALLOFFAME_H