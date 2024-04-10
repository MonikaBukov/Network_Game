//
// Created by monik on 28/10/2023.
//

#ifndef SFMLGAME_CHATBOXUI_H
#define SFMLGAME_CHATBOXUI_H


#include <vector>
#include "../../Networking/Client.h"
#include "UIElement.h"
#include "ButtonUI.h"
#include "InputFieldUI.h"

class ChatBoxUI : public UIElement {
 public:
  explicit ChatBoxUI(Client& client);;
  ~ChatBoxUI();
  void innitElements(sf::Font& font, const sf::String& buttonFilePa);
  void handleEvent(sf::Event event);
  void draw();
  void sendChatMessage();
  void addMessage(ChatMessage& message);
  void updateLatestChatMessage();
  void handleStatus(sf::Event event);
  void onClickSend(sf::Event event);
  void OnScroll(sf::Event event);
  const std::unique_ptr<ButtonUI>& getSendButton() const;


 private:
  Client& client;
  std::unique_ptr<InputFieldUI> messageInput;
  std::unique_ptr<ButtonUI> sendButton;
  sf::RectangleShape chatBox;
  std::vector<ChatMessage> chatMessages;
  sf::Font m_font;
  sf::Text m_text;
  int y;
  bool newMessageAdded = false;
  float deltaY;
  float deltaYScroll = 0;
  int spacing;


};


#endif // SFMLGAME_CHATBOXUI_H
