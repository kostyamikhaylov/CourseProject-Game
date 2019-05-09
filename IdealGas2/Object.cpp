#include <iostream>
#include <vector>
#include <cmath>

#include "Object.h"

#define REACTION_TIME 0.01
#define GRAVITATION 700
#define sqr(x) (x) * (x)


sf::RenderWindow *Window = nullptr;

Object::Object ():
	pos_ (sf::Vector2f ()),
	v_ (sf::Vector2f ()),
	size_ (sf::Vector2f ()),
	m_ (),
	friction_ (),
	sprite_ (sf::Sprite ())
{
	sf::FloatRect size = sprite_.getLocalBounds ();
	size_ = {size.width, size.height};
}

Object::Object (sf::Vector2f pos, sf::Vector2f v, float m, float friction, sf::Sprite sprite):
	pos_ (pos),
	v_ (v),
	size_ (sf::Vector2f ()),
	m_ (m),
	friction_ (friction),
	sprite_ (sprite)
{
	sf::FloatRect size = sprite_.getLocalBounds ();
	size_ = {size.width, size.height};
}

void Object::Draw (sf::RenderWindow *win) const
{
	sf::Sprite sprite = sprite_;

	sprite.setOrigin (size_.x / 2, size_.y / 2);
	sprite.setPosition (pos_);

	win->draw (sprite);
}

sf::Vector2f Object::GetNewPosition (float dt) const
{
	return sf::Vector2f (pos_.x + v_.x * dt, pos_.y + v_.y * dt + GRAVITATION * dt * dt / 2);
}

sf::Vector2f Object::GetNewSpeed (float dt) const
{
	return sf::Vector2f (v_.x, v_.y + GRAVITATION * dt);
}

void Object::Move (float dt, sf::RenderWindow *win)
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
}

void Object::Collide (Object *obstacle)
{
	sf::Vector2f diff ({pos_.x - obstacle->pos_.x, pos_.y - obstacle->pos_.y});
	sf::Vector2f future_diff ({	GetNewPosition (REACTION_TIME).x - obstacle->GetNewPosition (REACTION_TIME).x,
								GetNewPosition (REACTION_TIME).y - obstacle->GetNewPosition (REACTION_TIME).y});

	sf::Vector2f momentum (	m_ * v_.x + obstacle->m_ * obstacle->v_.x,
							m_ * v_.y + obstacle->m_ * obstacle->v_.y);
	
	sf::Vector2f mass_center_velocity ( momentum.x / (m_ + obstacle->m_),
										momentum.y / (m_ + obstacle->m_));

	if (size_.x / 2 + obstacle->size_.x / 2 >= abs (future_diff.x) 	&&
		size_.x / 2 + obstacle->size_.x / 2 < abs (diff.x)			&&
		size_.y / 2 + obstacle->size_.y / 2 >= abs (diff.y))
	{
		v_.x = - v_.x + 2 * mass_center_velocity.x;
		obstacle->v_.x = - obstacle->v_.x + 2 * mass_center_velocity.x;
	}
	if (size_.y / 2 + obstacle->size_.y / 2 >= abs (future_diff.y) 	&&
		size_.y / 2 + obstacle->size_.y / 2 < abs (diff.y)			&&
		size_.x / 2 + obstacle->size_.x / 2 >= abs (diff.x))
	{
		v_.y = - v_.y + 2 * mass_center_velocity.y;
		obstacle->v_.y = - obstacle->v_.y + 2 * mass_center_velocity.y;
	}

/*
	sf::Vector2f diff ({pos_.x - obstacle->pos_.x, pos_.y - obstacle->pos_.y});
	sf::Vector2f future_diff ({		pos_.x 				+ 	v_.x 			* 	REACTION_TIME -
								(	obstacle->pos_.x 	+ 	obstacle->v_.x 	* 	REACTION_TIME),
									pos_.y				+ 	v_.y 			* 	REACTION_TIME -
								(	obstacle->pos_.y	+	obstacle->v_.y 	* 	REACTION_TIME)});

	if (sqr (size_.x / 2 + obstacle->size_.x / 2) +
		sqr (size_.y / 2 + obstacle->size_.y / 2) >=
		sqr (future_diff.x) + sqr (future_diff.y))
	{
		std::cout << "{" << future_diff.x << ", " << future_diff.y << "}\n";

		if (size_.x / 2 + obstacle->size_.x / 2 >= abs (future_diff.x) &&
			size_.x / 2 + obstacle->size_.x / 2 < abs (diff.x))
		{
			std::cout << i++ << ") x collision\n";
			v_.x *= -1;
		}
		if (size_.y / 2 + obstacle->size_.y / 2 >= abs (future_diff.y) &&
			size_.y / 2 + obstacle->size_.y / 2 < abs (diff.y))
		{
			std::cout << i++ << ") y collision\n";
			v_.y *= -1;
		}
	}
*/
/*
	static sf::Clock clock_x, clock_y;
	sf::Vector2f diff ({pos_.x - obstacle->pos_.x, pos_.y - obstacle->pos_.y});
	sf::Vector2f future_diff ({		pos_.x 				+ 	v_.x 			* 	REACTION_TIME -
								(	obstacle->pos_.x 	+ 	obstacle->v_.x 	* 	REACTION_TIME),
									pos_.y				+ 	v_.y 			* 	REACTION_TIME -
								(	obstacle->pos_.y	+	obstacle->v_.y 	* 	REACTION_TIME)});

	if (sqr (size_.x / 2 + obstacle->size_.x / 2) +
		sqr (size_.y / 2 + obstacle->size_.y / 2) >=
		sqr (future_diff.x) + sqr (future_diff.y))
	{
		float time_x = clock_x.getElapsedTime ().asSeconds ();
		float time_y = clock_y.getElapsedTime ().asSeconds ();

		std::cout << "{" << future_diff.x << ", " << future_diff.y << "}\n";
		std::cout << "time_x: " << time_x << ", time_y: " << time_y << "\n";

		if (size_.x / 2 + obstacle->size_.x / 2 >= abs (future_diff.x) &&
			size_.x / 2 + obstacle->size_.x / 2 < abs (diff.x) &&
			time_x >= REACTION_TIME)
		{
			std::cout << i++ << ") x collision\n";
			v_.x *= -1;
			clock_x.restart ();
		}
		if (size_.y / 2 + obstacle->size_.y / 2 >= abs (future_diff.y) &&
			size_.y / 2 + obstacle->size_.y / 2 < abs (diff.y) &&
			time_y >= REACTION_TIME)
		{
			std::cout << i++ << ") y collision\n";
			v_.y *= -1;
			clock_y.restart ();
		}
	}
*/
/*
	sf::Vector2f diff ({pos_.x - obstacle->pos_.x, pos_.y - obstacle->pos_.y});
//	std::cout << "{" << diff.x << ", " << diff.y << "}\n";
	if (sqr (size_.x / 2 + obstacle->size_.x / 2) +
		sqr (size_.y / 2 + obstacle->size_.y / 2) >=
		sqr (diff.x) + sqr (diff.y))
	{
		if (size_.x / 2 + obstacle->size_.x / 2 >= abs (diff.x))
		{
			std::cout << "x collision\n";
			v_.x *= -1;
		}
		if (size_.y / 2 + obstacle->size_.y / 2 >= abs (diff.y))
		{
			std::cout << "y collision\n";
			v_.y *= -1;
		}
	}
*/
}

Killable::Killable ():
	Object (),
	hp_ ()
{
	sf::FloatRect size = sprite_.getLocalBounds ();
	size_ = {size.width, size.height};
}

Killable::Killable (sf::Vector2f pos, sf::Vector2f v, float m, float friction, int hp, sf::Sprite sprite):
	Object (pos, v, m, friction, sprite),
	hp_ (hp)
{
	sf::FloatRect size = sprite_.getLocalBounds ();
	size_ = {size.width, size.height};
}

void Killable::Move (float dt, sf::RenderWindow *win)
{
	pos_ = GetNewPosition (dt);
	v_ = GetNewSpeed (dt);

	if (	(GetNewPosition (REACTION_TIME).x - size_.x / 2 <= 0)					||
			(GetNewPosition (REACTION_TIME).x + size_.x / 2 >= win->getSize ().x)	)
	{
		v_.x *= -1;
		hp_--;
	}
	if (	(GetNewPosition (REACTION_TIME).y - size_.y / 2 <= 0)					||
			(GetNewPosition (REACTION_TIME).y + size_.y / 2 >= win->getSize ().y)	)
	{
		v_.y *= -1;
		hp_--;
	}
	
	v_.x *= (1 - friction_);
	v_.y *= (1 - friction_);
}

void Killable::Collide (Object *obstacle)
{
	sf::Vector2f diff ({pos_.x - obstacle->pos_.x, pos_.y - obstacle->pos_.y});
	sf::Vector2f future_diff ({	GetNewPosition (REACTION_TIME).x - obstacle->GetNewPosition (REACTION_TIME).x,
								GetNewPosition (REACTION_TIME).y - obstacle->GetNewPosition (REACTION_TIME).y});

	sf::Vector2f momentum (	m_ * v_.x + obstacle->m_ * obstacle->v_.x,
							m_ * v_.y + obstacle->m_ * obstacle->v_.y);
	
	sf::Vector2f mass_center_velocity ( momentum.x / (m_ + obstacle->m_),
										momentum.y / (m_ + obstacle->m_));

	if (size_.x / 2 + obstacle->size_.x / 2 >= abs (future_diff.x) 	&&
		size_.x / 2 + obstacle->size_.x / 2 < abs (diff.x)			&&
		size_.y / 2 + obstacle->size_.y / 2 >= abs (diff.y))
	{
		v_.x = - v_.x + 2 * mass_center_velocity.x;
		obstacle->v_.x = - obstacle->v_.x + 2 * mass_center_velocity.x;
	}
	if (size_.y / 2 + obstacle->size_.y / 2 >= abs (future_diff.y) 	&&
		size_.y / 2 + obstacle->size_.y / 2 < abs (diff.y)			&&
		size_.x / 2 + obstacle->size_.x / 2 >= abs (diff.x))
	{
		v_.y = - v_.y + 2 * mass_center_velocity.y;
		obstacle->v_.y = - obstacle->v_.y + 2 * mass_center_velocity.y;
	}
}
