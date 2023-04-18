#ifndef MAINMENU_H
#define MAINMENU_H

import Headers;
#include "State.h"
#include "Game.h"
#include "GameInterface.h"

class MainMenu : public Engine::State
{
    std::shared_ptr<Context> context;
    FontHolder font_holder;
    TextureHolder menu_textures;
    sf::Sprite background_sprite;
    sf::Text game_title;
    sf::Text play_button;
    sf::Text exit_button;
    sf::Text hall_of_fame_button;

    bool is_play_button_selected;
    bool is_play_button_pressed;

    bool is_exit_button_selected;
    bool is_exit_button_pressed;

    bool is_hall_of_fabe_button_selected;
    bool is_hall_of_fabe_button_pressed;

    int selected_option;

    sf::View view;

public:
    MainMenu(std::shared_ptr<Context>& context);
    ~MainMenu();

    void Init() override;
    void ProcessInput() override;
    void Update(sf::Time deltaTime) override;
    void Draw() override;
};

#endif //!MAINMENU_H