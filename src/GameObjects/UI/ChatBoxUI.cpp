//
// Created by monik on 28/10/2023.
//

#include "ChatBoxUI.h"
#include <algorithm>


ChatBoxUI::ChatBoxUI(Client& client) : client(client){}

void ChatBoxUI::innitElements(sf::Font& font, const sf::String& buttonFilePath)
{
  sendButton = std::make_unique<ButtonUI>(
    font, 15, CustomColors::TxtBlue , buttonFilePath,
    "send", sf::Vector2f(25, 95), sf::Vector2f(6, 5));
  messageInput = std::make_unique<InputFieldUI>(window,font, 15, CustomColors::TxtBlue, CustomColors::BcktBlue, sf::Vector2f (0,95), sf::Vector2f (25,5), 55);
  float combinedWidth = messageInput->getWidth() + sendButton->getWidth();
  sf::Vector2f oneThird = getPercentage(sf::Vector2f(33,33));
  chatBox.setSize(sf::Vector2f (combinedWidth, oneThird.y));
  chatBox.setPosition(0, window.getSize().y - chatBox.getSize().y);
  chatBox.setFillColor(CustomColors::BckGreen);
  chatBox.setOutlineThickness(3);
  chatBox.setOutlineColor(CustomColors::BrdGreen);
  m_text.setFont(font);
  m_text.setCharacterSize(15);
  m_text.setFillColor(CustomColors::TxtBlue);
  spacing = (m_text.getLineSpacing()*2) + m_text.getCharacterSize() + 3;
  setIsEnabled(true);
}
void ChatBoxUI::draw()
{
  if (getIsEnabled())
  {
    window.draw(chatBox);

    int characterLimit;
    int y = messageInput->getPos().y - 24;
    for (const auto& message : chatMessages)
    {
      std::string senderString    = message.sender + ": ";
      std::string tempMessageText = senderString + message.text;
      std::string messageText;
      m_text.setString(tempMessageText);
      characterLimit = GetCharacterLimit(m_text, chatBox.getGlobalBounds(), 1);

      int emptySpaceToIgnore = senderString.length() - 1;

      if (tempMessageText.length() > characterLimit)
      {
        messageText = TextWarp(
          tempMessageText, emptySpaceToIgnore, characterLimit, y, spacing);
      }
      else
      {
        messageText = tempMessageText;
      }
      m_text.setStyle(sf::Text::Regular);
      m_text.setString(messageText);
      m_text.setPosition(15, y + deltaYScroll);
      sf::FloatRect boxWithOffset = chatBox.getGlobalBounds();
      boxWithOffset.top           = boxWithOffset.top + 30;
      boxWithOffset.height        = boxWithOffset.height - 83;
      if (
        isInsideRect(boxWithOffset, m_text.getGlobalBounds()))
      {
        window.draw(m_text);
      }
      y -= spacing;
    }
    messageInput->draw();
    sendButton->draw();
  }
}
void ChatBoxUI::handleEvent(sf::Event event)
{
  if (getIsEnabled())
  {
    if (messageInput)
    {
      messageInput->handleEvent(event);
    }
  }
}

void ChatBoxUI::handleStatus(sf::Event event)
{
  if (event.type == sf::Event::KeyPressed)
  {
    if (event.key.code == sf::Keyboard::Enter)
    {
      if (!getIsEnabled())
      {
        setIsEnabled(true);
      }
      else
      {
        sendChatMessage();
      }
    }
    else if (event.key.code == sf::Keyboard::Escape && getIsEnabled())
    {
      setIsEnabled(false);
    }
  }
}

ChatBoxUI::~ChatBoxUI() = default;

void ChatBoxUI::sendChatMessage() {
  std::string messageString = messageInput->getInputText();

  if (!messageString.empty())
  {
    ChatMessage chatMessage;
    chatMessage.text   = messageString;
    chatMessage.sender = client.getUserName();
    client.sendChatMessage(chatMessage);
    chatMessage.sender = "You";
    addMessage(chatMessage);
  }
  messageInput->clearInput();
}
void ChatBoxUI::addMessage(ChatMessage& sentMessage)
{
  chatMessages.insert(chatMessages.begin(),sentMessage);
  if (chatMessages.size() >20)
  {
    chatMessages.pop_back();
  }
}

void ChatBoxUI:: updateLatestChatMessage() {
  if (client.isMessageReceived())
  {
    ChatMessage receivedMessage = client.getLastMessage();
   addMessage(receivedMessage);
    if (!receivedMessage.text.empty())
    {
      client.setMessageReceived(false);
    }
  }
}
void ChatBoxUI::onClickSend(sf::Event event)
{
  if (event.type ==  sf::Event::MouseButtonPressed)
  {
    if (event.mouseButton.button == sf::Mouse::Left)
    {
      sf::Vector2i click = sf::Mouse::getPosition(window);
      if(sendButton->isInsidePoint(static_cast<sf::Vector2f>(click)))
      {
        sendChatMessage();
      }
    }
  }
}
void ChatBoxUI::OnScroll(sf::Event event)
{
  if (event.type == sf::Event::MouseWheelScrolled)
  {
    if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
    {
      if (!chatMessages.empty())

      {
        deltaY = event.mouseWheelScroll.delta;
        deltaY = -deltaY * 4;

        int maxScroll;
        int minScroll;
        int totalHeight;
        int messageHeight;

        if (!chatMessages.empty())
        {
          for (const auto& message : chatMessages)
          {
            sf::FloatRect bounds = m_text.getLocalBounds();
            messageHeight = bounds.height;
            totalHeight += messageHeight;
          }
          maxScroll = totalHeight - chatBox.getGlobalBounds().height;
         // maxScroll = totalHeight;

          minScroll = 0;
        }
        deltaYScroll += deltaY;
        if (deltaYScroll > maxScroll)
        {
          deltaYScroll = maxScroll;
        }
        else if (deltaYScroll < minScroll)
        {
          deltaYScroll = minScroll;
        }
      }
    }
  }
}
const std::unique_ptr<ButtonUI>& ChatBoxUI::getSendButton() const
{
  return sendButton;
}
