//
// Created by m2-bukovics on 25/10/2023.
//

#include "UIElement.h"

sf::Vector2f UIElement::getPercentage(const sf::Vector2f& newPosition) const {
  sf::Vector2f percentage;

  float xPercentage = (windowSize.x / 100.0f) * newPosition.x;
  float yPercentage = (windowSize.y / 100.0f) * newPosition.y;

  percentage.x = xPercentage;
  percentage.y = yPercentage;

  return percentage;
}
std::string UIElement::TextWarp(const std::string& text, int firstEmptySpace, int limit,[[maybe_unused]] int& y,[[maybe_unused]] int & space)
{
  int emptySpaceToIgnore = firstEmptySpace;
  std::string t1;
  std::string t2;
  int lastEmptySpace;
  lastEmptySpace = text.find_last_of(" ", limit);
  if (lastEmptySpace != emptySpaceToIgnore && lastEmptySpace != -1)
  {
    t1 = text.substr(0, lastEmptySpace);
    t2 = text.substr(lastEmptySpace);
    y -= space;
  }
  else {
    t1 = text.substr(0, limit);
    t2 = text.substr(limit);
    y -= space;
  }
  return t1 + "\n" + t2;
}

int UIElement::GetCharacterLimit(const sf::Text& tempText, sf::FloatRect boxRect, float offset)
{
  int characterLimit;
  for (size_t i = 0; i < tempText.getString().getSize(); i++)
  {
    sf::Vector2f charPos = tempText.findCharacterPos(i);
    if (charPos.x > boxRect.left + boxRect.width - offset)
    {
      characterLimit = i - 1;
      return characterLimit;
    }
  }
  return characterLimit =  1000;
}
bool UIElement::isInsideRect(sf::FloatRect rect1, sf::FloatRect rect2)
{
  return (
    rect1.intersects(rect2)
    );
}

