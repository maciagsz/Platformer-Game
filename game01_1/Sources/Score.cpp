#include "../Headers/Score.h"
#include "../Headers/ResourceHolder.h"

Score::Score()
{
    font_holder.loadResource(Fonts::ID::Score, "Resources/fonts/mc_regular.otf");
    sf_text_score.setFont(font_holder.getResource(Fonts::ID::Score));
    sf_text_score.setCharacterSize(30);
    sf_text_score.setFillColor(sf::Color::Black);

    gametime_clock.restart();
    gametime = gametime_clock.restart();
}

void Score::update(Player& player, sf::Vector2f pos)
{
    gametime = gametime_clock.getElapsedTime();
    elapsed_timescore = gametime.asSeconds() * 10;
    integer_score = player.passed_distance + player.mushrooms_collected - elapsed_timescore;
    sf_text_score.setString("Score: " + toString(integer_score));
    sf_text_score.setPosition(pos.x - 100.f, 0);
}

void Score::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(sf_text_score, states);
}