#ifndef KILLABLE_CPP
#define KILLABLE_CPP

#include <iostream>
#include <vector>
#include <cmath>

#include "Killable.h"


Killable::Killable ():
	Object (),
	Movable (),
	Rotatable (),
	hp_ ()
{
	sf::FloatRect size = sprite_.getLocalBounds ();
	size_ = {size.width, size.height};
}

Killable::Killable (sf::Vector2f pos, sf::Vector2f v, float m, float friction, float rotation, int hp, sf::Sprite sprite):
	Object (pos, sprite),
	Movable (pos, v, m, friction, sprite),
	Rotatable (pos, rotation, sprite),
	hp_ (hp)
{
	sf::FloatRect size = sprite_.getLocalBounds ();
	size_ = {size.width, size.height};
}
		
void Killable::Draw (sf::RenderWindow *win) const
{
	Rotatable::Draw (win);
}

Object *Killable::Act (float dt, sf::RenderWindow *win)
{
	pos_ = GetNewPosition (dt);
	v_ = GetNewSpeed (dt);

	if (	(GetNewPosition (REACTION_TIME).x - size_.x / 2 <= 0)					||
			(GetNewPosition (REACTION_TIME).x + size_.x / 2 >= win->getSize ().x)	)
	{
		v_.x *= -1;
	}
	if (	(GetNewPosition (REACTION_TIME).y - size_.y / 2 <= 0)					||
			(GetNewPosition (REACTION_TIME).y + size_.y / 2 >= win->getSize ().y)	)
	{
		v_.y *= -1;
	}
	
	v_.x *= (1 - friction_);
	v_.y *= (1 - friction_);

	return nullptr;
}

#endif //KILLABLE_CPP

