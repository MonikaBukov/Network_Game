
#ifndef PLATFORMER_GAME_H
#define PLATFORMER_GAME_H

#include <SFML/Graphics.hpp>

#include "Networking/Client.h"
#include "Networking/Server.h"
#include "Networking/Network.h"
#include "GameStates/StateHandler.h"
#include "GameStates/GamePlay.h"
#include "GameStates/GameMenu.h"
#include "GameStates/GameLobby.h"

class Game
{
 public:
  Game(sf::RenderWindow& window);
  ~Game();
  void update(float dt);
  void render();
  void mouseClicked(sf::Event event);
  void keyPressed(sf::Event event);
  void textEntered(sf::Event event);
  void mouseWheelScrolled(sf::Event event);
  void mouseMoved(sf::Event event);
  void windowClosed(sf::Event event);


 private:
  sf::RenderWindow& window;
  StateHandler stateHandler;
  Network network;

};

#endif // PLATFORMER_GAME_H
