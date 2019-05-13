#ifndef MOVABLE_H
#define MOVABLE_H

#include <iostream>
#include <list>
#include <cmath>

#include <SFML/Graphics.hpp>

#include "Object.h"

extern sf::RenderWindow *Window;
extern int i;

class Movable: virtual public Object
{
	public:
		sf::Vector2f v_;

		float m_;
		float friction_;

		Movable ();
		Movable (sf::Vector2f pos, sf::Vector2f v, float m, float friction, sf::Sprite sprite);

		virtual void Draw (sf::RenderWindow *win = Window) const;
		sf::Vector2f GetNewPosition (float dt) const;
		sf::Vector2f GetNewSpeed (float dt) const;
		virtual Object *Act (float dt, sf::RenderWindow *win = Window);
		virtual CollisionType GetCollisionType ()
		{
			return MOVABLE;
		}
		virtual bool IsAlive ()
		{
			return true;
		}
		virtual ~Movable () {};
};

#endif //MOVABLE_H

