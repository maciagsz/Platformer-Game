#ifndef STATE_H
#define STATE_H

import Headers;
//#include "Headers.h"

namespace Engine
{
	class State
	{
	public:
		State() {};
		virtual ~State() {};

		virtual void Init() = 0;
		virtual void ProcessInput() = 0;
		virtual void Update(sf::Time) = 0;
		virtual void Draw() = 0;

		virtual void Pause() {};
		virtual void Start() {};
	};
}

#endif //!STATE_H