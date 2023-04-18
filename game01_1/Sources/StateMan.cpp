#include "../Headers/StateMan.h"

Engine::StateMan::StateMan() : is_to_be_added(false), is_to_be_replaced(false), is_to_be_removed(false)
{
}

Engine::StateMan::~StateMan()
{
}

void Engine::StateMan::Add(std::unique_ptr<State> toAdd, bool replace)
{
    is_to_be_added = true;
    new_state_uptr = std::move(toAdd);

    is_to_be_replaced = replace;
}

void Engine::StateMan::PopCurrent()
{
    is_to_be_removed = true;
}

void Engine::StateMan::ProcessStateChange()
{
    if (is_to_be_removed && (!state_stack.empty()))
    {
        state_stack.pop();

        if (!state_stack.empty())
        {
            state_stack.top()->Start();
        }

        is_to_be_removed = false;
    }

    if (is_to_be_added)
    {
        if (is_to_be_replaced && (!state_stack.empty()))
        {
            state_stack.pop();
            is_to_be_replaced = false;
        }

        if (!state_stack.empty())
        {
            state_stack.top()->Pause();
        }

        state_stack.push(std::move(new_state_uptr));
        state_stack.top()->Init();
        state_stack.top()->Start();
        is_to_be_added = false;
    }
}

std::unique_ptr<Engine::State>& Engine::StateMan::GetCurrent()
{
    return state_stack.top();
}