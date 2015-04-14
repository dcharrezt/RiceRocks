/*
 * Bullet.cpp
 *
 *  Created on: Nov 2, 2014
 *      Author: ddc
 */

#include "Bullet.h"

Bullet::Bullet(SDLsetup * setup, int x , int y) {
	bulletSpeed = SDL_GetTicks();
	this->setup = setup;
	bullet = new Sprite(this->setup->getRenderer(),"data/shot.png",x,y,10,10);
}

Bullet::~Bullet() {
	// TODO Auto-generated destructor stub
}

void Bullet::Draw()
{
	bullet->draw();
}
void Bullet::Shoot()
{
	if ( unsigned (bulletSpeed + 20) < SDL_GetTicks()){
		bullet->setX(bullet->getX()+0);
		bullet->setY(bullet->getY()-5);
		bulletSpeed = SDL_GetTicks();
		}
}




