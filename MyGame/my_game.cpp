#include "Object.h"
#include "Movable.h"
#include "Rotatable.h"
#include "Shootable.h"
#include "Killable.h"
#include "Bullet.h"

#include "Menus.h"

#include <string>
#include <algorithm>
#include <sys/time.h>
#include <setjmp.h>

#define MONEY_PER_ENEMY 50
#define MONEY_PER_CANNON 50

sf::RenderWindow *Window = nullptr;
jmp_buf env;
int i;
unsigned int hp = 10;
unsigned int money = 200;
sf::RectangleShape rectangle1;
sf::RectangleShape rectangle2;
sf::Font font;

void CollidePair (Object *x1, Object *x2);

void StartMenu (sf::RenderWindow *win);
void Pause (sf::RenderWindow *win);
void GameOver (sf::RenderWindow *win);

void InitializeGlobalVariables ();
void RunGame ();
void Draw (std::list<Object *> objects, sf::Sprite background, sf::Sprite sprite_hp, sf::Sprite sprite_money);
void Act (std::list<Object *>& objects, float time);
void Collide (std::list<Object *> objects);
void RemoveDeadObjects (std::list<Object *>& objects);
void RemoveDeadEnemies (std::list<Killable>& enemies, std::list<Shootable>& defence);
void CheckEnemies (std::list<Killable>& enemies);
Killable GenerateRandomEnemy (sf::Sprite enemy_sprite, sf::Time game_time);

int main ()
{
	sf::RenderWindow w (sf::VideoMode (700, 700), "Game", sf::Style::Default & ~sf::Style::Resize);

	Window = &w;

	StartMenu (Window);
	
	setjmp(env);

	InitializeGlobalVariables ();

	RunGame ();

	GameOver (Window);

	return 0;
}

void InitializeGlobalVariables ()
{
	hp = 10;
	money = 200;
	
	rectangle1.setSize (sf::Vector2f (Window->getSize ().x / 10, Window->getSize ().y / 10));
	rectangle2.setSize (sf::Vector2f (Window->getSize ().x / 10, Window->getSize ().y / 10));
	rectangle1.setFillColor(sf::Color::Green);
	rectangle2.setFillColor (sf::Color::Red);
	rectangle1.setPosition (0, 0);
	rectangle2.setPosition (Window->getSize ().x - rectangle2.getSize ().x,
							Window->getSize ().y - rectangle2.getSize ().y);
		
	font.loadFromFile ("arial.ttf");
}

void RunGame ()
{
	std::list<Shootable> user_defence;
	std::list<Killable> enemies;
	unsigned int enemies_number = 0;

	sf::Texture texture_bullet;
	texture_bullet.loadFromFile ("Bullet.png");
	sf::Texture texture_tank;
	texture_tank.loadFromFile ("Tank.png");
	sf::Texture texture_cannon;
	texture_cannon.loadFromFile ("Cannon.png");
	sf::Texture texture_heart;
	texture_heart.loadFromFile ("Heart.png");
	sf::Texture texture_coin;
	texture_coin.loadFromFile ("Coin.png");

	sf::Sprite sprite_bullet;
	sprite_bullet.setTexture (texture_bullet);
	sf::Sprite sprite_tank;
	sprite_tank.setTexture (texture_tank);
	sf::Sprite sprite_cannon;
	sprite_cannon.setTexture (texture_cannon);
	sf::Sprite sprite_heart;
	sprite_heart.setTexture (texture_heart);
	sf::Sprite sprite_coin;
	sprite_coin.setTexture (texture_coin);

		
	std::list<Object *> objects;
	
	sf::Texture background_texture;
	background_texture.loadFromFile ("WhiteBackground.png", sf::IntRect (0, 0, 100, 100));
	background_texture.setRepeated (true);

	sf::Sprite background_sprite;
	background_sprite.setTexture (background_texture);
	background_sprite.setTextureRect (sf::IntRect (0, 0, Window->getSize ().x, Window->getSize ().y));
	
    sprite_heart.setPosition (2, 2);
    sprite_coin.setPosition (2, sprite_heart.getLocalBounds ().height + 5);


	sf::Clock clock;
	sf::Clock enemies_clock;
	sf::Clock game_clock;


	while (Window->isOpen ())
	{
		float time = clock.restart ().asSeconds ();
		sf::Event event;

		if (hp <= 0)
			break;

		while (Window->pollEvent (event))
		{
			if (event.type == sf::Event::Closed)
				Window->close ();
			
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
				{
					Pause (Window);
					clock.restart ();
					enemies_clock.restart ();
				}
			}
			
			if (event.type == sf::Event::MouseButtonReleased)
			{
				if (event.mouseButton.button == sf::Mouse::Right)
				{
					if (money >= MONEY_PER_CANNON)
					{
						Shootable b ({(float) event.mouseButton.x, (float) event.mouseButton.y}, 0, nullptr, sprite_cannon);
						user_defence.push_back (b);
						objects.push_back (&user_defence.back ());

						money -= MONEY_PER_CANNON;
					}
				}
			}
		}

		if (enemies.size () < enemies_number)
		{
			money += MONEY_PER_ENEMY * abs (enemies_number - enemies.size ());
			enemies_number = enemies.size ();
		}

		if (enemies_clock.getElapsedTime ().asSeconds () > 2.0)
		{
			Killable b;
		    b = GenerateRandomEnemy (sprite_tank, game_clock.getElapsedTime ());
			enemies.push_back (b);
			objects.push_back (&enemies.back ());
			enemies_number++;
			enemies_clock.restart ();
		}
        
		CheckEnemies (enemies);

		RemoveDeadObjects (objects);
		RemoveDeadEnemies (enemies, user_defence);
	
		Collide (objects);

		Act (objects, time);

		Draw (objects, background_sprite, sprite_heart, sprite_coin);	
	}
}

void Draw (std::list<Object *> objects, sf::Sprite background, sf::Sprite sprite_hp, sf::Sprite sprite_money)
{
	Window->clear ();

	Window->draw (background);


	Window->draw (rectangle1);
	Window->draw (rectangle2);
	
	for (Object *o : objects)
	{
		o->Draw ();
	}
	
	sf::FloatRect hp_size = sprite_hp.getLocalBounds ();
	sf::FloatRect money_size = sprite_money.getLocalBounds ();

	sf::Text text_hp, text_money;
	text_hp.setFont (font);
	text_money.setFont (font);
	text_hp.setString (std::to_string (hp));
	text_money.setString (std::to_string (money));
	text_hp.setCharacterSize (std::min (hp_size.height, money_size.height));
	text_money.setCharacterSize (std::min (hp_size.height, money_size.height));
	text_hp.setFillColor (sf::Color::Blue);
	text_money.setFillColor (sf::Color::Blue);
	text_hp.setStyle (sf::Text::Bold);
	text_money.setStyle (sf::Text::Bold);

	text_hp.setPosition (sprite_hp.getPosition ().x + sprite_hp.getLocalBounds ().width + 5, sprite_hp.getPosition ().y);
	text_money.setPosition (sprite_money.getPosition ().x + sprite_money.getLocalBounds ().width + 5, sprite_money.getPosition ().y);
	
	Window->draw (sprite_hp);
	Window->draw (sprite_money);
	Window->draw (text_hp);
	Window->draw (text_money);

	Window->display ();
}

void Act (std::list<Object *>& objects, float time)
{
	Object *new_object = nullptr;
	std::list<Object *> to_be_added;
	for (Object *o : objects)
	{
		if ((new_object = o->Act (time, objects)))
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
			to_be_deleted.push_back (o);
	}

	for (Object *o : to_be_deleted)
		objects.remove (o);
}

void RemoveDeadEnemies (std::list<Killable>& enemies, std::list<Shootable>& defence)
{
	while (1)
	{
		auto it = enemies.begin ();
		for (Killable& k : enemies)
		{
			if (!k.IsAlive ())
			{
				for (Shootable& s : defence)
				{
					if (s.target_ == &k)
					{
						s.target_ = nullptr;
					}
				}
				enemies.erase (it);
				break;
			}
			it++;
		}
		if (it == enemies.end ())
			break;
	}
}

void CheckEnemies (std::list<Killable>& enemies)
{
	for (Killable& k : enemies)
	{
        if (sf::IntRect (	rectangle2.getPosition ().x,
							rectangle2.getPosition ().y,
							rectangle2.getSize ().x,
							rectangle2.getSize ().y	).contains (k.pos_.x, k.pos_.y))
		{
			hp--;
			k.hp_ = 0;
		}
	}
}

Killable GenerateRandomEnemy (sf::Sprite enemy_sprite, sf::Time game_time)
{
	struct timeval t;
	gettimeofday (&t, nullptr);
	srand ((unsigned int) (t.tv_sec * t.tv_usec));
	int rand1 = rand ();
	int rand2 = rand ();
	bool minus1 = rand () % 2;
	bool minus2 = rand () % 2;
	
	Killable b (	{rectangle1.getSize ().x / 2, rectangle1.getSize ().y / 2},
					{	(float) ((minus1) ? (rand1 % 60) : (-rand1 % 60)),
						(float) ((minus2) ? (rand2 % 60) : (-rand2 % 60))},
					50, 0, 0,
					10 + 10 * (int) pow (1 + game_time.asSeconds (), 0.5),
					enemy_sprite);

	return b;
}
