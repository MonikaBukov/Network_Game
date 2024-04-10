//
// Created by monik on 05/12/2023.
//

#include "Bomb.h"
void Bomb::spawnBomb( float dt)
{
  if (0.0f >= current_duration && isSpawned)
  {
    GetObjSprite()->setPosition(spawnPos);
    GetObjSprite()->setScale(radius,radius);
    animation.resetAnim();

  }
    if (current_duration <= detonationTime  && isSpawned) {
    animation.Update(0, dt, false);
    GetObjSprite()->setTextureRect(animation.rect);
    current_duration += dt;
    if (current_duration > detonationTime *0.6)
    {
      exploding = true;
    }
  }
  else {
    GetObjSprite()->setPosition(-10.f, -10.f);
    isSpawned = false;
    current_duration = 0.0f;
    exploding = false;
  }
}
void Bomb::innitBomb(const std::string& characterText)
{
  if(!bombTexture.loadFromFile(characterText))
  {
    std::cerr << "Bomb png did not load";
  };
  GetObjSprite()->setTexture(bombTexture);
  GetObjSprite()->setScale(radius, radius);
  animation.initAnim(&bombTexture, sf::Vector2u(24,1), 0.1);
}
bool Bomb::getIsSpawned() const
{
  return isSpawned;
}
void Bomb::setSpawned(bool spawned)
{
  Bomb::isSpawned = spawned;
}
void Bomb::draw()
{
  if(isSpawned)
  {
    window.draw(*GetObjSprite());
  }

}
float Bomb::getRadius() const
{
  return radius;
}
void Bomb::setRadius(float radius)
{
  Bomb::radius = radius;
}
const sf::Vector2f& Bomb::getSpawnPos() const
{
  return spawnPos;
}
void Bomb::setSpawnPos(const sf::Vector2f& spawnPos)
{
  Bomb::spawnPos = spawnPos;
}
bool Bomb::isExploding() const
{
  return exploding;
}
