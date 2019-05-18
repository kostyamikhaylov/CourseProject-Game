#ifndef BULLET_H
#define BULLET_H

#include <iostream>
#include <list>
#include <cmath>

#include <SFML/Graphics.hpp>

#include "Killable.h"

extern sf::RenderWindow *Window;
extern int i;

class Bullet: public Killable
{
	public:
		int damage_;

		Bullet ();
		Bullet (sf::Vector2f pos, sf::Vector2f v, float m, float friction, float rotation, int hp, int damage, sf::Sprite sprite);

		virtual Object *Act (float dt, std::list<Object *> objects, sf::RenderWindow *win = Window);
		virtual CollisionType GetCollisionType ()
		{
			return BULLET;
		}
		virtual bool IsAlive ()
		{
			return (hp_ > 0);
		}
		virtual ~Bullet () {};
};

#endif //BULLET_H

