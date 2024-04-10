//
// Created by monik on 24/10/2023.
//

#ifndef SFMLGAME_GAMELOBBY_H
#define SFMLGAME_GAMELOBBY_H

#include "../GameObjects/UI/BackgroundImage.h"
#include "../GameObjects/UI/ButtonUI.h"
#include "../GameObjects/UI/ChatBoxUI.h"
#include "../GameObjects/UI/CustomText.h"
#include "GameState.h"
#include "StateHandler.h"

class GameLobby: public GameState
{
 public:
  GameLobby(sf::RenderWindow& window,Network* network, StateHandler& handler);;
  bool init()override;
  void update(float dt)override;
  void render() override;
  void mouseClicked(sf::Event event) override;
  void keyPressed(sf::Event event) override;
  void textEntered(sf::Event event) override;
  void mouseWheelScrolled(sf::Event event) override;
  void mouseMoved(sf::Event event) override;
 void gameClosed(sf::Event event)override;

 private:
  Network* network;
  std::unique_ptr<ChatBoxUI> chatBox;
  std::unique_ptr<CustomText> ipToConnectText;
  std::unique_ptr<CustomText> waitText ;
  std::unique_ptr<CustomText> characterText ;
  std::unique_ptr<BackgroundImage> bckImage;
  sf::Font font;
  std::unique_ptr<ButtonUI> startButton;
  std::unique_ptr<ButtonUI> birdButton;
  std::unique_ptr<ButtonUI> catButton;
  std::unique_ptr<ButtonUI> foxButton;
  std::unique_ptr<ButtonUI> racoonButton;
  std::unique_ptr<ButtonUI> chosenCharacter;
  std::unique_ptr<sf::Texture> bird;
  std::unique_ptr<sf::Texture> cat;
  std::unique_ptr<sf::Texture>fox;
  std::unique_ptr<sf::Texture> rac;
  std::vector<std::unique_ptr<ButtonUI>> characterButtons;
  std::vector<bool> availableCharacters;

  //sf::SoundBuffer buffer;
 // sf::Sound sound;
 // sf::SoundBuffer clickBuffer;
 // sf::Sound clickSound;

  void innitButtons();
  void innitText();
  void updateChosenCharacter();
  void innitSounds();
};

#endif // SFMLGAME_GAMELOBBY_H
