#include "Object.h"
#include "Movable.h"
#include "Rotatable.h"
#include "Shootable.h"
#include "Killable.h"
#include "Bullet.h"

sf::RenderWindow *Window = nullptr;
int i;

void CollidePair (Object *x1, Object *x2);

void RunGame ();
void Draw (std::list<Object *> objects, sf::Sprite background);
void Act (std::list<Object *>& objects, float time);
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
	sf::Texture texture_big_bounce;
	texture_big_bounce.loadFromFile ("Bounce2.png");
	sf::Texture texture_fragile_bounce;
	texture_fragile_bounce.loadFromFile ("Fragile_bounce.png");
	sf::Texture texture_bullet;
	texture_bullet.loadFromFile ("Bullet.png");
	sf::Texture texture_wall;
	texture_wall.loadFromFile ("Wall.png");
	sf::Texture texture_floor;
	texture_floor.loadFromFile ("Floor.png");
	sf::Texture texture_tank;
	texture_tank.loadFromFile ("Tank.png");

	sf::Sprite sprite_bounce;
	sprite_bounce.setTexture (texture_bounce);
	sf::Sprite sprite_big_bounce;
	sprite_big_bounce.setTexture (texture_big_bounce);
	sf::Sprite sprite_fragile_bounce;
	sprite_fragile_bounce.setTexture (texture_fragile_bounce);
	sf::Sprite sprite_bullet;
	sprite_bullet.setTexture (texture_bullet);
	sf::Sprite sprite_wall;
	sprite_wall.setTexture (texture_wall);
	sf::Sprite sprite_floor;
	sprite_floor.setTexture (texture_floor);
	sf::Sprite sprite_tank;
	sprite_tank.setTexture (texture_tank);

//	Object bounce ({40, 15}, sprite_big_bounce);
	Movable bounce0 ({135, 100}, {340, 290}, 10, 0, sprite_bounce);
	Movable bounce1 ({16, 16}, {230, 480}, 40, 0, sprite_bounce);
	Rotatable bounce2 ({100, 126}, -135, sprite_big_bounce);
//	Object bounce3 ({36, 36}, {110, 50}, 10, 0, sprite_fragile_bounce);
//	Object bounce4 ({50, 50}, {110, 50}, 10, 0, sprite_fragile_bounce);
	
	Killable bounce5 ({60, 60}, {10, 20}, 10, 0, -45, 20, sprite_bounce);
	Shootable wall ({200, 150}, -30, &bounce5, sprite_wall);
//	Object floor ({100, 160}, {0, 0}, 200, 0, sprite_floor);
//	Shootable floor1 ({100, 160}, {0, 0}, 200, 0, &bounce5, sprite_floor);
//	Killable tank ({160, 60}, {110, 50}, 10, 0, 20, sprite_tank);

		
	std::list<Object *> objects;
//	objects.push_back (&bounce);
	objects.push_back (&bounce0);
	objects.push_back (&bounce1);
	objects.push_back (&bounce2);
//	objects.push_back (&bounce3);
//	objects.push_back (&bounce4);
	objects.push_back (&bounce5);
	objects.push_back (&wall);
//	objects.push_back (&floor);
//	objects.push_back (&floor1);
//	objects.push_back (&tank);
		
	sf::Texture background_texture;
	background_texture.loadFromFile ("WhiteBackground.png", sf::IntRect (0, 0, 100, 100));
	background_texture.setRepeated (true);

	sf::Sprite background_sprite;
	background_sprite.setTexture (background_texture);
	background_sprite.setTextureRect (sf::IntRect (0, 0, Window->getSize ().x, Window->getSize ().y));

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
	
		RemoveDeadObjects (objects);

		Collide (objects);

		Act (objects, time);

		Draw (objects, background_sprite);
	}
}

void Draw (std::list<Object *> objects, sf::Sprite background)
{
	Window->clear ();

	Window->draw (background);
	
	for (Object *o : objects)
	{
		o->Draw ();
	}
	
	Window->display ();
}

void Act (std::list<Object *>& objects, float time)
{
	Object *new_object = nullptr;
	std::list<Object *> to_be_added;
	for (Object *o : objects)
	{
		if ((new_object = o->Act (time)))
		{
			to_be_added.push_back (new_object);
		}
	}

	for (Object *o : to_be_added)
	{
		objects.push_back (o);
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
				CollidePair (o1, o2);
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

