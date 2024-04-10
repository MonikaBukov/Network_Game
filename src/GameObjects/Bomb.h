//
// Created by monik on 05/12/2023.
//

#ifndef SFMLGAME_BOMB_H
#define SFMLGAME_BOMB_H

#include "GameObject.h"
class Bomb : public GameObject
{
 public:
  void innitBomb(const std::string& characterText);
  void spawnBomb(float dt);

 private:
  sf::Texture bombTexture;
  bool isSpawned = false;
  float detonationTime = 0.1 * 22.0;
  float current_duration = 0.0f;
  float radius = 0.4;
  sf::Vector2f  spawnPos;
  bool exploding = false;

 public:
  bool isExploding() const;

 public:
  const sf::Vector2f& getSpawnPos() const;
  void setSpawnPos(const sf::Vector2f& spawnPos);

 public:
  float getRadius() const;
  void setRadius(float radius);

 public:
  bool getIsSpawned() const;
  void setSpawned(bool spawned);
  void draw();
};

#endif // SFMLGAME_BOMB_H
