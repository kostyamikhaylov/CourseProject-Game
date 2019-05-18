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
	
	texture_bullet_.loadFromFile ("Bullet.png");
	sprite_bullet_.setTexture (texture_bullet_);
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
	std::cout << "=here\n";

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

void Shootable::ChooseTarget (std::list<Object *> objects, sf::RenderWindow *win)
{
	Object *cur_target = nullptr;
	sf::Vector2f distance (win->getSize ().x, win->getSize ().y);
	for (Object * o : objects)
	{
		if (	(o->GetCollisionType () == KILLABLE) &&
				(sqr (o->pos_.x - pos_.x) + sqr (o->pos_.y - pos_.y) < sqr (distance.x) + sqr (distance.y)))
		{
			distance.x = o->pos_.x - pos_.x;
			distance.y = o->pos_.y - pos_.y;
			cur_target = o;
		}
	}

	if (cur_target)
		target_ = cur_target;
	else
		target_ = nullptr;
}
		
Object *Shootable::Act (float dt, std::list<Object *> objects, sf::RenderWindow *win)
{
	if (!target_ || !target_->IsAlive ())
	{
		ChooseTarget (objects);
		if (!target_)
			return nullptr;
	}

	sf::Vector2f v;
	if (pos_.x >= target_->pos_.x)
		v = {	(float) (-BULLET_SPEED * cos (atan ((pos_.y - target_->pos_.y) / (pos_.x - target_->pos_.x)))),
				(float) (-BULLET_SPEED * sin (atan ((pos_.y - target_->pos_.y) / (pos_.x - target_->pos_.x))))};
	else
		v = {	(float) ( BULLET_SPEED * cos (atan ((pos_.y - target_->pos_.y) / (pos_.x - target_->pos_.x)))),
				(float) ( BULLET_SPEED * sin (atan ((pos_.y - target_->pos_.y) / (pos_.x - target_->pos_.x))))};
	
	if (v.x > 0)
		rotation_ = 180 / M_PI * atan (v.y / v.x);
	else
		rotation_ = 180 / M_PI * atan (v.y / v.x) + 180;


	if (clock_.getElapsedTime ().asSeconds () < TIME_PER_SHOOT)
		return nullptr;
	
	
	sf::Vector2f offset ({	(float) (0.8 * size_.x / 2 * cos (M_PI / 180 * rotation_)),
							(float) (0.8 * size_.x / 2 * sin (M_PI / 180 * rotation_))});
	
	bullets_.push_back ({pos_ + offset, v, 4, 0, 0, 10, 5, sprite_bullet_});

	clock_.restart ();
	return &bullets_.back ();
}

#endif //SHOOTABLE_CPP

