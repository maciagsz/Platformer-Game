#include "../Headers/HallOfFame.h"
#include "../Headers/MainMenu.h"

HallOfFame::HallOfFame(std::shared_ptr<Context>& context)
    : context(context), is_exit_button_selected(false),
    is_exit_button_pressed(false)
{
    view.setSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    view.setCenter(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
    scores_file_exists = true;
}

HallOfFame::~HallOfFame()
{
}

void HallOfFame::Init()
{
    font_holder.loadResource(Fonts::ID::MenuFont, "Resources/fonts/mc_regular.otf");
    font_holder.loadResource(Fonts::ID::TitleFont, "Resources/fonts/ugly_byte.otf");
    // Title
    hall_of_fame_title.setFont(font_holder.getResource(Fonts::ID::TitleFont));
    hall_of_fame_title.setString("Hall of fame");
    hall_of_fame_title.setFillColor(sf::Color::Black);
    hall_of_fame_title.setCharacterSize(300);
    hall_of_fame_title.setOrigin(hall_of_fame_title.getLocalBounds().width / 2,
        hall_of_fame_title.getLocalBounds().height / 2);
    hall_of_fame_title.setPosition(context->m_window->getSize().x / 2,
        context->m_window->getSize().y / 2 - 500.f);

    // Back Button
    back_button.setFont(font_holder.getResource(Fonts::ID::MenuFont));
    back_button.setString("Back");
    back_button.setCharacterSize(120);
    back_button.setFillColor(sf::Color::Black);
    back_button.setOrigin(back_button.getLocalBounds().width / 2,
        back_button.getLocalBounds().height / 2);
    back_button.setPosition(context->m_window->getSize().x / 2 + 400,
        context->m_window->getSize().y / 2);

    //No scores
    no_scores.setFont(font_holder.getResource(Fonts::ID::MenuFont));
    no_scores.setString("No scores");
    no_scores.setFillColor(sf::Color::Black);
    no_scores.setCharacterSize(100);
    no_scores.setOrigin(hall_of_fame_title.getLocalBounds().width / 2,
        hall_of_fame_title.getLocalBounds().height / 2);
    no_scores.setPosition(context->m_window->getSize().x / 2,
        context->m_window->getSize().y / 2);

    if (!std::filesystem::exists("scores.txt"))
    {
        scores_file_exists = false;
        //throw std::exception("Score file does not exist!");
    }

    if (std::filesystem::exists("scores.txt"))
    {
        std::fstream score_file;
        score_file.open("scores.txt");

        if (!score_file.is_open())
            throw std::exception("Could not open score file.");

        std::string name;
        int score;

        std::string tempstring;
        while (getline(score_file, tempstring))
        {
            std::stringstream stringstream(tempstring);
            stringstream >> score >> name;

            if (tempstring == "")
                continue;

            scores.push_back(std::pair<int, std::string>(score, name));
        }

        std::ranges::sort(scores, [&](std::pair<int, std::string> a, std::pair<int, std::string> b)
            {
                return a.first > b.first;
            });

        for (auto& score : scores)
        {
            sf::Text text;
            text.setString(std::to_string(score.first) + " " + score.second);
            displayscores.push_back(text);
        }

        int counter = 0;
        for (auto& score : displayscores)
        {
            score.setFont(font_holder.getResource(Fonts::ID::MenuFont));
            score.setCharacterSize(50);
            score.setFillColor(sf::Color::Black);
            score.setPosition(context->m_window->getSize().x / 2 - 500,
                context->m_window->getSize().y / 2 - 200 + counter * 85);
            counter++;
        }
    }
}

void HallOfFame::ProcessInput()
{
    sf::Event event;
    while (context->m_window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            context->m_window->close();
        }
        else if (event.type == sf::Event::KeyPressed)
        {
            if (sf::Keyboard::Enter)
                is_exit_button_pressed = true;
        }
    }
}

void HallOfFame::Update(sf::Time deltaTime)
{
    if (is_exit_button_pressed)
    {
        context->m_states->Add(std::make_unique<MainMenu>(context), true);
    }
}

void HallOfFame::Draw()
{
    context->m_window->clear(sf::Color(220, 247, 255));
    context->m_window->draw(hall_of_fame_title);
    context->m_window->draw(back_button);
    if (!scores_file_exists)
        context->m_window->draw(no_scores);

    if (scores_file_exists)
        for (auto& score : displayscores)
            context->m_window->draw(score);
    context->m_window->setView(view);
    context->m_window->display();
}