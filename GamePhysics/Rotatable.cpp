#ifndef ROTATABLE_CPP
#define ROTATABLE_CPP

#include <iostream>
#include <vector>
#include <cmath>

#include "Rotatable.h"


Rotatable::Rotatable ():
	Object (sf::Vector2f (), sf::Sprite ()),
	rotation_ ()
{
	sf::FloatRect size = sprite_.getLocalBounds ();
	size_ = {size.width, size.height};
}

Rotatable::Rotatable (sf::Vector2f pos, float rotation, sf::Sprite sprite):
	Object (pos, sprite),
	rotation_ (rotation)
{
	sf::FloatRect size = sprite_.getLocalBounds ();
	size_ = {size.width, size.height};
}

Object *Rotatable::Act (float dt, sf::RenderWindow *win)
{
	return nullptr;
}

void Rotatable::Draw (sf::RenderWindow *win) const
{
	sf::Sprite sprite = sprite_;

	sprite.setOrigin (size_.x / 2, size_.y / 2);
	sprite.setPosition (pos_);
	sprite.setRotation (rotation_);

	win->draw (sprite);
}

#endif //ROTATABLE_CPP

