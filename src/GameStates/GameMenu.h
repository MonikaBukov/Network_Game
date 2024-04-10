//
// Created by monik on 23/10/2023.
//

#ifndef SFMLGAME_GAMEMENU_H
#define SFMLGAME_GAMEMENU_H
#include "../GameObjects/UI/ChatBoxUI.h"
#include "../GameObjects/UI/InputFieldUI.h"
#include "GameState.h"
#include "StateHandler.h"
#include "GameLobby.h"
#include <memory>

class GameMenu: public GameState
{
 public:
  GameMenu(sf::RenderWindow& window,Network* network, StateHandler& handler);
  bool init()override;
  void update(float dt)override;
  void render() override;
  void mouseClicked(sf::Event event) override;
  void keyPressed(sf::Event event) override;
  void textEntered(sf::Event event) override;
  void mouseWheelScrolled(sf::Event event) override;
  void mouseMoved(sf::Event event) override;
  void createUserNameInput();

 private:
  Network* network;
  std::unique_ptr<InputFieldUI> userNameInput;
  std::unique_ptr<InputFieldUI> ipInput;
  std::unique_ptr<ButtonUI> hostButton;
  std::unique_ptr<ButtonUI> joinButton;
  sf::Text textInputTittle;
  sf::Text textInputIP;
  std::unique_ptr<CustomText> cantJoinText;
  sf::Font font;
  StateHandler&  stateHandler;
 // sf::SoundBuffer clickBuffer;
  //sf::Sound clickSound;


};


#endif // SFMLGAME_GAMEMENU_H
