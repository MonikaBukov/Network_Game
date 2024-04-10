//
// Created by m2-bukovics on 25/10/2023.
//

#ifndef SFMLGAME_CHARACTER_H
#define SFMLGAME_CHARACTER_H

#include "GameObject.h"

class Character : public GameObject
{
 public:
  int getHealth() const;
  void setHealth(int health);
  void handleAnim(float dt);
  void changePosition(sf::Vector2f charPos);
  enum  MovementDirection
  {
    UP = 1,
    DOWN = 2,
    RIGHT = 3,
    LEFT = 4,
    OTHER = 5,
  }movementDirection;

  void innitCharacter(int id, const std::string& characterText, sf::Vector2f spawn_position, MovementDirection direction1);
  float getSpeed() const;
  void draw();
  int getId() const;
  MovementDirection getDirection() const;
  void updateInterpolation(float dt);
  sf::FloatRect getBoundsWithOffset();
  sf::Vector2f getPositionWithOffset();

 private:
  Animation characterAnim;
  sf::Texture characterTexture;
  int health;
  float speed = 100.0;

 public:
  void setSpeed(float speed);

 private:
  int ID;
  sf::Vector2f currentPosition;
  sf::Vector2f targetPosition;
  float interpolationFactor;
  float interpolationSpeed = 100.0f;
  bool dead = false;
  bool texture_changed = false;

 public:
  bool isTextureChanged() const;
  void setTextureChanged(bool textureChanged);

 public:
  bool isDead() const;
  void setDead(bool dead);
};



#endif // SFMLGAME_CHARACTER_H
