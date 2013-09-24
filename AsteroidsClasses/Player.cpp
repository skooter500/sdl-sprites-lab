#include "Player.h"
#include <iostream>
#include <SDL.h>
#include "Game.h"

using namespace Game1;
using namespace std;

Player::Player(void):GameComponent()
{
	position = glm::vec2(100, 100);
	look = glm::vec2(0, -1);
	speed = 50.0f;
}

bool Player::Initialise()
{
	SDL_Surface * temp = NULL;
	temp = SDL_LoadBMP("tank.bmp");
	if (temp == nullptr)
	{
		cout << "Could not load player texture" << endl;
		return false;
	}
	texture = SDL_CreateTextureFromSurface(Game::Instance()->renderer, temp);
	SDL_FreeSurface(temp);
	return true;
}


Player::~Player(void)
{
	
}

void Player::Update(float timeDelta)
{
	const Uint8 * keyState = SDL_GetKeyboardState(NULL);

	if (keyState[SDL_SCANCODE_UP])
	{
		position += look * speed * timeDelta; 
	}

	if (keyState[SDL_SCANCODE_DOWN])
	{
		position -= look * speed * timeDelta; 
	}

}

void Player::Draw()
{
	SDL_Rect rect;
	rect.x = position.x;
	rect.y = position.y;
	SDL_QueryTexture(texture, nullptr, nullptr, & rect.w, & rect.h);
	SDL_Point center;
	center.x = rect.w / 2;
	center.y = rect.h / 2;
	SDL_RenderCopyEx(Game::Instance()->renderer, texture, nullptr, & rect, rotation, & center, SDL_FLIP_NONE);

}
