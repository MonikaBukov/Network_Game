//
// Created by m2-bukovics on 25/10/2023.
//

#ifndef SFMLGAME_ANIMATION_H
#define SFMLGAME_ANIMATION_H
# include <SFML/Graphics.hpp>

class Animation
  {
   public:
    Animation();
    ~Animation();

    void initAnim (sf::Texture* texture, sf::Vector2u imageCount, float switch_time);
    void Update(int row, float dt,bool faceRight);
    void resetAnim();
    sf::IntRect rect;

   private:
    sf::Vector2u image_count;
    sf::Vector2u current_image;

    float total_time;
    float switch_time;
  };

#endif // SFMLGAME_ANIMATION_H
