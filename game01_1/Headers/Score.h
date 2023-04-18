#pragma once

import Headers;
//#include "Headers.h"
#include "Player.h"
#include "ResourceIdentifiers.h"
#include "StringHelpers.inl"
#include "World.h"

class Score : public sf::Drawable, sf::Transformable
{
	FontHolder font_holder;
	sf::Text sf_text_score;
	sf::Clock gametime_clock;
	sf::Time gametime;
	int elapsed_timescore;

public:
	int integer_score;
	Score();
	void update(Player&, sf::Vector2f);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
