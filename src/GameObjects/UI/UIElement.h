//
// Created by m2-bukovics on 25/10/2023.
//

#ifndef SFMLGAME_UIELEMENT_H
#define SFMLGAME_UIELEMENT_H

#include <SFML/Graphics.hpp>
#include "../GameObject.h"
#include "../../GameWindow.h"
#include "CustomColours.h"


class UIElement: public GameObject
{
 public:

  sf::Vector2f getPercentage(const sf::Vector2f& newPosition) const;
  std::string TextWarp(const std::string& text, int firstEmptySpace, int limit, int& y, int& space);

  bool getIsEnabled() const { return isEnabled; }
  void setIsEnabled(bool isEnabled) { this->isEnabled = isEnabled; }
  int GetCharacterLimit(const sf::Text& tempText, sf::FloatRect boxRect, float offset);
  bool isInsideRect(sf::FloatRect rect1, sf::FloatRect rect2);

 private:
  // Member variables to store the state of the UI element
  bool isEnabled = true;


 public:

};

#endif // SFMLGAME_UIELEMENT_H
