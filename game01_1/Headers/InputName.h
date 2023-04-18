#ifndef INPUTNAME_H
#define INPUTNAME_H

import Headers;
#include "GameInterface.h"
#include "ResourceIdentifiers.h"
#include "ResourceHolder.h"
#include "State.h"
#include "VariableHelper.h"

class InputName : public Engine::State
{
    std::shared_ptr<Context> context;
    sf::Text m_enterName;
    FontHolder font_holder;
    sf::View view;
    sf::String player_input;
    sf::Text player_text;

public:
    InputName(std::shared_ptr<Context>& context);
    ~InputName();

    void Init() override;
    void ProcessInput() override;
    void Update(sf::Time deltaTime) override;
    void Draw() override;
};

#endif//!INPUTNAME_H