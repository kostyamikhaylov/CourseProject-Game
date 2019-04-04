#include <SFML/Graphics.hpp>
#include <iostream>


bool ButtonPressedInsideRectangle (sf::Event::MouseButtonEvent click, sf::RectangleShape figure);

int main ()
{
	int cursorInsideScreen = 0;
	int count = 0;
	sf::Vector2f lu, rd;

	sf::RenderWindow window (sf::VideoMode (800, 500), "Simple Program");
	sf::RectangleShape rec;

	while (window.isOpen ())
	{
		sf::Event event;

		while (window.pollEvent (event))
		{
			switch (event.type)
			{
				case sf::Event::Closed:
					window.close ();
					break;

				case sf::Event::MouseEntered:
					cursorInsideScreen = 1;
					break;
				
				case sf::Event::MouseLeft:
					cursorInsideScreen = 0;
					break;
				
				case sf::Event::TextEntered:
					if (event.text.unicode == 'q')
						window.close ();
					break;
				
				case sf::Event::MouseButtonReleased:
					if (!cursorInsideScreen)
						break;

					if (event.mouseButton.button == sf::Mouse::Right)
					{
						if (count % 2 == 0)
						{
							lu.x = event.mouseButton.x;
							lu.y = event.mouseButton.y;

							count++;
						}
						else
						{
							rd.x = event.mouseButton.x;
							rd.y = event.mouseButton.y;

							rec.setSize ({rd.x - lu.x, rd.y - lu.y});
							rec.setPosition (lu.x, lu.y);
							rec.setFillColor (sf::Color::Green);

							count++;
						}
					}
					else if (event.mouseButton.button == sf::Mouse::Left)
					{
						if (count < 2)
							break;

						if (ButtonPressedInsideRectangle (event.mouseButton, rec))
							window.close ();
					}
					break;
			}

			window.clear ();
			window.draw (rec);
			window.display ();
		}
	}


	return 0;
}

bool ButtonPressedInsideRectangle (sf::Event::MouseButtonEvent click, sf::RectangleShape figure)
{
	sf::Vector2f size = figure.getSize ();
	sf::Vector2f rec = figure.getPosition ();

/*
	std::cout << "Position: x = " << rec.x << ", y = " << rec.y << '\n';
	std::cout << "Size: " << size.x << "x" << size.y << '\n';
	std::cout << "Mouse: x = " << click.x << ", y = " << click.y << '\n';
*/

	if (
		(
		(size.x >= 0) ?
		(click.x >= rec.x && click.x <= rec.x + size.x) :
		(click.x <= rec.x && click.x >= rec.x + size.x)
		)
		&&
		(
		(size.y >= 0) ?
		(click.y >= rec.y && click.y <= rec.y + size.y) :
		(click.y <= rec.y && click.y >= rec.y + size.y)
		)
	   )
		return 1;

	return 0;
}

