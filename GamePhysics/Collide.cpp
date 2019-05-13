#include "Object.h"
#include "Movable.h"
#include "Rotatable.h"
#include "Shootable.h"
#include "Killable.h"
#include "Bullet.h"


void CollidePair (Object *x1, Object *x2)
{
	switch (x1->GetCollisionType ())
	{
		case OBJECT:
			switch (x2->GetCollisionType ())
			{
				case OBJECT:
					break;

				case MOVABLE:
					break;
				
				case ROTATABLE:
					break;

				case SHOOTABLE:
					break;
				
				case KILLABLE:
					break;

				case BULLET:
					break;

				default:
					break;
			}
			break;

		case MOVABLE:
			switch (x2->GetCollisionType ())
			{
				case OBJECT:
					break;

				case MOVABLE:
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
							std::cout << i++ << ") x collision\n";
							o1->v_.x = - o1->v_.x + 2 * mass_center_velocity.x;
							o2->v_.x = - o2->v_.x + 2 * mass_center_velocity.x;
						}
						if (o1->size_.y / 2 + o2->size_.y / 2 >= abs (future_diff.y) 	&&
							o1->size_.y / 2 + o2->size_.y / 2 < abs (diff.y)			&&
							o1->size_.x / 2 + o2->size_.x / 2 >= abs (diff.x))
						{
							std::cout << i++ << ") y collision\n";
							o1->v_.y = - o1->v_.y + 2 * mass_center_velocity.y;
							o2->v_.y = - o2->v_.y + 2 * mass_center_velocity.y;
						}
					}
				}
					break;
				
				case ROTATABLE:
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
							std::cout << i++ << ") x collision\n";
							o1->v_.x *= -1;
						}
						if (o1->size_.y / 2 + o2->size_.y / 2 >= abs (future_diff.y) 	&&
							o1->size_.y / 2 + o2->size_.y / 2 < abs (diff.y)			&&
							o1->size_.x / 2 + o2->size_.x / 2 >= abs (diff.x))
						{
							std::cout << i++ << ") y collision\n";
							o1->v_.y *= -1;
						}
					}
				}
					break;

				case SHOOTABLE:
				{
					Movable *o1 = dynamic_cast<Movable *> (x1);
					Shootable *o2 = dynamic_cast<Shootable *> (x2);

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
							std::cout << i++ << ") x collision\n";
							o1->v_.x *= -1;
						}
						if (o1->size_.y / 2 + o2->size_.y / 2 >= abs (future_diff.y) 	&&
							o1->size_.y / 2 + o2->size_.y / 2 < abs (diff.y)			&&
							o1->size_.x / 2 + o2->size_.x / 2 >= abs (diff.x))
						{
							std::cout << i++ << ") y collision\n";
							o1->v_.y *= -1;
						}
					}
				}
					break;
				
				case KILLABLE:
				{
					Movable *o1 = dynamic_cast<Movable *> (x1);
					Killable *o2 = dynamic_cast<Killable *> (x2);

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
							std::cout << i++ << ") x collision\n";
							o1->v_.x = - o1->v_.x + 2 * mass_center_velocity.x;
							o2->v_.x = - o2->v_.x + 2 * mass_center_velocity.x;
						}
						if (o1->size_.y / 2 + o2->size_.y / 2 >= abs (future_diff.y) 	&&
							o1->size_.y / 2 + o2->size_.y / 2 < abs (diff.y)			&&
							o1->size_.x / 2 + o2->size_.x / 2 >= abs (diff.x))
						{
							std::cout << i++ << ") y collision\n";
							o1->v_.y = - o1->v_.y + 2 * mass_center_velocity.y;
							o2->v_.y = - o2->v_.y + 2 * mass_center_velocity.y;
						}
					}
				}
					break;

				case BULLET:
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
					break;

				default:
					break;
			}
			break;

		case ROTATABLE:
			switch (x2->GetCollisionType ())
			{
				case OBJECT:
					break;

				case MOVABLE:
				{
					Movable *o1 = dynamic_cast<Movable *> (x2);
					Rotatable *o2 = dynamic_cast<Rotatable *> (x1);

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
							std::cout << i++ << ") x collision\n";
							o1->v_.x *= -1;
						}
						if (o1->size_.y / 2 + o2->size_.y / 2 >= abs (future_diff.y) 	&&
							o1->size_.y / 2 + o2->size_.y / 2 < abs (diff.y)			&&
							o1->size_.x / 2 + o2->size_.x / 2 >= abs (diff.x))
						{
							std::cout << i++ << ") y collision\n";
							o1->v_.y *= -1;
						}
					}
				}
					break;
				
				case ROTATABLE:
					break;

				case SHOOTABLE:
					break;
				
				case KILLABLE:
				{
					Rotatable *o1 = dynamic_cast<Rotatable *> (x1);
					Killable *o2 = dynamic_cast<Killable *> (x2);

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
					{
						if (o1->size_.x / 2 + o2->size_.x / 2 >= abs (future_diff.x) 	&&
							o1->size_.x / 2 + o2->size_.x / 2 < abs (diff.x)			&&
							o1->size_.y / 2 + o2->size_.y / 2 >= abs (diff.y))
						{
							std::cout << i++ << ") x collision\n";
							o2->v_.x *= -1;
						}
						if (o1->size_.y / 2 + o2->size_.y / 2 >= abs (future_diff.y) 	&&
							o1->size_.y / 2 + o2->size_.y / 2 < abs (diff.y)			&&
							o1->size_.x / 2 + o2->size_.x / 2 >= abs (diff.x))
						{
							std::cout << i++ << ") y collision\n";
							o2->v_.y *= -1;
						}
					}
				}
					break;

				case BULLET:
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
					break;

				default:
					break;
			}
			break;

		case SHOOTABLE:
			switch (x2->GetCollisionType ())
			{
				case OBJECT:
					break;

				case MOVABLE:
				{
					Movable *o1 = dynamic_cast<Movable *> (x2);
					Shootable *o2 = dynamic_cast<Shootable *> (x1);

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
							std::cout << i++ << ") x collision\n";
							o1->v_.x *= -1;
						}
						if (o1->size_.y / 2 + o2->size_.y / 2 >= abs (future_diff.y) 	&&
							o1->size_.y / 2 + o2->size_.y / 2 < abs (diff.y)			&&
							o1->size_.x / 2 + o2->size_.x / 2 >= abs (diff.x))
						{
							std::cout << i++ << ") y collision\n";
							o1->v_.y *= -1;
						}
					}
				}
					break;
				
				case ROTATABLE:
					break;

				case SHOOTABLE:
					break;
				
				case KILLABLE:
				{
					Shootable *o1 = dynamic_cast<Shootable *> (x1);
					Killable *o2 = dynamic_cast<Killable *> (x2);

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
					{
						if (o1->size_.x / 2 + o2->size_.x / 2 >= abs (future_diff.x) 	&&
							o1->size_.x / 2 + o2->size_.x / 2 < abs (diff.x)			&&
							o1->size_.y / 2 + o2->size_.y / 2 >= abs (diff.y))
						{
							std::cout << i++ << ") x collision\n";
							o2->v_.x *= -1;
						}
						if (o1->size_.y / 2 + o2->size_.y / 2 >= abs (future_diff.y) 	&&
							o1->size_.y / 2 + o2->size_.y / 2 < abs (diff.y)			&&
							o1->size_.x / 2 + o2->size_.x / 2 >= abs (diff.x))
						{
							std::cout << i++ << ") y collision\n";
							o2->v_.y *= -1;
						}
					}
				}
					break;

				case BULLET:
				{
					Shootable *o1 = dynamic_cast<Shootable *> (x1);
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
					break;

				default:
					break;
			}
			break;

		case KILLABLE:
			switch (x2->GetCollisionType ())
			{
				case OBJECT:
					break;

				case MOVABLE:
				{
					Movable *o1 = dynamic_cast<Movable *> (x2);
					Killable *o2 = dynamic_cast<Killable *> (x1);

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
							std::cout << i++ << ") x collision\n";
							o1->v_.x = - o1->v_.x + 2 * mass_center_velocity.x;
							o2->v_.x = - o2->v_.x + 2 * mass_center_velocity.x;
						}
						if (o1->size_.y / 2 + o2->size_.y / 2 >= abs (future_diff.y) 	&&
							o1->size_.y / 2 + o2->size_.y / 2 < abs (diff.y)			&&
							o1->size_.x / 2 + o2->size_.x / 2 >= abs (diff.x))
						{
							std::cout << i++ << ") y collision\n";
							o1->v_.y = - o1->v_.y + 2 * mass_center_velocity.y;
							o2->v_.y = - o2->v_.y + 2 * mass_center_velocity.y;
						}
					}
				}
					break;
				
				case ROTATABLE:
				{
					Rotatable *o1 = dynamic_cast<Rotatable *> (x2);
					Killable *o2 = dynamic_cast<Killable *> (x1);

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
					{
						if (o1->size_.x / 2 + o2->size_.x / 2 >= abs (future_diff.x) 	&&
							o1->size_.x / 2 + o2->size_.x / 2 < abs (diff.x)			&&
							o1->size_.y / 2 + o2->size_.y / 2 >= abs (diff.y))
						{
							std::cout << i++ << ") x collision\n";
							o2->v_.x *= -1;
						}
						if (o1->size_.y / 2 + o2->size_.y / 2 >= abs (future_diff.y) 	&&
							o1->size_.y / 2 + o2->size_.y / 2 < abs (diff.y)			&&
							o1->size_.x / 2 + o2->size_.x / 2 >= abs (diff.x))
						{
							std::cout << i++ << ") y collision\n";
							o2->v_.y *= -1;
						}
					}
				}
					break;

				case SHOOTABLE:
				{
					Shootable *o1 = dynamic_cast<Shootable *> (x2);
					Killable *o2 = dynamic_cast<Killable *> (x1);

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
					{
						if (o1->size_.x / 2 + o2->size_.x / 2 >= abs (future_diff.x) 	&&
							o1->size_.x / 2 + o2->size_.x / 2 < abs (diff.x)			&&
							o1->size_.y / 2 + o2->size_.y / 2 >= abs (diff.y))
						{
							std::cout << i++ << ") x collision\n";
							o2->v_.x *= -1;
						}
						if (o1->size_.y / 2 + o2->size_.y / 2 >= abs (future_diff.y) 	&&
							o1->size_.y / 2 + o2->size_.y / 2 < abs (diff.y)			&&
							o1->size_.x / 2 + o2->size_.x / 2 >= abs (diff.x))
						{
							std::cout << i++ << ") y collision\n";
							o2->v_.y *= -1;
						}
					}
				}
					break;
				
				case KILLABLE:
				{
					Killable *o1 = dynamic_cast<Killable *> (x1);
					Killable *o2 = dynamic_cast<Killable *> (x2);

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
							std::cout << i++ << ") x collision\n";
							o1->v_.x = - o1->v_.x + 2 * mass_center_velocity.x;
							o2->v_.x = - o2->v_.x + 2 * mass_center_velocity.x;
						}
						if (o1->size_.y / 2 + o2->size_.y / 2 >= abs (future_diff.y) 	&&
							o1->size_.y / 2 + o2->size_.y / 2 < abs (diff.y)			&&
							o1->size_.x / 2 + o2->size_.x / 2 >= abs (diff.x))
						{
							std::cout << i++ << ") y collision\n";
							o1->v_.y = - o1->v_.y + 2 * mass_center_velocity.y;
							o2->v_.y = - o2->v_.y + 2 * mass_center_velocity.y;
						}
					}
				}
					break;

				case BULLET:
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
					break;

				default:
					break;
			}
			break;

		case BULLET:
			switch (x2->GetCollisionType ())
			{
				case OBJECT:
					break;

				case MOVABLE:
				{
					Movable *o1 = dynamic_cast<Movable *> (x2);
					Bullet *o2 = dynamic_cast<Bullet *> (x1);

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
					break;
				
				case ROTATABLE:
				{
					Rotatable *o1 = dynamic_cast<Rotatable *> (x2);
					Bullet *o2 = dynamic_cast<Bullet *> (x1);

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
					break;

				case SHOOTABLE:
				{
					Shootable *o1 = dynamic_cast<Shootable *> (x2);
					Bullet *o2 = dynamic_cast<Bullet *> (x1);

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
					break;
				
				case KILLABLE:
				{
					Killable *o1 = dynamic_cast<Killable *> (x2);
					Bullet *o2 = dynamic_cast<Bullet *> (x1);

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
					break;

				case BULLET:
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
					break;

				default:
					break;
			}
			break;
			
		default:
			break;
	}
}
