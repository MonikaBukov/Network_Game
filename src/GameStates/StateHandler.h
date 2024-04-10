//
// Created by monik on 23/10/2023.
//

#ifndef SFMLGAME_STATEHANDLER_H
#define SFMLGAME_STATEHANDLER_H

#include "GameState.h"

class StateHandler
{
 public:
  StateHandler() : currentState(nullptr) {}
  void setState(GameState* newState);
  void init();
  void update(float dt);
  void render();
  void mouseClicked(sf::Event event);
  void keyPressed(sf::Event event);
  void textEntered(sf::Event event);
  void onWheelScrolled(sf::Event event);
  void mouseMoved(sf::Event event);
  void gameClosed(sf::Event event);

 private:
  GameState* currentState;
};


#endif // SFMLGAME_STATEHANDLER_H
