#include "Object.h"


void RunGame ();
void Draw (std::list<Object *> objects);
void Move (std::list<Object *> objects, float time);
void Collide (std::list<Object *> objects);
void RemoveDeadObjects (std::list<Object *>& objects);

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

	Object bounce ({6, 6}, {120, 90}, 10, 0, sprite_bounce);
	Object wall ({200, 150}, {10, 15}, 30, 0, sprite_wall);
	Object floor ({100, 160}, {0, 0}, 200, 0, sprite_floor);
	
	sf::Texture texture_bounce1;
	texture_bounce1.loadFromFile ("Bounce.png");
	sf::Sprite sprite_bounce1;
	sprite_bounce1.setTexture (texture_bounce1);
	Object bounce1 ({16, 16}, {130, 80}, 10, 0, sprite_bounce1);

	sf::Texture texture_bounce2;
	texture_bounce2.loadFromFile ("Bounce.png");
	sf::Sprite sprite_bounce2;
	sprite_bounce2.setTexture (texture_bounce2);
	Object bounce2 ({26, 26}, {100, 120}, 10, 0, sprite_bounce2);

	sf::Texture texture_bounce3;
	texture_bounce3.loadFromFile ("Bounce.png");
	sf::Sprite sprite_bounce3;
	sprite_bounce3.setTexture (texture_bounce3);
	Object bounce3 ({36, 36}, {110, 50}, 10, 0, sprite_bounce3);

	sf::Texture texture_bounce4;
	texture_bounce4.loadFromFile ("Bounce2.png");
	sf::Sprite sprite_bounce4;
	sprite_bounce4.setTexture (texture_bounce4);
	Object bounce4 ({50, 50}, {110, 50}, 50, 0, sprite_bounce4);

	sf::Texture texture_bounce5;
	texture_bounce5.loadFromFile ("Fragile_bounce.png");
	sf::Sprite sprite_bounce5;
	sprite_bounce5.setTexture (texture_bounce5);
	Killable bounce5 ({60, 60}, {110, 50}, 10, 0, 100, sprite_bounce5);
	
	sf::Texture texture_bounce6;
	texture_bounce6.loadFromFile ("Fragile_bounce.png");
	sf::Sprite sprite_bounce6;
	sprite_bounce6.setTexture (texture_bounce6);
	Killable bounce6 ({90, 65}, {110, 50}, 10, 0, 50, sprite_bounce6);

	sf::Texture texture_bounce7;
	texture_bounce7.loadFromFile ("Fragile_bounce.png");
	sf::Sprite sprite_bounce7;
	sprite_bounce7.setTexture (texture_bounce7);
	Killable bounce7 ({120, 55}, {110, 50}, 10, 0, 20, sprite_bounce7);


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
	
		std::list<Object *> objects;
		objects.push_back (&bounce);
		objects.push_back (&bounce1);
		objects.push_back (&bounce2);
		objects.push_back (&bounce3);
		objects.push_back (&bounce4);
		objects.push_back (&bounce5);
		objects.push_back (&bounce6);
		objects.push_back (&bounce7);
//		objects.push_back (&wall);
//		objects.push_back (&floor);
		
		RemoveDeadObjects (objects);

		Collide (objects);

		Move (objects, time);

		Draw (objects);
	}
}

void Draw (std::list<Object *> objects)
{
	Window->clear ();
	
	for (Object *o : objects)
	{
		o->Draw ();
	}
	
	Window->display ();
}

void Move (std::list<Object *> objects, float time)
{
	for (Object *o : objects)
	{
		o->Move (time);
	}
}

void Collide (std::list<Object *> objects)
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

void RemoveDeadObjects (std::list<Object *>& objects)
{
	std::list<Object *> to_be_deleted;
	
	for (Object *o : objects)
	{
		if (!o->IsAlive ())
		{
			to_be_deleted.push_back (o);
		}
	}

	for (Object *o : to_be_deleted)
		objects.remove (o);
}

