//
// Created by m2-bukovics on 04/10/2023.
//

#include "Client.h"
#include "../GameStates/GamePlay.h"


void Client::connect(sf::IpAddress& ipToConnect)
{
  if (TcpSocket == nullptr)
    TcpSocket = std::make_unique<sf::TcpSocket>();

  if (TcpSocket->connect(ipToConnect, 53000) == sf::Socket::Status::Done)
  {
    std::cout << "You're Connected!" << std::endl;
    connected = true;
    sendWelcomeMessage();

    UdpSocket = std::make_unique<sf::UdpSocket>();
    if (UdpSocket->bind(sf::Socket::AnyPort) != sf::Socket::Done)
    {
      std::cerr << "Failed to bind UDP socket" << std::endl;
      return;
    }
    localPort = UdpSocket->getLocalPort();
    NewConnection infoRequest;
    infoRequest.localPort = localPort;
    infoRequest.userName = getUserName();
    std::cout <<  infoRequest.userName << "name is sent";
    sendConnectionRequest(infoRequest);

    // Start the TCP thread
    std::thread run_thread([this] { run(); });
    run_thread.detach();

    // Start the UDP thread
    std::thread run_Udpthread([this] { runUdpClient(); });
    run_Udpthread.detach();
  }
  else
  {
    std::cerr << "Failed to connect" << std::endl;
  }
}

void Client::run()
{
  running = true;
  while (running && connected)
  {
    while (connected)
    {
      sf::Packet receivedPacket;
      auto status = TcpSocket->receive(receivedPacket);
      if (status == sf::Socket::Status::Disconnected)
      {
        connected = false;
        std::cout << "clean disconnection" << std::endl;
        TcpSocket->disconnect();
        return ;
      }
      else if (status == sf::Socket::Status::Done)
      {
        int messageType;
        receivedPacket >> messageType;
        handleTCPMessages(
          static_cast<MessageType>(messageType), receivedPacket);
      }
      else if (status == sf::Socket::Status::Error)
      {
        std::cerr << "Socket error occurred. Closing connection." << std::endl;
        connected = false;
        TcpSocket->disconnect();
        return;
      }
      else
      {
        int portnum = TcpSocket->getRemotePort();
        std::cerr << "Failed to receive packet. Status: " << status
                  << std::endl;
      }
    }
  }
}

void Client::runUdpClient()
{
  while (running)
  {
    sf::Packet receivedPacket;
    sf::IpAddress sender;
    unsigned short port;

    auto status = UdpSocket->receive(receivedPacket, sender, port);
    if (status == sf::Socket::Status::Disconnected)
    {
      std::cout << "udo clean disconnection" << std::endl;
      UdpSocket->unbind();
      return ;
    }

    if (status == sf::Socket::Done)
    {
      int messageType;
      receivedPacket >> messageType;
      handleUdpMessage(static_cast<MessageType>(messageType), receivedPacket);
    }
  }
}

void Client::handleTCPMessages(MessageType messageType, sf::Packet& receivedPacket)
{
  switch (static_cast<MessageType>(messageType))
  {
    case MessageType::CHAT:
      handleChatMessage(receivedPacket);
      break;
    case MessageType::STATE:
      handleStateMessage(receivedPacket);
      break;
    case MessageType::CONNECTION:
      handleConnectionMessage(receivedPacket);
      break;
    case MessageType::CHAR_CHOICE:
      handleCharChooseMessage(receivedPacket);
      break;
    case MessageType::OTHER_CHAR:
      handleOtherCharChooseMessage(receivedPacket);
      break;
    case MessageType::UNAV_CHAR:
      handleUnavCharChooseMessage(receivedPacket);
      break;
    case MessageType::BOMB_SPAWN:
      handleBombSpawnMessage(receivedPacket);
      break;
    case MessageType::BOMB_KILLED:
      handlePlayerKilledMessage(receivedPacket);
      break;
    case MessageType::CONNECTION_DENIED:
      handleCOnnectionDeniedMessage(receivedPacket);
      break ;
      //this will cause error and can not recconect even after reduced player number:
      //TcpSocket->disconnect();
    case MessageType::ITEM_SPAWN:
      handleItemSpawnedMessages(receivedPacket);
      break ;
    case MessageType::ITEM_COLLECTED:
     handleItemCollectedMessages(receivedPacket);
     break ;
    default:
      std::cerr << "Received an unknown message type: " << messageType << std::endl;
      break;
  }
}
void Client::handleUdpMessage(MessageType messageType, sf::Packet& receivedPacket)
{
  switch (static_cast<MessageType>(messageType))
  {
    case MessageType::CHARACTER_UPDATE:
      handleCharacterUpdateMessage(receivedPacket);
      break;
    default:
      std::cerr << "Received an unknown message type: " << messageType << std::endl;
      break;
  }
}

void Client::handleChatMessage(sf::Packet& packet)
{
  ChatMessage chatMessage;
  if (packet >> chatMessage)
  {
    setLastMessage(chatMessage);
    setMessageReceived(true);
  }
  else
  {
    std::cerr << "Failed to extract chat message from received packet." << std::endl;
  }
}
void Client::handleStateMessage(sf::Packet& packet)
{
  StateMessage stateMessage;
  packet >> stateMessage;

  // Handle state change
   newState = stateMessage.state;
   stateChanged = true;
  switch (newState)
  {
    case 1:
      //clearing out all vectors for the next round
      otherBombs.clear();
      otherCharacters.clear();
      otherPlayers.clear();
      items.clear();
      break;
    case 2:
      // StateType::InGame
      break;
    case 3:
      // StateType::GameOver
      break;
    default:
      std::cerr << "Received an unknown state: " << newState << std::endl;
      break;
  }
}

// handle received packets
void Client::handleConnectionMessage(sf::Packet& packet)
{
  ConnectionMessage connectionMessage;
  if (packet >> connectionMessage)
  {
    collectionAllowed = true;
    gameIsRunning = connectionMessage.gameRunning;
    std::cerr << gameIsRunning << std::endl;
    characterAvailablity = connectionMessage.characterAvailability;
  }
  else
  {
    std::cerr << "Failed to extract chat message from received packet." << std::endl;
  }
}
void Client::sendWelcomeMessage()
{
  ChatMessage newConnection;
  newConnection.text = "Is Connected. Say Hi!";
  newConnection.sender = userName;
  sendChatMessage(newConnection);
}
void Client::handleCharChooseMessage(sf::Packet& packet)
{
  CharacterChoosing charMessage;
  if (packet >> charMessage)
  {
    characterID = charMessage.id;
    hasCharacter = true;
    characterChanged = true;
  }
  else
  {
    std::cerr << "Failed to extract character choose message from received packet." << std::endl;
  }
}
void Client::handleOtherCharChooseMessage(sf::Packet& packet)
{
  OtherCharacters charMessage;
  if (packet >> charMessage)
  {
    otherPlayers.push_back(charMessage.id);
  }
  else
  {
    std::cerr << "Failed to extract other character message from received packet." << std::endl;
  }
}
void Client::handleUnavCharChooseMessage(sf::Packet& packet)
{
  UnavailableCharacter charMessage;
  if (packet >> charMessage)
  {
    characterAvailablity = charMessage.characterAvailability;
  }
  else
  {
    std::cerr << "Failed to extract unavailable character message from received packet." << std::endl;
  }
}
void Client::handleCharacterUpdateMessage(sf::Packet& packet)
{
  CharacterUpdatePacket charMessage;
  if (packet >> charMessage)
  {
    for(auto & otherCharacter : otherCharacters)
    {
      if(charMessage.characterID == otherCharacter->getId())
      {
        otherCharacter->changePosition(sf::Vector2f (charMessage.newPosition.x, charMessage.newPosition.y));
        otherCharacter->movementDirection =  static_cast<Character::MovementDirection>(charMessage.state);
      }
    }
  }
  else
  {
    std::cerr << "Failed to extract character update message from received packet." << std::endl;
  }
}
void Client::handleBombSpawnMessage(sf::Packet& packet)
{
  BombSpawnMessage charMessage;
  if (packet >> charMessage)
  {
    for(int i = 0; i < otherBombs.size(); i++)
    {
      if (charMessage.charID == i)
      {
       otherBombs[i]->setSpawnPos(charMessage.spawn_pos);
       otherBombs[i]->setSpawned(true);
       otherBombs[i]->setRadius(charMessage.radius);
      }
    }
  }
  else
  {
    std::cerr << "Failed to extract bomb spawn message from received packet." << std::endl;
  }
}
void Client::handlePlayerKilledMessage(sf::Packet& packet)
{
  PlayerKilledMessage charMessage;
  if (packet >> charMessage)
  {
    for(auto & otherCharacter : otherCharacters)
    {
      if(charMessage.id == otherCharacter->getId())
      {
        otherCharacter->setDead(true);
      }
    }
  }
  else
  {
    std::cerr << "Failed to extract character dead message from received packet." << std::endl;
  }
}
void Client::handleCOnnectionDeniedMessage(sf::Packet& packet)
{
  ConnectionRequest charMessage;
  if (packet >> charMessage)
  {
    std::cout << "Before: " << collectionAllowed << std::endl;
    collectionAllowed = false;
    std::cout << "After: " << collectionAllowed << std::endl;
  }
  else
  {
    std::cerr << "Failed to extract character choose message from received packet." << std::endl;
  }
}
void Client::handleItemSpawnedMessages(sf::Packet& packet)
{
  ItemSpawnedMessage itemMessage;
  if (packet >> itemMessage)
  {
    std::unique_ptr<Item> newItem = std::make_unique<Item>();
    newItem->setId(itemMessage.id);
    newItem->GetSpite()
        ->setPosition(itemMessage.spawnPos);
    newItem->type = static_cast<Item::Type>(itemMessage.itemType);
    items.push_back(std::move(newItem));
    newItemSpawned = true;
  }
  else
  {
    std::cerr << "Failed to extract character choose message from received packet." << std::endl;
  }
}
void Client::handleItemCollectedMessages(sf::Packet& packet)
{
  ItemCollectedMessage charMessage;
  if (packet >> charMessage)
  {

    for (int i = 0; i < items.size(); ++i)
    {
      if (items[i]->getId() == charMessage.id)
      {
        std::cout << items[i]->getId() << "will be deleted";
        items.erase(items.begin() + i);
        break;
      }
    }

  }
  else
  {
    std::cerr << "Failed to extract character choose message from received packet." << std::endl;
  }
}

// send  packets
void Client::sendChatMessage(const ChatMessage& message) {
  if (connected && TcpSocket) {
    sf::Packet messagePacket;
    messagePacket << message;
    if (TcpSocket->send(messagePacket) != sf::Socket::Done) {
      std::cerr << "Failed to send chat message" << std::endl;
    }
  }
  else
  {
    std::cerr << "Failed to send chat message. Socket not connected or invalid." << std::endl;
  }
}

void Client::sendSateMessage(const StateMessage& message) {
  if (connected && TcpSocket) {
    sf::Packet messagePacket;
    messagePacket << message;
    if (TcpSocket->send(messagePacket) != sf::Socket::Done) {
      std::cerr << "Failed to send state message" << std::endl;
    }
  }
  else
  {
    std::cerr << "Failed to send state message. Socket not connected or invalid." << std::endl;
  }
}

void Client::sendConnectionRequest(const NewConnection& message) {
  if (connected && TcpSocket) {
    sf::Packet connectionPacket;
    connectionPacket << message;
    if (TcpSocket->send(connectionPacket) != sf::Socket::Done) {
      std::cerr << "Failed to send connection message" << std::endl;
    }
  }
  else
  {
    std::cerr << "Failed to send connection message. Socket not connected or invalid." << std::endl;
  }
}

void Client::sendDisconnectionRequest(const Disconnection& message) {
  if (connected && TcpSocket) {
    sf::Packet connectionPacket;
    connectionPacket << message;
    std::cerr << "disconnection message" << std::endl;
    if (TcpSocket->send(connectionPacket) != sf::Socket::Done) {
      std::cerr << "Failed to send disconnection message" << std::endl;
    }
  }
  else
  {
    std::cerr << "Failed to send diconnection message. Socket not connected or invalid." << std::endl;
  }
}

void Client::sendCharChoiceMessage(const CharacterChoosing& message) {
  if (connected && TcpSocket) {
    sf::Packet connectionPacket;
    connectionPacket << message;
    if (TcpSocket->send(connectionPacket) != sf::Socket::Done) {
      std::cerr << "Failed to send character choice message" << std::endl;
    }
  }
  else
  {
    std::cerr << "Failed to send connection message. Socket not connected or invalid." << std::endl;
  }
}
void Client::sendPlayerUpdate2(const CharacterUpdatePacket& message) {
  if (UdpSocket && UdpSocket->getLocalPort() != 0) {
    sf::Packet updatePacket;
    sf::IpAddress serverIp = sf::IpAddress::getLocalAddress();
    updatePacket << message;
    if (UdpSocket->send(updatePacket, serverIp, 54000) != sf::Socket::Done) {
      std::cerr << "Failed to send player update udp message" << std::endl;
    }
  }
  else
  {
    std::cerr << "Failed to send player update message. Socket not connected or invalid from client to server." << std::endl;
  }
}
void Client::sendBombSpawnMessage(const BombSpawnMessage& message) {
  if (connected && TcpSocket) {
    sf::Packet messagePacket;
    messagePacket << message;
    if (TcpSocket->send(messagePacket) != sf::Socket::Done) {
      std::cerr << "Failed to send bomb spawn message" << std::endl;
    }
  }
  else
  {
    std::cerr << "Failed to send bomb spawn message. Socket not connected or invalid." << std::endl;
  }
}
void Client::sendPlayerDiedMsg(const PlayerKilledMessage& message)
{
  if (connected && TcpSocket) {
    sf::Packet messagePacket;
    messagePacket << message;
    if (TcpSocket->send(messagePacket) != sf::Socket::Done) {
      std::cerr << "Failed to send death message" << std::endl;
    }
  }
  else
  {
    std::cerr << "Failed to send death message. Socket not connected or invalid." << std::endl;
  }
}
void Client::sendItemSpawnedMessage(const ItemSpawnedMessage& message)
{
  if (connected && TcpSocket) {
    sf::Packet messagePacket;
    messagePacket << message;
    if (TcpSocket->send(messagePacket) != sf::Socket::Done) {
      std::cerr << "Failed to send death message" << std::endl;
    }
  }
  else
  {
    std::cerr << "Failed to send death message. Socket not connected or invalid." << std::endl;
  }
}
void Client::sendItemCollectedMessage(const ItemCollectedMessage& message)
{
  if (connected && TcpSocket) {
    sf::Packet messagePacket;
    messagePacket << message;
    if (TcpSocket->send(messagePacket) != sf::Socket::Done) {
      std::cerr << "Failed to send death message" << std::endl;
    }
  }
  else
  {
    std::cerr << "Failed to send death message. Socket not connected or invalid." << std::endl;
  }
}
// setters and getters
bool Client::isMessageReceived() const
{
  return messageReceived;
}
void Client::setMessageReceived(bool messageReceived)
{
  Client::messageReceived = messageReceived;
}
const ChatMessage& Client::getLastMessage() const
{
  return lastMessage;
}
void Client::setLastMessage(const ChatMessage& message)
{
 lastMessage = message;
}
const std::string& Client::getUserName() const
{
  return userName;
}
void Client::setUserName(const std::string& userName)
{
  Client::userName = userName;
}

int Client::getNewState() const
{
  return newState;
}
void Client::setStateChanged(bool stateChanged)
{
  Client::stateChanged = stateChanged;
}
bool Client::isStateChanged() const
{
  return stateChanged;
}
bool Client::isServerHost() const
{
  return serverHost;
}
void Client::setServerHost(bool serverHost)
{
  Client::serverHost = serverHost;
}
bool Client::isGameIsRunning() const
{
  return gameIsRunning;
}
int Client::getCharacterId() const
{
  return characterID;
}

const std::vector<int>& Client::getOtherPlayers() const
{
  return otherPlayers;
}
const std::vector<bool>& Client::getCharacterAvailablity() const
{
  return characterAvailablity;
}
bool Client::isCollectionAllowed() const
{
  return collectionAllowed;
}
bool Client::isHasCharacter() const
{
  return hasCharacter;
}
bool Client::isCharacterChanged() const
{
  return characterChanged;
}
void Client::setCharacterChanged(bool characterChanged)
{
  Client::characterChanged = characterChanged;
}
bool Client::isNewItemSpawned() const
{
  return newItemSpawned;
}
void Client::setNewItemSpawned(bool newItemSpawned)
{
  Client::newItemSpawned = newItemSpawned;
}
