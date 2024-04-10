//
// Created by monik on 16/11/2023.
//

#ifndef SFMLGAME_NETWORK_H
#define SFMLGAME_NETWORK_H

#include "Client.h"
#include "Server.h"

class Network
{
 public:
  Network();
  ~Network() = default;
  bool clientConnect(sf::IpAddress& ipToConnect);
  [[nodiscard]] const std::unique_ptr<Client>& getClient() const;
  [[nodiscard]] const std::unique_ptr<Server>& getServer() const;
  void  createServer();
  sf::IpAddress localIP = sf::IpAddress::getLocalAddress();
  bool serverCreate = false;

 private:
  std::unique_ptr<Client> client = nullptr;
  std::unique_ptr<Server> server = nullptr;
  void runServer();


 public:

};

#endif // SFMLGAME_NETWORK_H
