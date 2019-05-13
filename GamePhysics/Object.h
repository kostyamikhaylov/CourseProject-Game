#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>
#include <list>
#include <cmath>

#include <SFML/Graphics.hpp>

#define REACTION_TIME 0.01
#define GRAVITATION 0
#define sqr(x) (x) * (x)

extern sf::RenderWindow *Window;
extern int i;

enum CollisionType
{
	OBJECT,
	ROTATABLE,
	MOVABLE,
	KILLABLE,
	BULLET,
	SHOOTABLE,
};

class Object
{
	public:
		sf::Vector2f pos_;
		sf::Vector2f size_;

		sf::Sprite sprite_;

		Object ();
		Object (sf::Vector2f pos, sf::Sprite sprite);

		virtual void Draw (sf::RenderWindow *win = Window) const = 0;
		virtual Object *Act (float dt, sf::RenderWindow *win = Window) = 0;
		virtual CollisionType GetCollisionType ()
		{
			return OBJECT;
		}
		virtual bool IsAlive ()
		{
			return true;
		}
		virtual ~Object () {};
};

#endif //OBJECT_H

