#ifndef MENUS_H
#define MENUS_H

#include <iostream>
#include <list>
#include <cmath>
#include <setjmp.h>

#include <SFML/Graphics.hpp>


extern sf::RenderWindow *Window;
extern jmp_buf env;

void StartMenu (sf::RenderWindow *win = Window);
void Pause (sf::RenderWindow *win = Window);
void GameOver (sf::RenderWindow *win = Window);


#endif //MENUS_H
