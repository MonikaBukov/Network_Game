//
// Created by monik on 29/11/2023.
//

#ifndef SFMLGAME_BACKGROUNDIMAGE_H
#define SFMLGAME_BACKGROUNDIMAGE_H

#include "UIElement.h"
class BackgroundImage: public UIElement
{
 public:
  BackgroundImage(const sf::String& imgPath);
  virtual ~BackgroundImage();
  void draw();

 private:
  sf::Sprite bckgSprite;
  sf::Texture bckgImg;
  std::string imgPath;

};

#endif // SFMLGAME_BACKGROUNDIMAGE_H
