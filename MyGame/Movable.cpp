#ifndef MOVABLE_CPP
#define MOVABLE_CPP

#include <iostream>
#include <vector>
#include <cmath>

#include "Movable.h"


Movable::Movable ():
	Object (sf::Vector2f (), sf::Sprite ()),
	v_ (sf::Vector2f ()),
	m_ (),
	friction_ ()
{
	sf::FloatRect size = sprite_.getLocalBounds ();
	size_ = {size.width, size.height};
}

Movable::Movable (sf::Vector2f pos, sf::Vector2f v, float m, float friction, sf::Sprite sprite):
	Object (pos, sprite),
	v_ (v),
	m_ (m),
	friction_ (friction)
{
	sf::FloatRect size = sprite_.getLocalBounds ();
	size_ = {size.width, size.height};
}

void Movable::Draw (sf::RenderWindow *win) const
{
	sf::Sprite sprite = sprite_;

	sprite.setOrigin (size_.x / 2, size_.y / 2);
	sprite.setPosition (pos_);

	win->draw (sprite);
}

sf::Vector2f Movable::GetNewPosition (float dt) const
{
	return sf::Vector2f (pos_.x + v_.x * dt, pos_.y + v_.y * dt + GRAVITATION * dt * dt / 2);
}

sf::Vector2f Movable::GetNewSpeed (float dt) const
{
	return sf::Vector2f (v_.x, v_.y + GRAVITATION * dt);
}

Object *Movable::Act (float dt, std::list<Object *> objects, sf::RenderWindow *win)
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

#endif //MOVABLE_CPP

