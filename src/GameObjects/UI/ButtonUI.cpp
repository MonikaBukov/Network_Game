//
// Created by monik on 28/10/2023.
//

#include "ButtonUI.h"

ButtonUI::ButtonUI(
  sf::Font& font, int fontSize, sf::Color textColor, const sf::String& buttonFilePath,
  const sf::String& buttonText, sf::Vector2f position, sf::Vector2f scale)
  : font(font), fontSize(fontSize), textColor(textColor), buttonFilePath(buttonFilePath), buttonText(buttonText), position(position), scale(scale)
{
  // Load button texture
  buttonTexture.loadFromFile(buttonFilePath);

  // Set up button sprite
  buttonBox.GetObjSprite()->setTexture(buttonTexture);

  // Calculate desired size based on scale
  float targetWidth = scale.x;
  float targetHeight = scale.y;

  // Set the size of the sprite
  buttonBox.GetObjSprite()->setScale(getPercentage(sf::Vector2f (targetWidth / buttonBox.GetObjSprite()->getLocalBounds().width, targetHeight / buttonBox.GetObjSprite()->getLocalBounds().height)));

  // Set position (scaled)
  buttonBox.GetObjSprite()->setPosition(getPercentage(position));

  // Set up text
  text.setFont(font);
  text.setCharacterSize(fontSize);
  text.setFillColor(textColor);
  text.setString(buttonText);

  // Center the text within the button
  sf::FloatRect textBounds = text.getLocalBounds();
  sf::FloatRect buttonBounds = buttonBox.GetObjSprite()->getGlobalBounds();

  float offsetX = (buttonBounds.width - textBounds.width) / 2.0f;
  float offsetY = (buttonBounds.height - textBounds.height) / 2.0f;

  text.setPosition(buttonBox.GetObjSprite()->getPosition().x + offsetX, buttonBox.GetObjSprite()->getPosition().y + offsetY);
}
void ButtonUI::draw()
{
  if (getIsEnabled())
  {
    window.draw(*buttonBox.GetObjSprite());
    window.draw(text);
  }
}

float ButtonUI::getWidth()
{
  sf::FloatRect buttonBoxBounds = buttonBox.GetObjSprite()->getGlobalBounds();
  float buttonBoxWidth = buttonBoxBounds.width;
  return buttonBoxWidth;
}

sf::Vector2<float> ButtonUI::getPosition()
{
  sf::Vector2f buttonBoxPosition = buttonBox.GetObjSprite()->getPosition();

  return buttonBoxPosition;
}

bool ButtonUI::isInsidePoint(sf::Vector2f point) const
{
  sf::FloatRect rect = buttonBox.GetObjSprite()->getGlobalBounds();
  return(rect.contains(point));
}

void ButtonUI::onSelected(sf::Event event)
{
  if (event.type == sf::Event::MouseMoved)
  {
    if (!available)
    {
      buttonBox.GetObjSprite()->setColor(sf::Color(50,50,50));
      selected = false;
    }
    if(available)
    {
      sf::Vector2i mousePos = sf::Mouse::getPosition(window);
      if (!selected)
      {
        if (isInsidePoint(static_cast<sf::Vector2f>(mousePos)))
        {
          buttonBox.GetObjSprite()->setColor(sf::Color(0, 255, 0));
          selected = true;
        }
      }
      if (selected || available)
      {
        if (!isInsidePoint(static_cast<sf::Vector2f>(mousePos)))
        {
          buttonBox.GetObjSprite()->setColor(sf::Color(255, 255, 255));
          selected = false;
        }
      }
    }
  }
}

bool ButtonUI::isSelected() const
{
  return selected;
}
bool ButtonUI::isAvailable() const
{
  return available;
}
void ButtonUI::setAvailable(bool available)
{
  ButtonUI::available = available;
}
const sf::Texture& ButtonUI::getButtonTexture() const
{
  return buttonTexture;
}
void ButtonUI::setButtonTexture(const sf::Texture& buttonTexture)
{
  ButtonUI::buttonTexture = buttonTexture;
}
