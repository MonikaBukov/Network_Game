//
// Created by m2-bukovics on 25/10/2023.
//

#include "Player.h"



void Player::changeDirection(const float& dt)
{
  resetVellocity();
  if(window.hasFocus() && !playerCharacter->isDead())
  {

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
      velocity.x -= playerCharacter->getSpeed();
      playerCharacter->movementDirection = Character::LEFT;
    }

    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
      velocity.x += playerCharacter->getSpeed();
      playerCharacter->movementDirection = Character::RIGHT;
    }

    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
      velocity.y -= playerCharacter->getSpeed();
      playerCharacter->movementDirection = Character::UP;
    }

    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
      velocity.y += playerCharacter->getSpeed();
      playerCharacter->movementDirection = Character::DOWN;
    }
  }
}
void Player::move(const float& dt)
{
  if(!playerCharacter->isDead())
  {
    prevPos = getPlayerCharacter()->GetObjSprite()->getPosition();
    playerCharacter->GetObjSprite()->move(velocity * dt);
  }
}
/*
void Player::onCollision(sf::Vector2f direction)
{
  prevPos = GetObjSprite()->getPosition();
  if (direction.x < 0.0f && velocity.x > 0.0f)
  {
    velocity.x = 0.0f;
  }
  if (direction.x > 0.0f && velocity.x < 0.0f)
  {
    velocity.x = 0.0f;
  }

  if (direction.y < 0.0f && velocity.y > 0.0f)
  {
    velocity.y = 0.0f;
  }
 if (direction.y > 0.0f && velocity.y < 0.0f)
  {
    velocity.y = 0.0f;
  }
}*/
void Player::resetVellocity()
{
  velocity.x = 0.0f;
  velocity.y = 0.0f;
}
void Player::assignCharacter(std::unique_ptr<Character> character) {
  playerCharacter = std::move(character);}
const std::unique_ptr<Character>& Player::getPlayerCharacter() const
{
  return playerCharacter;
}
const sf::Vector2f& Player::getPrevPos() const
{
  return prevPos;
}
bool Player::isBombDeployed() const
{
  return bombDeployed;
}
void Player::setBombDeployed(bool bombDeployed)
{
  Player::bombDeployed = bombDeployed;
}
