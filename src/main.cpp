#include <iostream>
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "GameWindow.h"


int main()
{
  std::cout << "You should see a window that opens as well as this writing to console..."
            << std::endl;

  // create window and set up
  sf::RenderWindow& window = GameWindow::getWindow();
  window.setFramerateLimit(60);

  sf::Texture cursorImg;
  if (!cursorImg.loadFromFile("Data/Images/sCursor.png")) {
    std::cerr << "Failed to load image" << std::endl;
  }
  sf::Cursor cursor;
  cursor.loadFromPixels(cursorImg.copyToImage().getPixelsPtr(), cursorImg.getSize(), {0, 0});
  {
    window.setMouseCursor(cursor);
  }

  sf::Image icon;
  if (!icon.loadFromFile("Data/Images/bomb.png")) {
    // Error loading image
    std::cerr << "Failed to load image" << std::endl;
  }
  window.setIcon(icon.getSize().x,icon.getSize().y, icon.getPixelsPtr());

  //initialise an instance of the game class
  Game game(window);

  // A Clock starts counting as soon as it's created
  sf::Clock clock;

  // Game loop: run the program as long as the window is open
  while (window.isOpen())
  {
    // check all the window's events that were triggered since the last iteration of the loop
    sf::Event event;

    //calculate delta time
    sf::Time time = clock.restart();
    float dt = time.asSeconds();

    //'process inputs' element of the game loop
    while (window.pollEvent(event) && window.hasFocus())
    {
      // "close requested" event: we close the window
      if (event.type == sf::Event::Closed)
        window.close();
      if (event.type == sf::Event::KeyPressed)
        game.keyPressed(event);
      if (event.type == sf::Event::TextEntered)
        game.textEntered(event);
      if (event.type == sf::Event::MouseButtonPressed)
        game.mouseClicked(event);
      if (event.type == sf::Event::MouseWheelScrolled)
        game.mouseWheelScrolled(event);
      if (event.type == sf::Event::MouseMoved)
        game.mouseMoved(event);
      if (event.type == sf::Event::Closed)
      {
        game.windowClosed(event);
      }
    }

    //'update' element of the game loop
    game.update(dt);

    window.clear(sf::Color::Black);

    //'render' element of the game loop
    game.render();
    window.display();
  }

  return 0;
}
