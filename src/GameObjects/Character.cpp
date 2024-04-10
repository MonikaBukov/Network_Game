//
// Created by m2-bukovics on 25/10/2023.
//

#include "Character.h"
int Character::getHealth() const
{
  return health;
}
void Character::setHealth(int health)
{
  Character::health = health;
}
float Character::getSpeed() const
{
  return speed;
}
void Character::handleAnim(float dt)
{
  if (!dead)
  {
    switch (movementDirection)
    {
      case Character::UP:
        animation.Update(8, dt, false);

        GetObjSprite()->setTextureRect(animation.rect);
        break;

      case Character::DOWN:
        animation.Update(1, dt, false);
        GetObjSprite()->setTextureRect(animation.rect);
        break;

      case Character::RIGHT:
        animation.Update(4, dt, false);
        GetObjSprite()->setTextureRect(animation.rect);
        break;

      case Character::LEFT:
        animation.Update(6, dt, false);
        GetObjSprite()->setTextureRect(animation.rect);
        break;

      case Character::OTHER:
        // Handle iddle animation which I dont have
        break;

      default:
        // Handle the default case
        break;
    }
  }
  else
  {
    GetObjSprite()->setTextureRect(sf::IntRect (0.0f,0.0f,GetObjSprite()->getTexture()->getSize().x,GetObjSprite()->getTexture()->getSize().y));
    GetObjSprite()->setScale(0.3,0.3);
  }
}
void Character::innitCharacter(int id, const std::string & characterText, sf::Vector2f spawn_position, MovementDirection direction1)
{
  if (!characterTexture.loadFromFile(characterText))
  {
    std::cerr << "Failed to load texture: " << characterText << std::endl;
    return;
  }
  ID = id;
  GetObjSprite()->setPosition(spawn_position);
  GetObjSprite()->setTexture(characterTexture);
  animation.initAnim(&characterTexture, sf::Vector2u(4,9), 0.3);
  movementDirection = direction1;
  GetObjSprite()->setScale(2.5,2.5);
}

// boundaries changed to simulate more 2.5 view;
sf::FloatRect Character::getBoundsWithOffset()
  {
    sf::FloatRect boundsWithOffset = GetObjSprite()->getGlobalBounds();
    boundsWithOffset.top += 30;
    boundsWithOffset.left += 18;
    boundsWithOffset.height -= 40;
    boundsWithOffset.width -= 50;
    return boundsWithOffset;
  }


void Character::draw()
{
  window.draw(*GetObjSprite());
}
void Character::changePosition(sf::Vector2f charPos)
{
  targetPosition = charPos;
  interpolationFactor = 0.0f;
}
Character::MovementDirection Character::getDirection() const
{
  return movementDirection;
}
int Character::getId() const
{
  return ID;
}

// smooths out character movement in case packet loss
sf::Vector2f lerp(const sf::Vector2f& start, const sf::Vector2f& end, float t)
{
  return (1.0f - t) * start + t * end;
}

void Character::updateInterpolation(float dt)
{
  currentPosition = lerp(currentPosition, targetPosition, interpolationFactor);
  interpolationFactor += interpolationSpeed * dt;
  interpolationFactor = std::min(1.0f, interpolationFactor);
  GetObjSprite()->setPosition(currentPosition);
}

bool Character::isDead() const
{
  return dead;
}
void Character::setDead(bool dead)
{
  Character::dead = dead;
}
bool Character::isTextureChanged() const
{
  return texture_changed;
}
void Character::setTextureChanged(bool textureChanged)
{
  texture_changed = textureChanged;
}
void Character::setSpeed(float speed)
{
  Character::speed = speed;
}
