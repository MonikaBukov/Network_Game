
#include "Game.h"

#include <iostream>

Game::Game(sf::RenderWindow& game_window)
  : window(game_window)
{
  srand(time(NULL));
  stateHandler.setState(new GameMenu(window, &network, stateHandler));
}

Game::~Game()
{
}

void Game::update(float dt)
{
  stateHandler.update(dt);
  if (network.getClient()->isStateChanged())
  {
    int newState = network.getClient()->getNewState();

      switch (newState)
      {
        case 1: // StateType::Lobby
          stateHandler.setState(new GameLobby(window, &network, stateHandler));
          network.getClient()->setStateChanged(false);
          break;
        case 2: // StateType::InGame
          stateHandler.setState(new GamePlay(window, &network, stateHandler));
          network.getClient()->setStateChanged(false);
          break;
        default:
          std::cerr << "Received an unknown state: " << newState << std::endl;
          // Handle unexpected state
          break;
      }
  }
}
void Game::render()
{
  stateHandler.render();
}

void Game::mouseClicked(sf::Event event)
{
  sf::Vector2i click = sf::Mouse::getPosition(window);
  stateHandler.mouseClicked(event);
}

void Game::keyPressed(sf::Event event)
{
  stateHandler.keyPressed(event);
}

void Game::textEntered(sf::Event event) {
  stateHandler.textEntered(event);
}

void Game::mouseWheelScrolled(sf::Event event) {
  stateHandler.onWheelScrolled(event);
}

void Game::mouseMoved(sf::Event event) {
  stateHandler.mouseMoved(event);
}
void Game::windowClosed(sf::Event event)
{
  Disconnection msg;
  msg.userName = network.getClient()->getUserName();
  network.getClient()->sendDisconnectionRequest(msg);
  stateHandler.gameClosed(event);
  window.close();
}
