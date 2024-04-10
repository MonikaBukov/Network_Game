//
// Created by m2-bukovics on 04/10/2023.
//

#include "Server.h"
#include "../ChatMessage.h"

void Server::init()
{
  if (listener == nullptr) listener = std::make_unique<sf::TcpListener>();
  if (listener->listen(53000) != sf::Socket::Done)
  {
    std::cerr << "Failed to bind and listen on port 53000" << std::endl;
  }
  udpSocket = std::make_unique<sf::UdpSocket>();
  if (udpSocket->bind(serverPort) != sf::Socket::Done)
  {
    std::cerr << "Failed to bind and listen on port 54000" << std::endl;
  }
}

void Server::run()
{
  std::thread run_udp_server([&] {runUdpServer(); });
  run_udp_server.detach();
  runTcpServer();
}

void Server::runTcpServer()
{
  {
    while (running)
    {
        sf::TcpSocket& cSock =
          connections.emplace_back(std::make_unique<sf::TcpSocket>()).operator*();
        if (listener->accept(cSock) != sf::Socket::Done)
        {
          connections.pop_back();
          return;
        }
        else
        {
          std::cout << "Accept new client done \n";
        }
        std::cout << "Client connected @ " << cSock.getRemotePort()
                  << std::endl;
        workers.emplace_back(
          [&]
          {
            listen(cSock);
            std::lock_guard<std::mutex> lck(mutex);
            for (int i = 0; i < connections.size(); ++i)
            {
              if (connections[i]->getLocalPort() == cSock.getLocalPort())
              {
                connections.erase(connections.begin() + i);
                break;
              }
            }
          });
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
  }
}
void Server::runUdpServer()
{
  while (running)
  {
    sf::Packet receivedPacket;
    sf::IpAddress sender;
    unsigned short port;

    auto status = udpSocket->receive(receivedPacket, sender, port);

    if (status == sf::Socket::Done)
    {
      // Handle the received UDP packet
      for (auto& client : connectedClients)
      {
        sf::IpAddress clientIpAddress   = sf::IpAddress::getLocalAddress();
        unsigned short clientPort       = client.udpPortNumber;
        sf::Packet copyOfReceivedPacket = receivedPacket;
        if (client.udpPortNumber != port)
        {
          if (
            udpSocket->send(
              copyOfReceivedPacket, clientIpAddress, clientPort) !=
            sf::Socket::Done)
          {
            std::cerr << "Failed to send UDP packet to client "
                      << clientIpAddress << ":" << clientPort << std::endl;
          }
        }
      }
    }
  }
}

void Server::listen(sf::TcpSocket& cSocket)
{
  static short clientID   = 0;
  short currentClientID   = ++clientID;
  bool continue_receiving = true;
  while (continue_receiving)
  {
    sf::Packet receivedPacket;
    auto status           = cSocket.receive(receivedPacket);
    sf::Packet copyPacket = receivedPacket;
    if (status == sf::Socket::Status::Disconnected)
    {
      continue_receiving = false;
      std::cout << "Disconnected" << std::endl;
    }
    int messageType;
    copyPacket >> messageType;
    sf::IpAddress IP = cSocket.getRemoteAddress();
    portNum          = cSocket.getRemotePort();
    if (static_cast<MessageType>(messageType) == MessageType::CHAR_CHOICE)
    {
      sendInfoForChosenCharacter(receivedPacket,copyPacket, currentClientID);
    }
    else if (static_cast<MessageType>(messageType) == MessageType::STATE)
    {
      int state;
      copyPacket >> state;
      if (state == 2)
      {
        bool hasSelected = true;

        for (const ClientData& value : connectedClients)
        {
          hasSelected &= value.hasCharacter;
        }

        if (hasSelected)
        {
          sendInfoForGameStart(receivedPacket);
          gameIsRunning = true;
        }
        else
        {
          ChatMessage msg;
          sf::Packet serverMsg;
          msg.sender = "Server";
          msg.text   = "Everyone must select a character before the game";
          serverMsg << msg;
          sendToEveryone(serverMsg);
        }
      }
      else if (state == 1)
      {
        characterChoosenID.clear();
        gameIsRunning = false;
        sendToEveryone(receivedPacket);
      }
    }
    else if (static_cast<MessageType>(messageType) == MessageType::BOMB_SPAWN)
    {
      sendToEveryone(receivedPacket);
    }
    else if(static_cast<MessageType>(messageType) == MessageType::NEW_CONNECTION)
    {
      clientNum++;
      if (connectedClients.size()<MAX_CLIENT_NUMBER)
      {
        int newUDPPortNum;
        std::string userName;
        copyPacket >> newUDPPortNum >> userName;
        ClientData newClient;
        newClient.udpPortNumber = newUDPPortNum;
        newClient.userName      = userName;
        newClient.clientID      = currentClientID;
        newClient.characterID   = -1;
        connectedClients.push_back(newClient);
        sendInfoForNewConnections();
      }
      else
      {
        ConnectionRequest msg;
        msg.connectionAllowed = false;
        sf::Packet newPacket;
        newPacket << msg;
        sendToSender( newPacket);
      }
    }
    else if(static_cast<MessageType>(messageType) == MessageType::DISCONNECTION)
    {
      handleDisconnection(copyPacket,currentClientID);
    }
    else if(static_cast<MessageType>(messageType) == MessageType::ITEM_SPAWN || static_cast<MessageType>(messageType) == MessageType::ITEM_COLLECTED)
    {
      sendToEveryone(receivedPacket);
    }
    else
    {
      sendToOthers(receivedPacket);
    }
    std::cout << "Received from " << IP.toString() << std::endl;
  }
  cSocket.disconnect();
}

//send options
void Server::sendToEveryone(sf::Packet& packet) {
  for (auto& connection : connections)
  {
    std::lock_guard<std::mutex> lck(mutex);

    if (connection->send(packet) != sf::Socket::Done)
    {
      //std::cerr << "Failed to send packet to a everyone" << std::endl;
    }
  }
}
void Server::sendToSender(sf::Packet& packet) {
  std::lock_guard<std::mutex> lck(mutex);
  for (auto& connection : connections)
  {
    if (connection->getRemotePort() == portNum)
    {
      if (connection->send(packet) != sf::Socket::Done)
      {
        std::cerr << "Failed to send packet to a client" << std::endl;
      }
    }
  }
}
void Server::sendToOthers(sf::Packet& packet) {
  std::lock_guard<std::mutex> lck(mutex);
  for (auto& connection : connections)
  {
    if (connection->getRemotePort() != portNum)
    {
      if (connection->send(packet) != sf::Socket::Done)
      {
        std::cerr << "Failed to send packet to a other clients" << std::endl;
      }
    }
  }
}

//handling different type of info requests and send them back relevant info
void Server::sendInfoForNewConnections()
{
  sf::Packet connectionPacket;
  ConnectionMessage newConnection;
  newConnection.gameRunning = gameIsRunning;
  newConnection.characterAvailability = characterAvailableID;
  connectionPacket << newConnection;
  sendToSender(connectionPacket);
}

void Server::sendInfoForGameStart(sf::Packet receivedPacket)
{
  characterChoosenID.clear();

  // Collect character IDs that have been chosen
  for (int i = 0; i < characterAvailableID.size(); i++) {
    if (!characterAvailableID[i]) {
      characterChoosenID.push_back(i);
    }
  }

  // Send information about chosen characters
  for (auto& id : characterChoosenID)
  {
    OtherCharacters newChars;
    newChars.id = id;
    sf::Packet charPacket;
    charPacket << newChars;
    sendToEveryone(charPacket);
  }

  // Send the received packet if it's not empty
  if (!receivedPacket.getDataSize() == 0) {
    sendToEveryone(receivedPacket);
  }
}
void Server::sendInfoForChosenCharacter(sf::Packet receivedPacket, sf::Packet copyPacket, short currentClientID)
{
  int charID;
  copyPacket >> charID;
  ChatMessage message;
  for (auto& client: connectedClients)
  {
    if(client.clientID == currentClientID)
    {
      if (characterAvailableID[charID])
      {

        for (int i = 0; i < characterOwnedBy.size(); ++i)
        {
          if (characterOwnedBy[i] == client.clientID)
          {
            characterAvailableID[i] = true;
            characterOwnedBy[i]     = 0;
          }
        }
        characterOwnedBy[charID] = client.clientID;
        characterAvailableID[charID] = false;
        client.hasCharacter = true;
        sendToSender(receivedPacket);
      }
      else
      {
      }
    }
  }
  sf::Packet unavCharPacket;
  UnavailableCharacter unavailableCharacters;
  unavailableCharacters.characterAvailability = characterAvailableID;
  unavCharPacket << unavailableCharacters;
  sendToEveryone(unavCharPacket);
}

void Server::handleDisconnection(sf::Packet& copyPacket,int clientId)
{
  std::string userName;
  copyPacket >> userName;
  for (int i = 0; i < connectedClients.size(); ++i)
  {
    if (connectedClients[i].userName == userName)
    {
      for (int i = 0; i < characterOwnedBy.size(); ++i)
      {
        if (characterOwnedBy[i] == clientId)
        {
          characterAvailableID[i] = true;
          characterOwnedBy[i]     = 0;
        }
      }
      ChatMessage msg;
      sf::Packet serverMsg;
      msg.sender = userName;
      msg.text = " Left the game";
      serverMsg << msg;
      sendToEveryone(serverMsg);
      connectedClients.erase(connectedClients.begin() + i);
      sf::Packet connectionPacket;
      ConnectionMessage newConnection;
      newConnection.gameRunning = isGameIsRunning();
      newConnection.characterAvailability = characterAvailableID;
      connectionPacket << newConnection;
      sendToEveryone(connectionPacket);
      break;
    }
  }
}

// setters and getters
bool Server::isGameIsRunning() const
{
  return gameIsRunning;
}
