//
// Created by monik on 28/11/2023.
//

#ifndef SFMLGAME_CUSTOMTEXT_H
#define SFMLGAME_CUSTOMTEXT_H
#include <SFML/Graphics.hpp>
#include "UIElement.h"
//#pragma once

class CustomText : public sf::Text, public UIElement{
 public:
  CustomText(const sf::Font& font, unsigned int characterSize, const sf::Color& fillColor, const std::string& text);
  void draw();
 private:
  sf::Font font;

};

#endif // SFMLGAME_CUSTOMTEXT_H
