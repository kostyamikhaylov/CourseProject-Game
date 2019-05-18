#ifndef BULLET_CPP
#define BULLET_CPP

#include <iostream>
#include <vector>
#include <cmath>

#include "Bullet.h"


Bullet::Bullet ():
	Object (),
	Killable (),
	damage_ ()
{
	sf::FloatRect size = sprite_.getLocalBounds ();
	size_ = {size.width, size.height};
}

Bullet::Bullet (sf::Vector2f pos, sf::Vector2f v, float m, float friction, float rotation, int hp, int damage, sf::Sprite sprite):
	Object (pos, sprite),
	Killable (pos, v, m, friction, rotation, hp, sprite),
	damage_ (damage)
{
	sf::FloatRect size = sprite_.getLocalBounds ();
	size_ = {size.width, size.height};
}
		
Object *Bullet::Act (float dt, std::list<Object *> objects, sf::RenderWindow *win)
{
	pos_ = GetNewPosition (dt);
	v_ = GetNewSpeed (dt);

	if (	(GetNewPosition (REACTION_TIME).x - size_.x / 2 <= 0)					||
			(GetNewPosition (REACTION_TIME).x + size_.x / 2 >= win->getSize ().x)	)
	{
		hp_ = 0;
	}
	if (	(GetNewPosition (REACTION_TIME).y - size_.y / 2 <= 0)					||
			(GetNewPosition (REACTION_TIME).y + size_.y / 2 >= win->getSize ().y)	)
	{
		hp_ = 0;
	}
	
	v_.x *= (1 - friction_);
	v_.y *= (1 - friction_);

	return nullptr;
}

#endif //BULLET_CPP

