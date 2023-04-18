#ifndef STATEMAN_H
#define STATEMAN_H

import Headers;
#include "State.h"

namespace Engine
{
    class StateMan
    {
        std::stack<std::unique_ptr<State>> state_stack;
        std::unique_ptr<State> new_state_uptr;

        bool is_to_be_added;
        bool is_to_be_replaced;
        bool is_to_be_removed;

    public:
        StateMan();
        ~StateMan();

        void Add(std::unique_ptr<State>, bool replace = false);
        void PopCurrent();
        void ProcessStateChange();
        std::unique_ptr<State>& GetCurrent();
    };
}

#endif //!STATEMAN_H