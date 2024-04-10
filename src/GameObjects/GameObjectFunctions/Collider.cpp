//
// Created by m2-bukovics on 25/10/2023.
//

#include "Collider.h"
#include <iostream>
Collider::Collider(sf::Sprite& body): body(body)
{
}
Collider::~Collider() {}


void Collider::move(float dx, float dy) const
{
  body.move(dx, dy);
}

sf::Vector2f Collider::getPosition() const
{
  return body.getPosition();
}

  sf::Vector2f Collider::getHalfSize() const
{
  return { body.getGlobalBounds().width / 2.0f, body.getGlobalBounds().height / 2.0f };
}
bool Collider::checkCollision(const Collider& other, sf::Vector2f& direction)
{
  sf::Vector2f otherPosition = other.getPosition();
  sf::Vector2f otherHalfSize = other.getHalfSize() ;
  sf::Vector2f thisPosition  = getPosition();
  sf::Vector2f thisHalfSize  = getHalfSize();

  float delta_x = otherPosition.x  - thisPosition.x;
  float delta_y = otherPosition.y  - thisPosition.y;

  float intersect_x = abs(delta_x) - (otherHalfSize.x  + thisHalfSize.x)/2;
  float intersect_y = abs(delta_y) - (otherHalfSize.y  + thisHalfSize.y)/2;

  if (intersect_x <= 0.0f && intersect_y <= 0.0f)
  {
    if (intersect_x >= intersect_y)
    {
      if(delta_x > 0.0f)
      {

        other.move(-intersect_x, 0.0f);

        direction.x = 1.0f;
        direction.y = 0;
      }
      else
      {

        other.move(intersect_x , 0.0f);

        direction.x = -1.0f;
        direction.y = 0.0f;
      }
    }
    else
    {
      if(delta_y > 0.0f)
      {
        other.move(0.0f,-intersect_y);

        direction.x = 0.0f;
        direction.y = 1.0;
      }
      else
      {
        other.move(0.0f,intersect_y);

        direction.x = 0.0f;
        direction.y = -1.0;
      }
    }
    return true;
  }
  else
  {
    return false;
  }
}
