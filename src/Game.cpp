/*
 * Game.cpp
 *
 *      Author: Diego Charrez
 */

#include "Game.h"
#include "stdafx.h"
#include "SDLsetup.h"

Game::Game(int screenWidth,int screenHeigh) {
	bulletSpeed=timeCheck = SDL_GetTicks();
	this->screenWidth = screenWidth;
	this->screenHeight = screenHeigh;
	quit = false;
	setup = new SDLsetup(& quit, this->screenWidth , this->screenHeight);
	ship = new Ship(setup);

	background = new Sprite(setup->getRenderer(),"data/background.jpg",0,0,screenWidth,screenWidth);

	Lives = "Lives: 3";
	Score = "Score: ";


	attack = false;

}
Game::~Game() {

  armageddon.clear();
  shots.clear();

	delete setup;
	delete background;
	delete ship;
}
void Game::createArmageddon(){

	if ( unsigned (timeCheck + 500) < SDL_GetTicks() ) {
		armageddon.push_back(new  Rock(setup,this->screenWidth , this->screenHeight));
		timeCheck = SDL_GetTicks();
	}
	for(vector<Rock *>::iterator it = armageddon.begin(); it!= armageddon.end(); ++it ){
			(*it)->draw();

			rockMotion = 0;//rand() % 1;
						switch (rockMotion) {
							case 0: (*it)->randomMotionLeftO(); break;
							case 1: (*it)->randomMotionRightO(); break;
							case 2: (*it)->randomMotionDown(); break;
						}

		}
}
void Game::bullets() {
	//if ( unsigned (bulletSpeed + 200) < SDL_GetTicks() ) {
		if (setup->getMainEvent()->type == SDL_KEYDOWN) {
			if(setup->getMainEvent()->key.keysym.sym == SDLK_q)
				attack = true;
		}
		if (setup->getMainEvent()->type == SDL_KEYUP) {
			if(setup->getMainEvent()->key.keysym.sym == SDLK_q)
				attack = false;
		}
		if (attack) {
						if (unsigned (bulletSpeed + 250) < SDL_GetTicks()){
							shots.push_back(new Bullet ( setup , ship->getShipX()+45,ship->getShipY()));

							Score = "Score: ";
							score++;
							stringstream ss;
							ss << score;
							Score = Score  + ss.str();
							bulletSpeed = SDL_GetTicks();
						}
		//bulletSpeed = SDL_GetTicks();
	//}
	}

	for(vector<Bullet *>::iterator it = shots.begin(); it!= shots.end(); ++it ){
		(*it)->Draw();
		(*it)->Shoot();
	}
}

bool Game::checkCollisions(SDL_Rect a, SDL_Rect b) {

      int leftA, leftB;
      int rightA, rightB;
      int topA, topB;
      int bottomA, bottomB;

      leftA = a.x;
      rightA = a.x + a.w;
      topA = a.y;
      bottomA = a.y + a.h;

      leftB = b.x;
      rightB = b.x + b.w;
      topB = b.y;
      bottomB = b.y + b.h;

      if( bottomA <= topB || topA >= bottomB || rightA <= leftB || leftA >= rightB)
          return false;
      return true;
}


void Game::collisionShipRock(Ship * Ship, vector<Rock *> Rocks) {


  for(vector<Rock *>::size_type i = 0; i != Rocks.size(); i++) {
      /* std::cout << someVector[i]; ... */

 //for (vector<Rock *>::iterator it = Rocks.begin(); it != Rocks.end() ; ++it) {

    if ( checkCollisions(  Ship->ship->getRect(),(Rocks[i]->rock->getRect() ) ) ){

       /*SDL_DestroyTexture(Rocks[i]->rock->getTexture());
       Rocks[i] = Rocks.back();
       Rocks.pop_back();*/

       //Rocks.erase(Rocks.begin() + i);


         lives--;
         Lives = "Lives: ";
         stringstream ss;
         ss << lives;
         Lives = Lives  + ss.str();

         break;

     }
  }



  /*int TEMP = 0;
  for (vector<Rock *>::iterator it = Rocks.begin(); it != Rocks.end() ; ++it) {
    if ( checkCollisions( Ship->ship->getRect(),(*it)->rock->getRect()) ) {


      Rocks.erase(Rocks.begin()+TEMP);

      lives--;
      Lives = "Lives: ";
      stringstream ss;
      ss << lives;
      Lives = Lives  + ss.str();

      cout << TEMP << endl;
    }
    TEMP++;
  }*/

}
void Game::collisionBulletRock(vector<Bullet *> Bullets, vector<Rock *> Rocks) {

  /*for (vector<Bullet *>::iterator i = Bullets.begin(); i != Bullets.end() ; ++i) {
      for (vector<Rock *>::iterator j = Rocks.begin(); j != Rocks.end() ; ++j) {
        if ( checkCollisions( (*i)->bullet->getRect(),(*j)->rock->getRect()) ) {
      }
    }
  }*/

  for (vector<Bullet *>::size_type j = 0; j != Bullets.size() ; j++) {
    for (vector<Rock *>::size_type i = 0; i != Rocks.size(); i++) {
      //if ( checkCollisions( Bullets[j]->bullet->getRect(), Rocks[i]->rock->getRect()) ) {
      if ( checkCollisions( Rocks[i]->rock->getRect(), Bullets[j]->bullet->getRect()) ) {
        //cout << "Rock Destroyed" << endl;

        SDL_DestroyTexture(Bullets[j]->bullet->getTexture());
        SDL_DestroyTexture(Rocks[i]->rock->getTexture());

        /*Rocks[i] = Rocks.back();
        Rocks.pop_back();


        Bullets[j] = Bullets.back();
        Bullets.pop_back();*/


        //Rocks.erase(Rocks.begin() + i);
        //Bullets.erase(Bullets.begin()+j);

        //score++;

      }
    }
  }

}


void Game::gameLoop(){
	while(!quit && setup->getMainEvent()->type != SDL_QUIT){
			setup->begin();

			background->draw();

			createArmageddon();



			ship->draw();

			ship->move();

			setup->writeText(Lives,25,10);
			setup->drawText();
			setup->writeText(Score,screenWidth - 150,10);
			setup->drawText();

			bullets();

			collisionShipRock(ship, armageddon);
			collisionBulletRock(shots, armageddon);



			setup->end();
		}
}

