//
// Created by monik on 01/11/2023.
//
#include "ChatMessage.h"
sf::Packet& operator <<(sf::Packet& packet, const ChatMessage& message)
{
  return packet <<CHAT << message.text << message.sender;
}
sf::Packet& operator >>(sf::Packet& packet, ChatMessage& message)
{
  packet >> message.text >> message.sender;
  return packet;
}


sf::Packet& operator <<(sf::Packet& packet, const StateMessage& message)
{
  return packet << STATE << message.state;
}
sf::Packet& operator >>(sf::Packet& packet, StateMessage& message)
{
  packet  >> message.state;
  return packet;
}


sf::Packet& operator <<(sf::Packet& packet, const ConnectionMessage& message)
{
  packet << CONNECTION << message.gameRunning;
  for (bool status : message.characterAvailability)
  {
    packet << status;
  }
  return packet;
}
sf::Packet& operator >>(sf::Packet& packet, ConnectionMessage& message)
{
  packet >> message.gameRunning;
  for (int i = 0; i < 4; ++i)
  {
    bool taken = true;
    packet >> taken;
    message.characterAvailability[i] = taken;
  }
  return packet;
}


sf::Packet& operator <<(sf::Packet& packet, const CharacterChoosing& message)
{
  return packet << CHAR_CHOICE << message.id;
}

sf::Packet& operator >>(sf::Packet& packet, CharacterChoosing& message)
{
  packet  >> message.id;
  return packet;
}


sf::Packet& operator <<(sf::Packet& packet, const CharacterUpdatePacket& message)
{
  return packet  << CHARACTER_UPDATE << message.characterID << message.newPosition.x << message.newPosition.y << message.state;
}
sf::Packet& operator >>(sf::Packet& packet, CharacterUpdatePacket& message)
{
  packet  >> message.characterID >> message.newPosition.x >> message.newPosition.y >> message.state;
  return packet;
}


sf::Packet& operator <<(sf::Packet& packet, const OtherCharacters& message)
{
  return packet << OTHER_CHAR << message.id;
}
sf::Packet& operator >>(sf::Packet& packet, OtherCharacters& message)
{
  packet  >> message.id;
  return packet;
}


sf::Packet& operator <<(sf::Packet& packet, const NewConnection& message)
{
  return packet << NEW_CONNECTION << message.localPort << message.userName;
}



sf::Packet& operator <<(sf::Packet& packet, const UnavailableCharacter& message)
{  packet << UNAV_CHAR;
  for (bool status : message.characterAvailability)
  {
    packet << status;
  }
  return packet;
}


sf::Packet& operator >>(sf::Packet& packet, UnavailableCharacter& message)
{
  for (int i = 0; i < 4; ++i)
  {
    bool available = true;
    packet >> available;
    message.characterAvailability[i] = available;
  }
  return packet;
}


sf::Packet& operator <<(sf::Packet& packet, const BombSpawnMessage& message)
{
  return packet << BOMB_SPAWN << message.charID << message.spawn_pos.x << message.spawn_pos.y << message.radius;
}
sf::Packet& operator >>(sf::Packet& packet, BombSpawnMessage& message)
{
  packet >> message.charID >> message.spawn_pos.x >> message.spawn_pos.y >> message.radius;
  return packet;
}


sf::Packet& operator <<(sf::Packet& packet, const PlayerKilledMessage& message)
{
  return packet << BOMB_KILLED << message.id;
}
sf::Packet& operator >>(sf::Packet& packet, PlayerKilledMessage& message)
{
  packet  >> message.id;
  return packet;
}


sf::Packet& operator <<(sf::Packet& packet, const Disconnection& message)
{
  return packet <<DISCONNECTION << message.userName;
}

sf::Packet& operator <<(sf::Packet& packet, const ConnectionRequest& message)
{
  return packet << CONNECTION_DENIED << message.connectionAllowed;
}
sf::Packet& operator >>(sf::Packet& packet, ConnectionRequest& message)
{
  packet  >> message.connectionAllowed;
  return packet;
}


sf::Packet& operator <<(sf::Packet& packet, const ItemSpawnedMessage& message)
{
  return packet << ITEM_SPAWN << message.id << message.itemType << message.spawnPos.x << message.spawnPos.y;
}
sf::Packet& operator >>(sf::Packet& packet, ItemSpawnedMessage& message)
{
  packet  >>  message.id >> message.itemType >> message.spawnPos.x >> message.spawnPos.y;
  return packet;
}


sf::Packet& operator <<(sf::Packet& packet, const ItemCollectedMessage& message)
{
  return packet << ITEM_COLLECTED << message.id;
}
sf::Packet& operator >>(sf::Packet& packet, ItemCollectedMessage& message)
{
  packet  >>  message.id;
  return packet;
}