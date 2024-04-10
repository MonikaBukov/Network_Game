//
// Created by m2-bukovics on 25/10/2023.
//

#ifndef SFMLGAME_COLLIDER_H
#define SFMLGAME_COLLIDER_H
# include <SFML/Graphics.hpp>


class Collider
{
 public:
  explicit Collider(sf::Sprite& body);
  ~Collider();

  void  move(float  dx, float  dy) const;
  bool checkCollision(const Collider& other, sf::Vector2f& direction);
  sf::Vector2f getPosition() const;
  sf::Vector2f getHalfSize() const;

 private:
  sf::Sprite& body;
};

#endif // SFMLGAME_COLLIDER_H
