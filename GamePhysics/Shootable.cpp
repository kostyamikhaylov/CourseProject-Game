#ifndef SHOOTABLE_CPP
#define SHOOTABLE_CPP

#include "Shootable.h"


Shootable::Shootable ():
	Object (),
	Rotatable (),
	target_ (nullptr),
	clock_ (sf::Clock ()),
	texture_bullet_ (sf::Texture ()),
	sprite_bullet_ (sf::Sprite ()),
	bullets_ (std::list<Bullet> ())
{
	sf::FloatRect size = sprite_.getLocalBounds ();
	size_ = {size.width, size.height};
}
		
Shootable::Shootable (const Shootable& s):
	Object (s.pos_, s.sprite_),
	Rotatable (s.pos_, s.rotation_, s.sprite_),
	target_ (s.target_),
	clock_ (s.clock_),
	texture_bullet_ (s.texture_bullet_),
	sprite_bullet_ (s.sprite_bullet_),
	bullets_ (s.bullets_)
{
	sf::FloatRect size = sprite_.getLocalBounds ();
	size_ = {size.width, size.height};
}

const Shootable& Shootable::operator = (const Shootable& s)
{
	this->pos_ 		= 	s.pos_;
	this->size_		=	s.size_;
	this->rotation_	=	s.rotation_;
	this->sprite_ 	= 	s.sprite_;
	this->target_ 	= 	s.target_;
	this->clock_	=	s.clock_;
	this->texture_bullet_	=	s.texture_bullet_;
	this->sprite_bullet_	=	s.sprite_bullet_;
	this->bullets_	=	s.bullets_;

	return *this;
}

Shootable::Shootable (sf::Vector2f pos, float rotation, Object *target, sf::Sprite sprite):
	Object (pos, sprite),
	Rotatable (pos, rotation, sprite),
	target_ (target),
	clock_ (sf::Clock ()),
	texture_bullet_ (sf::Texture ()),
	sprite_bullet_ (sf::Sprite ()),
	bullets_ (std::list<Bullet> ())
{
	sf::FloatRect size = sprite_.getLocalBounds ();
	size_ = {size.width, size.height};
	
	texture_bullet_.loadFromFile ("Bullet.png");
	sprite_bullet_.setTexture (texture_bullet_);
}
		
Object *Shootable::Act (float dt, sf::RenderWindow *win)
{
	if (!target_ || !target_->IsAlive () || clock_.getElapsedTime ().asSeconds () < 3.0)
		return nullptr;

	sf::Vector2f v;
	if (pos_.x >= target_->pos_.x)
		v = {	(float) (-700 * cos (atan ((pos_.y - target_->pos_.y) / (pos_.x - target_->pos_.x)))),
				(float) (-700 * sin (atan ((pos_.y - target_->pos_.y) / (pos_.x - target_->pos_.x))))};
	else
		v = {	(float) ( 700 * cos (atan ((pos_.y - target_->pos_.y) / (pos_.x - target_->pos_.x)))),
				(float) ( 700 * sin (atan ((pos_.y - target_->pos_.y) / (pos_.x - target_->pos_.x))))};

	bullets_.push_back ({pos_, v, 4, 0, 0, 10, 5, sprite_bullet_});

	clock_.restart ();
	return &bullets_.back ();
}

#endif //SHOOTABLE_CPP

