//
// Created by monik on 23/10/2023.
//

#ifndef SFMLGAME_GAMESTATE_H
#define SFMLGAME_GAMESTATE_H
#include <SFML/Graphics.hpp>
#include "../Networking/Client.h"
#include "../Networking/Network.h"
#include <SFML/Audio.hpp>

class GameState
{
 public:
  GameState(sf::RenderWindow& window) : window(window) { }
  virtual ~GameState() = default;
  virtual bool init() = 0;
  virtual void update(float dt){};
  virtual void render() = 0;
  virtual void mouseClicked(sf::Event event) = 0;
  virtual void keyPressed(sf::Event event) = 0;
  virtual void textEntered(sf::Event event)=0;
  virtual void mouseWheelScrolled(sf::Event event)=0;
  virtual void mouseMoved(sf::Event event)=0;
  virtual void gameClosed(sf::Event event){};

 protected:
  sf::RenderWindow& window;
};

#endif // SFMLGAME_GAMESTATE_H
