#pragma once
#include "GameComponent.h"
#include <SDL.h>

namespace Game1
{
	class Player :
		public GameComponent
	{
	public:
		Player(void);
		~Player(void);

		SDL_Texture * texture; 

		void Update(float timeDelta);
		bool Initialise();
		void Update();
		void Draw();

	};
}

