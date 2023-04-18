#ifndef GAMEOVER_H
#define GAMEOVER_H

import Headers;
//#include "Headers.h"
#include "GameInterface.h"
#include "ResourceHolder.h"
#include "ResourceIdentifiers.h"
#include "State.h"

class GameOver : public Engine::State
{
	std::shared_ptr<Context> context;
	sf::Text game_over_title;
	sf::Text retry_button;
	sf::Text exit_button;

	sf::View view;

	FontHolder font_holder;

	bool is_retry_button_selected;
	bool is_retry_button_pressed;

	bool is_exit_button_selected;
	bool is_exit_button_pressed;

public:
	GameOver(std::shared_ptr<Context>& context);
	~GameOver();

	void Init() override;
	void ProcessInput() override;
	void Update(sf::Time deltaTime) override;
	void Draw() override;
};

#endif //!GAMEOVER_H
