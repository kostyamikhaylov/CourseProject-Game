#include <iostream>
#include <vector>
#include <cmath>

#include <SFML/Graphics.hpp>

#define REACTION_TIME 0.01
#define GRAVITATION 700
#define sqr(x) (x) * (x)

sf::RenderWindow *Window = nullptr;

void RunGame ();

class Object
{
	public:
		sf::Vector2f pos_;
		sf::Vector2f v_;
		sf::Vector2f size_;

		float m_;
		float friction_;

		sf::Sprite sprite_;

		Object ();
		Object (sf::Vector2f pos, sf::Vector2f v, sf::Vector2f size, float m, float friction, sf::Sprite sprite);

		void Draw (sf::RenderWindow *win = Window) const;
		sf::Vector2f GetNewPosition (float dt) const;
		sf::Vector2f GetNewSpeed (float dt) const;
		void Move (float dt, sf::RenderWindow *win = Window);
		void Collide (Object *obstacle);
};

Object::Object ():
	pos_ (sf::Vector2f ()),
	v_ (sf::Vector2f ()),
	size_ (1, 1),
	m_ (),
	friction_ (),
	sprite_ (sf::Sprite ())
{
}

Object::Object (sf::Vector2f pos, sf::Vector2f v, sf::Vector2f size, float m, float friction, sf::Sprite sprite):
	pos_ (pos),
	v_ (v),
	size_ (size),
	m_ (m),
	friction_ (friction),
	sprite_ (sprite)
{
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

	if ((pos_.x - size_.x / 2 <= 0) || (pos_.x + size_.x / 2 >= win->getSize ().x))
		v_.x *= -1;
	if ((pos_.y - size_.y / 2 <= 0) || (pos_.y + size_.y / 2 >= win->getSize ().y))
		v_.y *= -1;
}

void Object::Collide (Object *obstacle)
{
	static int i = 0;
	
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
		std::cout << i++ << ") x collision\n";
		v_.x = - v_.x + 2 * mass_center_velocity.x;
		obstacle->v_.x = - obstacle->v_.x + 2 * mass_center_velocity.x;
	}
	if (size_.y / 2 + obstacle->size_.y / 2 >= abs (future_diff.y) 	&&
		size_.y / 2 + obstacle->size_.y / 2 < abs (diff.y)			&&
		size_.x / 2 + obstacle->size_.x / 2 >= abs (diff.x))
	{
		std::cout << i++ << ") y collision\n";
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

void Draw (std::vector<Object *> objects);
void Move (std::vector<Object *> objects, float time);
void Collide (std::vector<Object *> objects);

int main ()
{
	sf::RenderWindow w (sf::VideoMode (250, 250), "Bounce", sf::Style::Default & ~sf::Style::Resize);

	Window = &w;

	RunGame ();

	return 0;
}

void RunGame ()
{
	sf::Texture texture_bounce;
	texture_bounce.loadFromFile ("Bounce.png");
	sf::Texture texture_wall;
	texture_wall.loadFromFile ("Wall.png");
	sf::Texture texture_floor;
	texture_floor.loadFromFile ("Floor.png");

	sf::Sprite sprite_bounce;
	sprite_bounce.setTexture (texture_bounce);
	sf::Sprite sprite_wall;
	sprite_wall.setTexture (texture_wall);
	sf::Sprite sprite_floor;
	sprite_floor.setTexture (texture_floor);

	Object bounce ({6, 6}, {120, 90}, {10, 10}, 10, 0, sprite_bounce);
	Object wall ({200, 150}, {10, 15}, {50, 50}, 30, 0, sprite_wall);
	Object floor ({100, 160}, {0, 0}, {200, 80}, 200, 0, sprite_floor);
	
	sf::Texture texture_bounce1;
	texture_bounce1.loadFromFile ("Bounce.png");
	sf::Sprite sprite_bounce1;
	sprite_bounce1.setTexture (texture_bounce1);
	Object bounce1 ({16, 16}, {130, 80}, {10, 10}, 10, 0, sprite_bounce1);

	sf::Texture texture_bounce2;
	texture_bounce2.loadFromFile ("Bounce.png");
	sf::Sprite sprite_bounce2;
	sprite_bounce2.setTexture (texture_bounce2);
	Object bounce2 ({26, 26}, {100, 120}, {10, 10}, 10, 0, sprite_bounce2);

	sf::Texture texture_bounce3;
	texture_bounce3.loadFromFile ("Bounce.png");
	sf::Sprite sprite_bounce3;
	sprite_bounce3.setTexture (texture_bounce3);
	Object bounce3 ({36, 36}, {110, 50}, {10, 10}, 10, 0, sprite_bounce3);

	sf::Texture texture_bounce4;
	texture_bounce4.loadFromFile ("Bounce2.png");
	sf::Sprite sprite_bounce4;
	sprite_bounce4.setTexture (texture_bounce4);
	Object bounce4 ({50, 50}, {110, 50}, {22, 22}, 50, 0, sprite_bounce4);

	sf::Clock clock;

	while (Window->isOpen ())
	{
		float time = clock.restart ().asSeconds ();
		sf::Event event;

		while (Window->pollEvent (event))
		{
			if (event.type == sf::Event::Closed)
				Window->close ();
		}
	
		std::vector<Object *> objects;
		objects.push_back (&bounce);
		objects.push_back (&bounce1);
		objects.push_back (&bounce2);
		objects.push_back (&bounce3);
		objects.push_back (&bounce4);
		objects.push_back (&wall);
		objects.push_back (&floor);

		Collide (objects);

		Move (objects, time);

		Draw (objects);
	}
}

void Draw (std::vector<Object *> objects)
{
	Window->clear ();
	
	for (Object *o : objects)
	{
		o->Draw ();
	}
	
	Window->display ();
}

void Move (std::vector<Object *> objects, float time)
{
	for (Object *o : objects)
	{
		o->Move (time);
	}
}

void Collide (std::vector<Object *> objects)
{
	int i = 0;
	for (Object *o1 : objects)
	{
		int j = 0;
		for (Object *o2 : objects)
		{
			if (i < j)
				o1->Collide (o2);
			j++;
		}
		i++;
	}
}

