#ifndef SHOOTABLE_H
#define SHOOTABLE_H

#include <iostream>
#include <list>
#include <cmath>

#include <SFML/Graphics.hpp>

#include "Rotatable.h"
#include "Bullet.h"

#define BULLET_SPEED 200
#define TIME_PER_SHOOT 1.0

extern sf::RenderWindow *Window;
extern int i;

class Shootable: virtual public Rotatable
{
	public:
		Object *target_;
		sf::Clock clock_;

		sf::Texture texture_bullet_;
		sf::Sprite sprite_bullet_;
		std::list<Bullet> bullets_;

		Shootable ();
		Shootable (const Shootable& s);
		const Shootable& operator = (const Shootable& s);
		Shootable (sf::Vector2f pos, float rotation, Object *target, sf::Sprite sprite);

		void ChooseTarget (std::list<Object *> objects, sf::RenderWindow *win = Window);
		Object *Act (float dt, std::list<Object *> objects, sf::RenderWindow *win = Window);
		CollisionType GetCollisionType ()
		{
			return SHOOTABLE;
		}
		~Shootable () {};
};

#endif //SHOOTABLE_H

