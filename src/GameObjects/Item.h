//
// Created by monik on 06/12/2023.
//

#ifndef SFMLGAME_ITEM_H
#define SFMLGAME_ITEM_H

#include "GameObject.h"
#include "IItemConfig.h"
class Item: public GameObject
{
 public:;
  Item();
  enum Type
  {
    SPEED=1,
    RADIUS=2
  }type;
 private:
  int ID;
  std::unique_ptr<sf::Sprite> itemSprite;
  bool enabled = true;

 public:
  bool isEnabled() const;
  void setEnabled(bool enabled);
  int getId() const;
  void setId(int id);
  void draw();
  std::unique_ptr<sf::Sprite>& GetSpite();
  void collect(IItemConfig* collector);



};

#endif // SFMLGAME_ITEM_H
