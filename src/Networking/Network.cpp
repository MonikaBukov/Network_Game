//
// Created by monik on 16/11/2023.
//

#include "Network.h"

Network::Network(): client(std::make_unique<Client>()) {}

bool Network::clientConnect(sf::IpAddress& ipToConnect)
{
  client->connect( ipToConnect);
  return client->connected;
}
const std::unique_ptr<Client>& Network::getClient() const
{
  return client;
}
void Network::runServer() {
  server = std::make_unique<Server>();
  server->init();
  serverCreate = server->created;
  server->run();
}
void Network::createServer()
{
  std::thread run_server([&] { runServer(); });
  run_server.detach();
}
const std::unique_ptr<Server>& Network::getServer() const
{
  return server;
}
