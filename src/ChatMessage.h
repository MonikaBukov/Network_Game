//
// Created by m2-bukovics on 01/11/2023.
//

#ifndef SFMLGAME_CHATMESSAGE_H
#define SFMLGAME_CHATMESSAGE_H
#include <iostream>
#include <Sfml/Network.hpp>

enum  MessageType
{
  CHAT = 1,
  STATE = 2,
  CONNECTION = 3,
  CHAR_CHOICE = 4,
  CHARACTER_UPDATE = 5,
  OTHER_CHAR = 6,
  NEW_CONNECTION = 7,
  UNAV_CHAR = 8,
  BOMB_SPAWN = 9,
  BOMB_KILLED = 10,
  ITEM_SPAWN = 11,
  ITEM_COLLECTED = 12,
  DISCONNECTION = 13,
  CONNECTION_DENIED = 20
};

struct ChatMessage
{
  std::string text;
  std::string sender;
};
sf::Packet& operator <<(sf::Packet& packet, const ChatMessage& message);
sf::Packet& operator >>(sf::Packet& packet, ChatMessage& message);

struct StateMessage
{
  int state;
};
sf::Packet& operator <<(sf::Packet& packet, const StateMessage& message);
sf::Packet& operator >>(sf::Packet& packet, StateMessage& message);

struct ConnectionMessage
{
  bool gameRunning;
  std::vector<bool> characterAvailability = {true,true,true,true};
};
sf::Packet& operator <<(sf::Packet& packet, const ConnectionMessage& message);
sf::Packet& operator >>(sf::Packet& packet, ConnectionMessage& message);


struct CharacterChoosing
{
 int id;
};
sf::Packet& operator <<(sf::Packet& packet, const CharacterChoosing& message);
sf::Packet& operator >>(sf::Packet& packet, CharacterChoosing& message);

struct CharacterUpdatePacket {
  int characterID;
  sf::Vector2f newPosition;
  int state;
};
sf::Packet& operator <<(sf::Packet& packet, const CharacterUpdatePacket& message);
sf::Packet& operator >>(sf::Packet& packet, CharacterUpdatePacket& message);

struct OtherCharacters
{
  int id;
};
sf::Packet& operator <<(sf::Packet& packet, const OtherCharacters& message);
sf::Packet& operator >>(sf::Packet& packet, OtherCharacters& message);

struct NewConnection
{
  int localPort;
  std::string userName;
};
sf::Packet& operator <<(sf::Packet& packet, const NewConnection& message);
sf::Packet& operator >>(sf::Packet& packet, NewConnection& message);

struct UnavailableCharacter
{
  std::vector<bool> characterAvailability = {true,true,true,true};
};
sf::Packet& operator <<(sf::Packet& packet, const UnavailableCharacter& message);
sf::Packet& operator >>(sf::Packet& packet, UnavailableCharacter& message);

struct BombSpawnMessage
{
  sf::Vector2f  spawn_pos;
  int charID;
  float radius;
};
sf::Packet& operator <<(sf::Packet& packet, const struct BombSpawnMessage& message);
sf::Packet& operator >>(sf::Packet& packet, struct BombSpawnMessage& message);

struct PlayerKilledMessage
{
  int id;
};
sf::Packet& operator <<(sf::Packet& packet, const PlayerKilledMessage& message);
sf::Packet& operator >>(sf::Packet& packet, PlayerKilledMessage& message);

struct ItemSpawnedMessage
{
  int id;
  sf::Vector2f spawnPos;
  int itemType;
};
sf::Packet& operator <<(sf::Packet& packet, const ItemSpawnedMessage& message);
sf::Packet& operator >>(sf::Packet& packet, ItemSpawnedMessage& message);

struct ItemCollectedMessage
{
  int id;
};
sf::Packet& operator <<(sf::Packet& packet, const ItemCollectedMessage& message);
sf::Packet& operator >>(sf::Packet& packet, ItemCollectedMessage& message);



struct Disconnection
{
  std::string userName;
};
sf::Packet& operator <<(sf::Packet& packet, const Disconnection& message);
sf::Packet& operator >>(sf::Packet& packet, Disconnection& message);

struct ConnectionRequest
{
  bool connectionAllowed;
};
sf::Packet& operator <<(sf::Packet& packet, const ConnectionRequest& message);
sf::Packet& operator >>(sf::Packet& packet, ConnectionRequest& message);


#endif // SFMLGAME_CHATMESSAGE_H
