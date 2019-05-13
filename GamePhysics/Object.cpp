#ifndef OBJECT_CPP
#define OBJECT_CPP

#include <iostream>
#include <vector>
#include <cmath>

#include "Object.h"


Object::Object ():
	pos_ (sf::Vector2f ()),
	size_ (sf::Vector2f ()),
	sprite_ (sf::Sprite ())
{
	sf::FloatRect size = sprite_.getLocalBounds ();
	size_ = {size.width, size.height};
}

Object::Object (sf::Vector2f pos, sf::Sprite sprite):
	pos_ (pos),
	size_ (sf::Vector2f ()),
	sprite_ (sprite)
{
	sf::FloatRect size = sprite_.getLocalBounds ();
	size_ = {size.width, size.height};
}

#endif //OBJECT_CPP

