#ifndef MENUS_CPP
#define MENUS_CPP

#include "Menus.h"

void StartMenu (sf::RenderWindow *win)
{
    sf::Texture start_texture, exit_texture, background_texture;
    start_texture.loadFromFile("NewGame.png");
    exit_texture.loadFromFile("Exit.png");
	background_texture.loadFromFile ("WhiteBackground.png", sf::IntRect (0, 0, 100, 100));
	background_texture.setRepeated (true);
    
	sf::Sprite 	start_sprite (start_texture),
				exit_sprite (exit_texture),
				background_sprite (background_texture);
	
	background_sprite.setTextureRect (sf::IntRect (0, 0, win->getSize ().x, win->getSize ().y));

    bool still_here = true;
    int button_pressed_number = 0;


	sf::FloatRect start_size = start_sprite.getLocalBounds ();
	sf::FloatRect exit_size = exit_sprite.getLocalBounds ();
    start_sprite.setOrigin (start_size.width / 2, start_size.height / 2);
    exit_sprite.setOrigin (exit_size.width / 2, exit_size.height / 2);
    start_sprite.setPosition (win->getSize ().x * 0.5, win->getSize ().y * 1/3);
    exit_sprite.setPosition (win->getSize ().x * 0.5, win->getSize ().y * 2/3);
    background_sprite.setPosition (0, 0);

    while (still_here && win->isOpen())
    {
        sf::Event event;
        while (win->pollEvent (event))
        {
            if (event.type == sf::Event::Closed)
                win->close ();
        }

        start_sprite.setColor (sf::Color::White);
        exit_sprite.setColor (sf::Color::White);
        button_pressed_number = 0;
        
        if (sf::IntRect (	start_sprite.getPosition ().x - start_size.width / 2,
							start_sprite.getPosition ().y - start_size.height / 2,
							start_size.width,
							start_size.height	).contains(sf::Mouse::getPosition (*win)))
        {
            start_sprite.setColor (sf::Color::Magenta);
        	button_pressed_number = 1;
        }
        if (sf::IntRect (	exit_sprite.getPosition ().x - exit_size.width / 2,
							exit_sprite.getPosition ().y - exit_size.height / 2,
							exit_size.width,
							exit_size.height	).contains(sf::Mouse::getPosition (*win)))
        {
            exit_sprite.setColor (sf::Color::Magenta);
        	button_pressed_number = 2;
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            if (button_pressed_number == 1)
				still_here = false;
            if (button_pressed_number == 2)
            {
                win->close();
                still_here = false;
				break;
            }
        }

		win->clear ();

        win->draw (background_sprite);
        win->draw (start_sprite);
        win->draw (exit_sprite);

        win->display();
    }
}

void Pause (sf::RenderWindow *win)
{
    sf::Texture continue_texture, restart_texture, exit_texture, background_texture;
    continue_texture.loadFromFile("Continue.png");
    restart_texture.loadFromFile("Restart.png");
    exit_texture.loadFromFile("Exit.png");
	background_texture.loadFromFile ("WhiteBackground.png", sf::IntRect (0, 0, 100, 100));
	background_texture.setRepeated (true);
    
	sf::Sprite 	continue_sprite (continue_texture),
				restart_sprite (restart_texture),
				exit_sprite (exit_texture),
				background_sprite (background_texture);
	
	background_sprite.setTextureRect (sf::IntRect (0, 0, win->getSize ().x, win->getSize ().y));

    bool still_here = true;
    int button_pressed_number = 0;


	sf::FloatRect continue_size = continue_sprite.getLocalBounds ();
	sf::FloatRect restart_size = restart_sprite.getLocalBounds ();
	sf::FloatRect exit_size = exit_sprite.getLocalBounds ();
    continue_sprite.setOrigin (continue_size.width / 2, continue_size.height / 2);
    restart_sprite.setOrigin (restart_size.width / 2, restart_size.height / 2);
    exit_sprite.setOrigin (exit_size.width / 2, exit_size.height / 2);
    continue_sprite.setPosition (win->getSize ().x * 0.5, win->getSize ().y * 1/4);
    restart_sprite.setPosition (win->getSize ().x * 0.5, win->getSize ().y * 2/4);
    exit_sprite.setPosition (win->getSize ().x * 0.5, win->getSize ().y * 3/4);
    background_sprite.setPosition (0, 0);

    while (still_here && win->isOpen())
    {
        sf::Event event;
        while (win->pollEvent (event))
        {
            if (event.type == sf::Event::Closed)
                win->close ();
        }

        continue_sprite.setColor (sf::Color::White);
        restart_sprite.setColor (sf::Color::White);
        exit_sprite.setColor (sf::Color::White);
        button_pressed_number = 0;

        if (sf::IntRect (	continue_sprite.getPosition ().x - continue_size.width / 2,
							continue_sprite.getPosition ().y - continue_size.height / 2,
							continue_size.width,
							continue_size.height	).contains(sf::Mouse::getPosition (*win)))
        {
            continue_sprite.setColor (sf::Color::Magenta);
        	button_pressed_number = 1;
        }
        if (sf::IntRect (	restart_sprite.getPosition ().x - restart_size.width / 2,
							restart_sprite.getPosition ().y - restart_size.height / 2,
							restart_size.width,
							restart_size.height	).contains(sf::Mouse::getPosition (*win)))
        {
            restart_sprite.setColor (sf::Color::Magenta);
        	button_pressed_number = 2;
        }
        if (sf::IntRect (	exit_sprite.getPosition ().x - exit_size.width / 2,
							exit_sprite.getPosition ().y - exit_size.height / 2,
							exit_size.width,
							exit_size.height	).contains(sf::Mouse::getPosition (*win)))
        {
            exit_sprite.setColor (sf::Color::Magenta);
        	button_pressed_number = 3;
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            if (button_pressed_number == 1)
				still_here = false;
            if (button_pressed_number == 2)
			{
				longjmp (env, 0);
				still_here = false;
			}
            if (button_pressed_number == 3)
            {
                win->close();
                still_here = false;
				break;
            }
        }

		win->clear ();

        win->draw (background_sprite);
        win->draw (continue_sprite);
        win->draw (restart_sprite);
        win->draw (exit_sprite);

        win->display();
    }
}

void GameOver (sf::RenderWindow *win)
{
    sf::Texture restart_texture, exit_texture, background_texture;
    restart_texture.loadFromFile("Restart.png");
    exit_texture.loadFromFile("Exit.png");
	background_texture.loadFromFile ("WhiteBackground.png", sf::IntRect (0, 0, 100, 100));
	background_texture.setRepeated (true);
    
	sf::Sprite 	restart_sprite (restart_texture),
				exit_sprite (exit_texture),
				background_sprite (background_texture);
	
	background_sprite.setTextureRect (sf::IntRect (0, 0, win->getSize ().x, win->getSize ().y));

    bool still_here = true;
    int button_pressed_number = 0;


	sf::FloatRect restart_size = restart_sprite.getLocalBounds ();
	sf::FloatRect exit_size = exit_sprite.getLocalBounds ();
    restart_sprite.setOrigin (restart_size.width / 2, restart_size.height / 2);
    exit_sprite.setOrigin (exit_size.width / 2, exit_size.height / 2);
    restart_sprite.setPosition (win->getSize ().x * 0.5, win->getSize ().y * 1/3);
    exit_sprite.setPosition (win->getSize ().x * 0.5, win->getSize ().y * 2/3);
    background_sprite.setPosition (0, 0);

    while (still_here && win->isOpen())
    {
        sf::Event event;
        while (win->pollEvent (event))
        {
            if (event.type == sf::Event::Closed)
                win->close ();
        }

        restart_sprite.setColor (sf::Color::White);
        exit_sprite.setColor (sf::Color::White);
        button_pressed_number = 0;

        if (sf::IntRect (	restart_sprite.getPosition ().x - restart_size.width / 2,
							restart_sprite.getPosition ().y - restart_size.height / 2,
							restart_size.width,
							restart_size.height	).contains(sf::Mouse::getPosition (*win)))
        {
            restart_sprite.setColor (sf::Color::Magenta);
        	button_pressed_number = 1;
        }
        if (sf::IntRect (	exit_sprite.getPosition ().x - exit_size.width / 2,
							exit_sprite.getPosition ().y - exit_size.height / 2,
							exit_size.width,
							exit_size.height	).contains(sf::Mouse::getPosition (*win)))
        {
            exit_sprite.setColor (sf::Color::Magenta);
        	button_pressed_number = 2;
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            if (button_pressed_number == 1)
			{
				longjmp (env, 0);
				still_here = false;
			}
            if (button_pressed_number == 2)
            {
                win->close();
                still_here = false;
				break;
            }
        }

		win->clear ();

        win->draw (background_sprite);
        win->draw (restart_sprite);
        win->draw (exit_sprite);

        win->display();
    }
}

        
#endif //MENUS_CPP
