//
// Created by monik on 25/10/2023.
//

#include "InputFieldUI.h"
InputFieldUI::InputFieldUI(sf::RenderWindow& window, sf::Font& font, int fontSize, sf::Color textColor, sf::Color fillColor, sf::Vector2f position, sf::Vector2f size, int limit)
  : window(window), font(font), fontSize(fontSize), textColor(textColor), fillColor(fillColor), position(position), size(size), limit(limit)
{
  text.setFont(font);
  text.setCharacterSize(fontSize);
  text.setFillColor(textColor);
  inputBox.setSize(getPercentage(size));
  inputBox.setFillColor(fillColor);
  inputBox.setPosition(getPercentage(position));
  sf::Vector2f boxPos = inputBox.getPosition();
  posY = boxPos.y + (inputBox.getGlobalBounds().height / 2) -
             text.getGlobalBounds().height / 2 - 15;
  text.setPosition(boxPos.x + 10, posY);

}

  void InputFieldUI::handleEvent(sf::Event event)
  {
    int charLim;

    charLim = GetCharacterLimit(text, inputBox.getGlobalBounds(), 20);
    if (getIsEnabled())
    {
      if (event.type == sf::Event::TextEntered)
      {
        if (event.text.unicode < 128)
        {
          if (event.text.unicode == '\b' && !inputText.empty())
          {
            inputText.pop_back();
          }
          else if (inputText.length() < limit)
          {
            if (event.text.unicode != '\b' && event.text.unicode != 13)
            {
              inputText += static_cast<char>(event.text.unicode);
            }
          }
        }
      }
      text.setString(inputText);
      if (
        text.getGlobalBounds().width >
        inputBox.getGlobalBounds().width - 20)
      {
        charLim = GetCharacterLimit(text, inputBox.getGlobalBounds(), 20);
        std::cout <<charLim;
        {
          if (!wasWarped && charLim != 1000)
          {
            charLim = GetCharacterLimit(text, inputBox.getGlobalBounds(), 20);
            if (!limitationSet)
            {
              prevlim = charLim;
              limitationSet = true;
            }
            int notInUse;
            inputText = TextWarp(inputText, 0, charLim, notInUse, notInUse);
            text.setPosition(text.getPosition().x, text.getPosition().y - text.getGlobalBounds().height / 2);
            wasWarped = true;
          }
        }
      }
      else if (wasWarped && inputText.length() <= prevlim)
      {
        wasWarped = false;
        text.setPosition(boxPos.x + 10, posY);
      }

    }
  }

  void InputFieldUI::draw()
  {
    if (getIsEnabled())
    {
      if (getIsEnabled())
      {
        window.draw(inputBox);
        window.draw(text);
      }
    }
  }
  float InputFieldUI::getWidth()
  {
    sf::FloatRect inputBoxBounds = inputBox.getGlobalBounds();
    float inputBoxWidth = inputBoxBounds.width;
    return  inputBoxWidth;
  }
  void InputFieldUI::clearInput() {
    inputText.clear();
    text.setString(inputText);
    text.setPosition(boxPos.x + 10, posY);
    wasWarped = false;
  }
  const sf::Vector2f& InputFieldUI::getPos()
  {
    boxPos = inputBox.getPosition();
    return boxPos;
  }
  const std::string& InputFieldUI::getInputText()
  {
    std::string newString = inputText;
    size_t pos;
    if ((pos = newString.find('\n')) != std::string::npos)
      newString.erase(pos, 1);
    inputText = newString;
    std::cout << inputText << "\n";
    return inputText;
  }
  float InputFieldUI::getHeight()
  {
    sf::FloatRect inputBoxBounds = inputBox.getGlobalBounds();
    float inputBoxHeight = inputBoxBounds.height;
    return  inputBoxHeight;

  }
  sf::FloatRect InputFieldUI::GetBounds()
  {
    sf::FloatRect inputBoxBounds = inputBox.getGlobalBounds();
    return  inputBoxBounds;
  }