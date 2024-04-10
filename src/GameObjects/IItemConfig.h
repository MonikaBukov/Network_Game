//
// Created by monik on 08/12/2023.
//

#ifndef SFMLGAME_IITEMCONFIG_H
#define SFMLGAME_IITEMCONFIG_H

class IItemConfig
{
 public:
  virtual void increaseSpeed(int speed) =0;
  virtual void increaseRadius(float radius) = 0;
};

#endif // SFMLGAME_IITEMCONFIG_H
