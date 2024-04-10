//
// Created by monik on 23/10/2023.
//

#ifndef SFMLGAME_GAMEWINDOW_H
#define SFMLGAME_GAMEWINDOW_H

#include <SFML/Graphics.hpp>

class GameWindow
{
 public:
  static sf::RenderWindow& getWindow() {
    static sf::RenderWindow window(sf::VideoMode(1360, 768), "BomberGame", sf::Style::Default);
    return window;
  }
};



#endif // SFMLGAME_GAMEWINDOW_H
