//
// Created by m2-bukovics on 25/10/2023.
//

#include "GameObject.h"

GameObject::GameObject()
{
  objectSprite = std::make_unique<sf::Sprite>();
}
void GameObject::drawObject()
{
  if (objectSprite) {
    window.draw(*objectSprite);
  } else {
    std::cerr << "Null pointer encountered when drawing objectSprite." << std::endl;
  }
}
Collider GameObject::getCollider() const
{
  return Collider(*objectSprite);
}
const std::unique_ptr<sf::Sprite>& GameObject::GetObjSprite() const
{
  return objectSprite;
}
