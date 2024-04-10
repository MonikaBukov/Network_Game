//
// Created by monik on 28/11/2023.
//

#include "CustomText.h"


CustomText::CustomText(const sf::Font& font, unsigned int characterSize, const sf::Color& fillColor, const std::string& text)
  : sf::Text(), font(font) {

  setFont(font);
  setCharacterSize(characterSize);
  setFillColor(fillColor);
  setString(text);
}
void CustomText::draw()
{
  if (getIsEnabled())
  {
    window.draw(*this);
  }
}
