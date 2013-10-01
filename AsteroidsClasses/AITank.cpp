#include "AITank.h"
#include <iostream>
#include <SDL.h>
#include "Game.h"
#include "Bullet.h"
#include <glm/gtx/constants.hpp>

using namespace Game1;


AITank::~AITank(void)
{
}

AITank::AITank(void):GameComponent()
{
	position = glm::vec2(320, 450);
	look = glm::vec2(-1, 0);
	speed = 200.0f;
	elapsed = 1.0f;
	rotation = (3.0f / 2.0f) * glm::pi<float>();
	fireRate = 10.0f;
}

bool AITank::Initialise()
{
	SDL_Surface * temp = NULL;
	temp = SDL_LoadBMP("tank.bmp");
	if (temp == nullptr)
	{
		cout << "Could not load AITank texture" << endl;
		return false;
	}
	texture = SDL_CreateTextureFromSurface(Game::Instance()->renderer, temp);
	SDL_FreeSurface(temp);

	SDL_QueryTexture(texture, nullptr, nullptr, & rect.w, & rect.h);

	center.x = rect.w / 2;
	center.y = rect.h / 2;
	return true;
}


void AITank::Draw()
{	
	rect.x = position.x;
	rect.y = position.y;

	SDL_RenderCopyEx(Game::Instance()->renderer, texture, nullptr, & rect, glm::degrees(rotation), & center, SDL_FLIP_NONE);
}

void AITank::Update(float timeDelta)
{
	position += look * speed * timeDelta;
	if (position.x < 20)
	{
		position.x = 20;
		rotation = 0;
	}

	if (position.y < 20)
	{
		position.y = 20;
		rotation = glm::half_pi<float>();
	}

	if (position.x > 610)
	{
		position.x = 610;
		rotation = glm::pi<float>();
	}

	if (position.y > 450)
	{
		position.y = 450;
		rotation = (3.0f / 2.0f) * glm::pi<float>();
	}

	look.x = glm::sin(rotation);
	look.y = -glm::cos(rotation);

}
