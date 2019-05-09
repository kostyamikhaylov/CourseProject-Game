#include <iostream>
#include <list>
#include <cmath>

#include <SFML/Graphics.hpp>

extern sf::RenderWindow *Window;

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
		Object (sf::Vector2f pos, sf::Vector2f v, float m, float friction, sf::Sprite sprite);

		void Draw (sf::RenderWindow *win = Window) const;
		sf::Vector2f GetNewPosition (float dt) const;
		sf::Vector2f GetNewSpeed (float dt) const;
		virtual void Move (float dt, sf::RenderWindow *win = Window);
		void Collide (Object *obstacle);
		virtual bool IsAlive ()
		{
			return true;
		}
		virtual ~Object () {};
};

class Killable: public Object
{
	public:
		int hp_;

		Killable ();
		Killable (sf::Vector2f pos, sf::Vector2f v, float m, float friction, int hp, sf::Sprite sprite);

		void Move (float dt, sf::RenderWindow *win = Window);
		void Collide (Object *obstacle);
		bool IsAlive ()
		{
			return (hp_ > 0);
		}
		~Killable () {};
};

