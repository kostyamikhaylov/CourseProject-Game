#ifndef COLLIDE_CPP
#define COLLIDE_CPP

#include "Object.h"
#include "Movable.h"
#include "Rotatable.h"
#include "Shootable.h"
#include "Killable.h"
#include "Bullet.h"

void NoCollision (Object *x1, Object *x2);
void MovableMovable (Object *x1, Object *x2);
void MovableMotionless (Object *x1, Object *x2);
void MovableBullet (Object *x1, Object *x2);
void RotatableBullet (Object *x1, Object *x2);
void KillableBullet (Object *x1, Object *x2);
void BulletBullet (Object *x1, Object *x2);

void CollidePair (Object *x1, Object *x2)
{
	switch (x1->GetCollisionType ())
	{
		case OBJECT:
			switch (x2->GetCollisionType ())
			{
				case OBJECT:
					NoCollision (x1, x2);
					break;

				case MOVABLE:
					NoCollision (x1, x2);
					break;
				
				case ROTATABLE:
					NoCollision (x1, x2);
					break;

				case SHOOTABLE:
					NoCollision (x1, x2);
					break;
				
				case KILLABLE:
					NoCollision (x1, x2);
					break;

				case BULLET:
					NoCollision (x1, x2);
					break;

				default:
					break;
			}
			break;

		case MOVABLE:
			switch (x2->GetCollisionType ())
			{
				case OBJECT:
					NoCollision (x1, x2);
					break;

				case MOVABLE:
					MovableMovable (x1, x2);
					break;
				
				case ROTATABLE:
					MovableMotionless (x1, x2);
					break;

				case SHOOTABLE:
					MovableMotionless (x1, x2);
					break;
				
				case KILLABLE:
					MovableMovable (x1, x2);
					break;

				case BULLET:
					MovableBullet (x1, x2);
					break;

				default:
					break;
			}
			break;

		case ROTATABLE:
			switch (x2->GetCollisionType ())
			{
				case OBJECT:
					NoCollision (x1, x2);
					break;

				case MOVABLE:
					MovableMotionless (x2, x1);
					break;
				
				case ROTATABLE:
					NoCollision (x1, x2);
					break;

				case SHOOTABLE:
					NoCollision (x1, x2);
					break;
				
				case KILLABLE:
					MovableMotionless (x2, x1);
					break;

				case BULLET:
					RotatableBullet (x1, x2);
					break;

				default:
					break;
			}
			break;

		case SHOOTABLE:
			switch (x2->GetCollisionType ())
			{
				case OBJECT:
					NoCollision (x1, x2);
					break;

				case MOVABLE:
					MovableMotionless (x2, x1);
					break;
				
				case ROTATABLE:
					NoCollision (x1, x2);
					break;

				case SHOOTABLE:
					NoCollision (x1, x2);
					break;
				
				case KILLABLE:
					MovableMotionless (x2, x1);
					break;

				case BULLET:
					RotatableBullet (x1, x2);
					break;

				default:
					break;
			}
			break;

		case KILLABLE:
			switch (x2->GetCollisionType ())
			{
				case OBJECT:
					NoCollision (x1, x2);
					break;

				case MOVABLE:
					MovableMovable (x1, x2);
					break;
				
				case ROTATABLE:
					MovableMotionless (x1, x2);
					break;

				case SHOOTABLE:
					MovableMotionless (x1, x2);
					break;
				
				case KILLABLE:
					MovableMovable (x1, x2);
					break;

				case BULLET:
					KillableBullet (x1, x2);
					break;

				default:
					break;
			}
			break;

		case BULLET:
			switch (x2->GetCollisionType ())
			{
				case OBJECT:
					NoCollision (x1, x2);
					break;

				case MOVABLE:
					MovableBullet (x2, x1);
					break;
				
				case ROTATABLE:
					RotatableBullet (x2, x1);
					break;

				case SHOOTABLE:
					RotatableBullet (x2, x1);
					break;
				
				case KILLABLE:
					KillableBullet (x2, x1);
					break;

				case BULLET:
					BulletBullet (x1, x2);
					break;

				default:
					break;
			}
			break;
			
		default:
			break;
	}
}

void NoCollision (Object *x1, Object *x2)
{
	return ;
}

void MovableMovable (Object *x1, Object *x2)
{
	Movable *o1 = dynamic_cast<Movable *> (x1);
	Movable *o2 = dynamic_cast<Movable *> (x2);

	sf::Vector2f diff ({o1->pos_.x - o2->pos_.x, o1->pos_.y - o2->pos_.y});
	sf::Vector2f future_diff ({	o1->GetNewPosition (REACTION_TIME).x - o2->GetNewPosition (REACTION_TIME).x,
								o1->GetNewPosition (REACTION_TIME).y - o2->GetNewPosition (REACTION_TIME).y});

	if ((	o1->size_.x / 2 + o2->size_.x / 2 >= abs (future_diff.x) 		&&
			o1->size_.x / 2 + o2->size_.x / 2 < abs (diff.x)				&&
			o1->size_.y / 2 + o2->size_.y / 2 >= abs (diff.y)			)
			||
		(	o1->size_.y / 2 + o2->size_.y / 2 >= abs (future_diff.y)		&&
			o1->size_.y / 2 + o2->size_.y / 2 < abs (diff.y)				&&
			o1->size_.x / 2 + o2->size_.x / 2 >= abs (diff.x)			))
	{
		sf::Vector2f momentum (	o1->m_ * o1->v_.x + o2->m_ * o2->v_.x,
								o1->m_ * o1->v_.y + o2->m_ * o2->v_.y);
		
		sf::Vector2f mass_center_velocity ( momentum.x / (o1->m_ + o2->m_),
											momentum.y / (o1->m_ + o2->m_));

		if (o1->size_.x / 2 + o2->size_.x / 2 >= abs (future_diff.x) 	&&
			o1->size_.x / 2 + o2->size_.x / 2 < abs (diff.x)			&&
			o1->size_.y / 2 + o2->size_.y / 2 >= abs (diff.y))
		{
			o1->v_.x = - o1->v_.x + 2 * mass_center_velocity.x;
			o2->v_.x = - o2->v_.x + 2 * mass_center_velocity.x;
		}
		if (o1->size_.y / 2 + o2->size_.y / 2 >= abs (future_diff.y) 	&&
			o1->size_.y / 2 + o2->size_.y / 2 < abs (diff.y)			&&
			o1->size_.x / 2 + o2->size_.x / 2 >= abs (diff.x))
		{
			o1->v_.y = - o1->v_.y + 2 * mass_center_velocity.y;
			o2->v_.y = - o2->v_.y + 2 * mass_center_velocity.y;
		}
	}
}

void MovableMotionless (Object *x1, Object *x2)
{
	Movable *o1 = dynamic_cast<Movable *> (x1);
	Rotatable *o2 = dynamic_cast<Rotatable *> (x2);

	sf::Vector2f diff ({o1->pos_.x - o2->pos_.x, o1->pos_.y - o2->pos_.y});
	sf::Vector2f future_diff ({	o1->GetNewPosition (REACTION_TIME).x - o2->pos_.x,
								o1->GetNewPosition (REACTION_TIME).y - o2->pos_.y});

	if ((	o1->size_.x / 2 + o2->size_.x / 2 >= abs (future_diff.x) 		&&
			o1->size_.x / 2 + o2->size_.x / 2 < abs (diff.x)				&&
			o1->size_.y / 2 + o2->size_.y / 2 >= abs (diff.y)			)
			||
		(	o1->size_.y / 2 + o2->size_.y / 2 >= abs (future_diff.y)		&&
			o1->size_.y / 2 + o2->size_.y / 2 < abs (diff.y)				&&
			o1->size_.x / 2 + o2->size_.x / 2 >= abs (diff.x)			))
	{
		if (o1->size_.x / 2 + o2->size_.x / 2 >= abs (future_diff.x) 	&&
			o1->size_.x / 2 + o2->size_.x / 2 < abs (diff.x)			&&
			o1->size_.y / 2 + o2->size_.y / 2 >= abs (diff.y))
		{
			o1->v_.x *= -1;
		}
		if (o1->size_.y / 2 + o2->size_.y / 2 >= abs (future_diff.y) 	&&
			o1->size_.y / 2 + o2->size_.y / 2 < abs (diff.y)			&&
			o1->size_.x / 2 + o2->size_.x / 2 >= abs (diff.x))
		{
			o1->v_.y *= -1;
		}
	}
}

void MovableBullet (Object *x1, Object *x2)
{
	Movable *o1 = dynamic_cast<Movable *> (x1);
	Bullet *o2 = dynamic_cast<Bullet *> (x2);

	sf::Vector2f diff ({o1->pos_.x - o2->pos_.x, o1->pos_.y - o2->pos_.y});
	sf::Vector2f future_diff ({	o1->GetNewPosition (REACTION_TIME).x - o2->GetNewPosition (REACTION_TIME).x,
								o1->GetNewPosition (REACTION_TIME).y - o2->GetNewPosition (REACTION_TIME).y});

	if ((	o1->size_.x / 2 + o2->size_.x / 2 >= abs (future_diff.x) 		&&
			o1->size_.x / 2 + o2->size_.x / 2 < abs (diff.x)				&&
			o1->size_.y / 2 + o2->size_.y / 2 >= abs (diff.y)			)
			||
		(	o1->size_.y / 2 + o2->size_.y / 2 >= abs (future_diff.y)		&&
			o1->size_.y / 2 + o2->size_.y / 2 < abs (diff.y)				&&
			o1->size_.x / 2 + o2->size_.x / 2 >= abs (diff.x)			))
		o2->hp_ = 0;
}

void RotatableBullet (Object *x1, Object *x2)
{
	Rotatable *o1 = dynamic_cast<Rotatable *> (x1);
	Bullet *o2 = dynamic_cast<Bullet *> (x2);

	sf::Vector2f diff ({o1->pos_.x - o2->pos_.x, o1->pos_.y - o2->pos_.y});
	sf::Vector2f future_diff ({	o1->pos_.x - o2->GetNewPosition (REACTION_TIME).x,
								o1->pos_.y - o2->GetNewPosition (REACTION_TIME).y});

	if ((	o1->size_.x / 2 + o2->size_.x / 2 >= abs (future_diff.x) 		&&
			o1->size_.x / 2 + o2->size_.x / 2 < abs (diff.x)				&&
			o1->size_.y / 2 + o2->size_.y / 2 >= abs (diff.y)			)
			||
		(	o1->size_.y / 2 + o2->size_.y / 2 >= abs (future_diff.y)		&&
			o1->size_.y / 2 + o2->size_.y / 2 < abs (diff.y)				&&
			o1->size_.x / 2 + o2->size_.x / 2 >= abs (diff.x)			))
		o2->hp_ = 0;
}
				
void KillableBullet (Object *x1, Object *x2)
{
	Killable *o1 = dynamic_cast<Killable *> (x1);
	Bullet *o2 = dynamic_cast<Bullet *> (x2);

	sf::Vector2f diff ({o1->pos_.x - o2->pos_.x, o1->pos_.y - o2->pos_.y});
	sf::Vector2f future_diff ({	o1->GetNewPosition (REACTION_TIME).x - o2->GetNewPosition (REACTION_TIME).x,
								o1->GetNewPosition (REACTION_TIME).y - o2->GetNewPosition (REACTION_TIME).y});

	if ((	o1->size_.x / 2 + o2->size_.x / 2 >= abs (future_diff.x) 		&&
			o1->size_.x / 2 + o2->size_.x / 2 < abs (diff.x)				&&
			o1->size_.y / 2 + o2->size_.y / 2 >= abs (diff.y)			)
			||
		(	o1->size_.y / 2 + o2->size_.y / 2 >= abs (future_diff.y)		&&
			o1->size_.y / 2 + o2->size_.y / 2 < abs (diff.y)				&&
			o1->size_.x / 2 + o2->size_.x / 2 >= abs (diff.x)			))
	{
		o1->hp_ -= o2->damage_;
		o2->hp_ = 0;
	}
}

void BulletBullet (Object *x1, Object *x2)
{
	Bullet *o1 = dynamic_cast<Bullet *> (x1);
	Bullet *o2 = dynamic_cast<Bullet *> (x2);

	sf::Vector2f diff ({o1->pos_.x - o2->pos_.x, o1->pos_.y - o2->pos_.y});
	sf::Vector2f future_diff ({	o1->GetNewPosition (REACTION_TIME).x - o2->GetNewPosition (REACTION_TIME).x,
								o1->GetNewPosition (REACTION_TIME).y - o2->GetNewPosition (REACTION_TIME).y});

	if ((	o1->size_.x / 2 + o2->size_.x / 2 >= abs (future_diff.x) 		&&
			o1->size_.x / 2 + o2->size_.x / 2 < abs (diff.x)				&&
			o1->size_.y / 2 + o2->size_.y / 2 >= abs (diff.y)			)
			||
		(	o1->size_.y / 2 + o2->size_.y / 2 >= abs (future_diff.y)		&&
			o1->size_.y / 2 + o2->size_.y / 2 < abs (diff.y)				&&
			o1->size_.x / 2 + o2->size_.x / 2 >= abs (diff.x)			))
	{
		o1->hp_ = 0;
		o2->hp_ = 0;
	}
}

#endif //COLLIDE_CPP

