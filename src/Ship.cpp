/*
 * Ship.cpp
 *
 *      Author: Diego Charrez
 */

#include "Ship.h"
#include "SDLsetup.h"

Ship::Ship(SDLsetup * setup)
{
	this->setup = setup;
	ship = new Sprite(setup->getRenderer(),"data/ship.png",250,250,100,100);

	timeCheck = SDL_GetTicks();

	moveRight = false;
	moveLeft = false;
	moveUp = false;
	moveDown = false;
}
Ship::~Ship()
{
	delete ship;
}
void Ship::draw()
{
	ship->draw();
}

void Ship::move()
{
	switch (setup->getMainEvent()->type )
	{
				case SDL_KEYDOWN :
					switch (setup->getMainEvent()->key.keysym.sym )
					{
					case SDLK_a:
						moveLeft = true; break;
					case SDLK_w:
						moveUp = true; break;
					case SDLK_s:
						moveDown = true; break;
					case SDLK_d:
						moveRight = true; break;
						break;
					default: break;
					} break;
				case SDL_KEYUP :
					switch (setup->getMainEvent()->key.keysym.sym ) {
					case SDLK_a:
						moveLeft = false; break;
					case SDLK_w:
						moveUp = false; break;
					case SDLK_s:
						moveDown = false; break;
					case SDLK_d:
						moveRight = false; 	break;
					default: break;
					} break;
				default: break;
				}
				if (timeCheck + 8 < SDL_GetTicks())
				{
						if (moveRight && !moveDown && !moveUp)
							ship->setX(ship->getX() +2);
						if (moveLeft && !moveDown && !moveUp)
							ship->setX(ship->getX() -2);
						if (moveUp && !moveLeft && !moveRight)
							ship->setY(ship->getY() -2);
						if (moveDown && !moveLeft && !moveRight)
							ship->setY(ship->getY() +2);
						if (moveRight && (moveDown || moveUp))
							ship->setX(ship->getX() +1);
						if (moveLeft && (moveDown || moveUp))
							ship->setX(ship->getX() -1);
						if (moveUp && (moveLeft || moveRight))
							ship->setY(ship->getY() -1);
						if (moveDown && (moveLeft || moveRight))
							ship->setY(ship->getY() +1);
					timeCheck = SDL_GetTicks();
				}
}
int Ship::getShipX(){
	return ship->getX();
}
int Ship::getShipY(){
	return ship->getY();
}

