#ifndef ROTATABLE_H
#define ROTATABLE_H

#include <iostream>
#include <list>
#include <cmath>

#include <SFML/Graphics.hpp>

#include "Object.h"

extern sf::RenderWindow *Window;
extern int i;

class Rotatable: virtual public Object
{
	public:
		float rotation_;

		Rotatable ();
		Rotatable (sf::Vector2f pos, float rotation, sf::Sprite sprite);

		virtual void Draw (sf::RenderWindow *win = Window) const;
		virtual Object *Act (float dt, std::list<Object *> objects, sf::RenderWindow *win = Window);
		virtual CollisionType GetCollisionType ()
		{
			return ROTATABLE;
		}
		virtual bool IsAlive ()
		{
			return true;
		}
		virtual ~Rotatable () {};
};

#endif //ROTATABLE_H

