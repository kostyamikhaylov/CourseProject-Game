#ifndef KILLABLE_H
#define KILLABLE_H

#include <iostream>
#include <list>
#include <cmath>

#include <SFML/Graphics.hpp>

#include "Movable.h"
#include "Rotatable.h"

extern sf::RenderWindow *Window;
extern int i;

class Killable: public Movable, public Rotatable
{
	public:
		int hp_;

		Killable ();
		Killable (sf::Vector2f pos, sf::Vector2f v, float m, float friction, float rotation, int hp, sf::Sprite sprite);

		virtual void Draw (sf::RenderWindow *win = Window) const;
		virtual Object *Act (float dt, sf::RenderWindow *win = Window);
		virtual CollisionType GetCollisionType ()
		{
			return KILLABLE;
		}
		virtual bool IsAlive ()
		{
			return (hp_ > 0);
		}
		virtual ~Killable () {};
};

#endif //KILLABLE_H

