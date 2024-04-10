//
// Created by monik on 25/10/2023.
//

#ifndef SFMLGAME_INPUTFIELDUI_H
#define SFMLGAME_INPUTFIELDUI_H
#include "UIElement.h"
#include <SFML/Graphics.hpp>
#include <iostream>

class InputFieldUI :public UIElement
{
 public:
  InputFieldUI(sf::RenderWindow& window, sf::Font& font, int fontSize, sf::Color textColor, sf::Color fillColor, sf::Vector2f position, sf::Vector2f size, int limit);
  ~InputFieldUI() = default;
  void handleEvent(sf::Event event);
  void draw();
  float getWidth();
  float getHeight();
  void clearInput();
  const sf::Vector2f& getPos();
  const std::string& getInputText();
  sf::FloatRect GetBounds();

 private:
  sf::RenderWindow& window;
  sf::Font& font;
  int fontSize;
  sf::Color textColor;
  sf::Color fillColor;
  sf::Vector2f position;
  sf::Vector2f size;
  sf::RectangleShape inputBox;
  sf::Text text;
  std::string inputText;
  sf::Vector2f boxPos;
  int limit;
  int posY;
  bool wasWarped = false;
  bool limitationSet = false;
  int prevlim;


};

#endif // SFMLGAME_INPUTFIELDUI_H
