//
// Created by m2-bukovics on 25/10/2023.
//

#ifndef SFMLGAME_PLAYER_H
#define SFMLGAME_PLAYER_H
#include "Character.h"

class Player : public GameObject
{
 private:
  std::unique_ptr<Character> playerCharacter;

 public:
  const std::unique_ptr<Character>& getPlayerCharacter() const;

 private:
  sf::Vector2f velocity;
  sf::Vector2f prevPos;
  bool bombDeployed;

 public:
  bool isBombDeployed() const;
  void setBombDeployed(bool bombDeployed);

 public:
  const sf::Vector2f& getPrevPos() const;
  //void onCollision(sf::Vector2f direction);
  void changeDirection(const float& dt);
  void assignCharacter(std::unique_ptr<Character> character);
  void resetVellocity();
  void move(const float& dt);
};

#endif // SFMLGAME_PLAYER_H
