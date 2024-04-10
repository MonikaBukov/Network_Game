//
// Created by monik on 29/11/2023.
//

#include "BackgroundImage.h"
BackgroundImage::BackgroundImage(const sf::String& imgPath) : imgPath(imgPath)
{
  bckgImg.loadFromFile(imgPath);
  bckgSprite.setTexture(bckgImg);
  float targetWidth  = 100;
  float targetHeight = 100;
  bckgSprite.setScale(getPercentage(sf::Vector2f(
    targetWidth / bckgSprite.getLocalBounds().width,
    targetHeight / bckgSprite.getLocalBounds().height)));
}

void BackgroundImage::draw()
{
  if (getIsEnabled())
  {
    window.draw(bckgSprite);
  }
}
BackgroundImage::~BackgroundImage() {}
