//
// Created by m2-bukovics on 04/10/2023.
//

#ifndef SFMLGAME_CLIENT_H
#define SFMLGAME_CLIENT_H

#include "../ChatMessage.h"
#include "../GameObjects/Bomb.h"
#include "../GameObjects/Character.h"
#include "../GameObjects/Item.h"
#include <Sfml/Network.hpp>
#include <atomic>
#include <future>
#include <iostream>
#include <thread>
#include <vector>

class Client
{
 public:
  void connect(sf::IpAddress& ipToConnect);
  void run();
  std::atomic<bool> running = false;
  std::atomic<bool> connected = false;
  void handleTCPMessages(MessageType messageType, sf::Packet& packet);
  void handleUdpMessage(MessageType messageType, sf::Packet& receivedPacket);
  void runUdpClient();

  void sendChatMessage(const ChatMessage& message);
  bool isMessageReceived() const;
  void setMessageReceived(bool messageReceived);
  const ChatMessage& getLastMessage() const;
  void setLastMessage(const ChatMessage& lastMessage);
  void handleChatMessage(sf::Packet& packet);

  const std::string& getUserName() const;
  void setUserName(const std::string& userName);
  int getNewState() const;
  bool isStateChanged() const;
  void setStateChanged(bool stateChanged);
  bool isServerHost() const;
  void setServerHost(bool serverHost);
  bool isGameIsRunning() const;
  int getCharacterId() const;



  std::vector<std::unique_ptr<Character>> otherCharacters;
  std::vector<std::unique_ptr<Bomb>> otherBombs;
  std::vector<std::unique_ptr<GameObject>> tombstones;
  std::vector<std::unique_ptr<Item>> items;

 private:
  std::unique_ptr<sf::TcpSocket> TcpSocket;
  std::unique_ptr<sf::UdpSocket> UdpSocket;
  sf::IpAddress clientIpAddress;
  unsigned short localPort;
  bool messageReceived;
  ChatMessage lastMessage;
  std::string  userName;


 public:
  bool isHasCharacter() const;
  bool isCharacterChanged() const;
  void setCharacterChanged(bool characterChanged);
  bool isCollectionAllowed() const;
  const std::vector<int>& getOtherPlayers() const;
  const std::vector<bool>& getCharacterAvailablity() const;

 private:
  bool serverHost= false;
  bool gameIsRunning = false;
  int newState;
  bool stateChanged= false;
  int characterID;
  std::vector<int> otherPlayers;
  std::vector<bool> characterAvailablity;
  bool collectionAllowed = false;
  bool hasCharacter = false;
  bool characterChanged = false;
  bool newItemSpawned = false;

 public:
  bool isNewItemSpawned() const;
  void setNewItemSpawned(bool newItemSpawned);

 private:
  void handleConnectionMessage(sf::Packet& packet);
  void handleCharacterUpdateMessage(sf::Packet& packet);
  void handleBombSpawnMessage(sf::Packet& packet);
  void handlePlayerKilledMessage(sf::Packet& packet);
  void handleCOnnectionDeniedMessage(sf::Packet& packet);
  void handleCharChooseMessage(sf::Packet& packet);
  void handleOtherCharChooseMessage(sf::Packet& packet);
  void handleUnavCharChooseMessage(sf::Packet& packet);
  void handleStateMessage(sf::Packet& packet);
  void handleItemSpawnedMessages(sf::Packet& packet);
  void handleItemCollectedMessages(sf::Packet& packet);

 public:
  void sendSateMessage(const StateMessage& message);
  void sendCharChoiceMessage(const CharacterChoosing& message);
  void sendPlayerUpdate2(const CharacterUpdatePacket& message);
  void sendBombSpawnMessage(const BombSpawnMessage& message);
  void sendPlayerDiedMsg(const PlayerKilledMessage& message);
  void sendDisconnectionRequest(const Disconnection& message);
  void sendConnectionRequest(const NewConnection& message);
  void sendWelcomeMessage();
  void sendItemSpawnedMessage(const ItemSpawnedMessage& message);
  void sendItemCollectedMessage(const ItemCollectedMessage& message);
};

#endif // SFMLGAME_CLIENT_H
