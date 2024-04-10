//
// Created by m2-bukovics on 18/10/2023.
//

#ifndef SFMLGAME_TILE_H
#define SFMLGAME_TILE_H

#include "../GameObjects/GameObject.h"
#include <SFML/Graphics.hpp>
#include <memory>

class Tile: public GameObject
{
 public:
  Tile();
  Tile(const int& ID, const sf::Texture& texture);
  ~Tile() = default;
  std::unique_ptr<sf::Sprite>& GetSpite();
  int GetID() const;
  Collider getCollider(){return Collider(*tileSprite);};

 private:
  int tileID = 0;
  std::unique_ptr<sf::Sprite> tileSprite;
};

#endif // SFMLGAME_TILE_H
