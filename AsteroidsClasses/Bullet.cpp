#include "Bullet.h"
#include <iostream>
#include <SDL.h>
#include "Game.h"


using namespace Game1;
using namespace std;

Bullet::Bullet(void):GameComponent()
{
	speed = 100.0f;
}

Bullet::~Bullet(void)
{
}

void Bullet::Update(float timeDelta)
{
	position += look * speed * timeDelta;
	if ((position.x < 0) || (position.x > 640) || (position.y < 0) || (position.y > 480))
	{
		alive = false;
	}

	// Check distance to the AI tank
	glm::vec2 tankPos = Game::Instance()->aiTank->position + glm::vec2(Game::Instance()->aiTank->center.x , Game::Instance()->aiTank->center.y);
	float dist = glm::length(position - tankPos);
	if (dist < 20)
	{
		cout << "Hit the AI Tank!!" << endl;
		alive = false;
	}
}

bool Bullet::Initialise()
{
	SDL_Surface * temp = NULL;
	temp = SDL_LoadBMP("bullet.bmp");
	if (temp == nullptr)
	{
		cout << "Could not load player texture" << endl;
		return false;
	}
	texture = SDL_CreateTextureFromSurface(Game::Instance()->renderer, temp);
	SDL_FreeSurface(temp);
	return true;
}

void Bullet::Draw()
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
