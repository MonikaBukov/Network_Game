//
// Created by m2-bukovics on 04/10/2023.
//

#ifndef SFMLGAME_SERVER_H
#define SFMLGAME_SERVER_H

#include <SFML/Network.hpp>
#include <atomic>
#include <iostream>
#include <list>
#include <memory>
#include <mutex>
#include <thread>

struct ClientData
{
  int clientID;
  int characterID;
  std::string  userName;
  int udpPortNumber;
  bool hasCharacter = false;
};


class Server
{
 public:
  void init();
  void run();
  void runTcpServer();
  void runUdpServer();
  void listen(sf::TcpSocket& cSocket);
  std::atomic<bool> created = false;
  bool isGameIsRunning() const;
  void sendToEveryone(sf::Packet& packet);
  void sendToSender(sf::Packet& packet);
  void sendToOthers(sf::Packet& packet);
  void sendInfoForNewConnections();
  void sendInfoForGameStart(sf::Packet receivedPacket);
  void sendInfoForChosenCharacter(sf::Packet receivedPacket, sf::Packet copyPacket, short currentClientID);
  void handleDisconnection(sf::Packet& copyPacket,int clientId);

 private:
  std::vector<std::thread> workers;
  std::vector<std::unique_ptr<sf::TcpSocket>> connections;
  std::unique_ptr<sf::TcpListener>listener;
  std::unique_ptr<sf::TcpSocket> tcpSocket;
  std::unique_ptr<sf::UdpSocket> udpSocket;
  unsigned short serverPort = 54000;
  std::mutex mutex;
  bool  running = true;
  int portNum;

  bool gameIsRunning = false;


  //info needed for character selection
  short clientNum = 0;
  short MAX_CLIENT_NUMBER = 4;
  std::vector<short>clientIDs[4];
  std::vector<bool>characterAvailableID = {true,true,true,true};
  std::vector<int> characterChoosenID;
  std::vector<int> characterOwnedBy ={0,0,0,0};
  std::vector<ClientData> connectedClients;




};

#endif // SFMLGAME_SERVER_H
