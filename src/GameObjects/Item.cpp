//
// Created by monik on 06/12/2023.
//

#include "Item.h"

Item::Item()
{
  itemSprite = std::make_unique<sf::Sprite>();
}
void Item::collect(IItemConfig* collector)
{
  switch (type)
  {
    case Type::SPEED:
    {
      collector->increaseSpeed(20);
      break;
    }
    case Type::RADIUS:
    {
      collector->increaseRadius(1.1f);
      break;
    }
  }
}
int Item::getId() const
{
  return ID;
}
void Item::setId(int id)
{
  ID = id;
}
void Item::draw()
{
    window.draw(*GetObjSprite());
}
std::unique_ptr<sf::Sprite>& Item::GetSpite()
{
  return itemSprite;
}
bool Item::isEnabled() const
{
  return enabled;
}
void Item::setEnabled(bool enabled)
{
  Item::enabled = enabled;
}
