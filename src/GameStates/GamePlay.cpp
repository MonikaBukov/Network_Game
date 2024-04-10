//
// Created by monik on 23/10/2023.
//

#include "GamePlay.h"

#include <cmath>
#include <iostream>
#include <algorithm>
#include <tmxlite/Map.hpp>
#include <tmxlite/Layer.hpp>
#include <tmxlite/TileLayer.hpp>


void::GamePlay::increaseRadius(float radius)
{
  for(int i = 0; i <  network->getClient()->otherBombs.size(); i++)
  {
    if (playerCharacter->getPlayerCharacter()->getId() == i)
    {
      float newRadius = network->getClient()->otherBombs[i]->getRadius() * radius;
      network->getClient()->otherBombs[i]->setRadius(newRadius);
      network->getClient()->otherBombs[i]->GetObjSprite()->setOrigin(newRadius, newRadius);
    }
  }
}
void::GamePlay::increaseSpeed(int speed)
{
  int floatNewSpeed = playerCharacter->getPlayerCharacter()->getSpeed() + speed;
  playerCharacter->getPlayerCharacter()->setSpeed(floatNewSpeed);
}
void GamePlay::Map_Loading(const std::string& tmxPath, const std::string& imgPath,
                           std::unique_ptr<sf::Texture>& tileMap,
                           std::vector<std::vector<std::unique_ptr<Tile>>>& TILE_MAP,
                           float scale)
{
  tmx::Map map;
  if (!tileMap->loadFromFile(imgPath))
  {
    throw std::runtime_error("Failed to load spritesheet: " + imgPath);
  }
  if (!map.load(tmxPath))
  {
    throw std::runtime_error("Failed to load map data: " + tmxPath);
  }

  const unsigned int MAP_COLUMNS = map.getTileCount().x;
  const unsigned int MAP_ROWS = map.getTileCount().y;
  const auto& tile_size = map.getTileSize();

  TILE_MAP.reserve(map.getLayers().size());

  for (std::size_t layerIndex = 0; layerIndex < map.getLayers().size(); ++layerIndex)
  {
    TILE_MAP.emplace_back(std::vector<std::unique_ptr<Tile>>());
    const auto& tiles = map.getLayers()[layerIndex]->getLayerAs<tmx::TileLayer>().getTiles();
    TILE_MAP.back().reserve(tiles.size());

    for (const auto& tile : tiles)
    {
      SetTileWithID(tileMap, TILE_MAP, MAP_COLUMNS, MAP_ROWS, tile_size, tile, scale, layerIndex);
    }
  }
}

void GamePlay::SetTileWithID(std::unique_ptr<sf::Texture>& tileMap,
                             std::vector<std::vector<std::unique_ptr<Tile>>>& TILE_MAP,
                             const unsigned int MAP_COLUMNS, const unsigned int MAP_ROWS,
                             const tmx::Vector2u& tile_size, const tmx::TileLayer::Tile& tile,
                             float scale, std::size_t currentLayerIndex)
{
  int TILE_SIZE = 16;

  auto& current =
    *TILE_MAP[currentLayerIndex].emplace_back(std::make_unique<Tile>(tile.ID, *tileMap));

  if (current.GetID() == 0)
  {
    current.GetSpite()->setTextureRect(sf::IntRect(0, 0, 0, 0));
  }
  else
  {
    int idWithOffset = current.GetID() - 1;
    current.GetSpite()->setTextureRect(
      sf::IntRect((idWithOffset) % (tileMap->getSize().x /TILE_SIZE) * tile_size.x - tile_size.x *4,
                  (std::floor((idWithOffset) / (tileMap->getSize().y /TILE_SIZE) * tile_size.y)) - tile_size.y *6,
                  tile_size.x, tile_size.y));
  }

  current.GetSpite()->setScale(scale, scale);
  current.GetSpite()->setPosition(((TILE_MAP[currentLayerIndex].size() - 1) % MAP_COLUMNS) * (tile_size.x * scale),
                                  ((TILE_MAP[currentLayerIndex].size() - 1) / MAP_COLUMNS) * (tile_size.y * scale));
}

void GamePlay::DrawMap(std::vector<std::vector<std::unique_ptr<Tile>>>& TILE_MAP)
{
  for (const auto& layer: TILE_MAP)
  {
    for (const auto& tile: layer)
    {
      if(tile->GetID() != 0)
      {
        window.draw(*tile->GetSpite());
      }
    }
  }
}
void GamePlay::innitBombs()
{
    for (int i = 0; i < 5; ++i) {
      auto newBomb = std::make_unique<Bomb>();
      newBomb->innitBomb("Data/Images/objects/ezgif.com-gif-maker.png");
      network->getClient()->otherBombs.push_back(std::move(newBomb));
    }
  }

void GamePlay::innitCharacters()
{
  characters.clear();
  network->getClient()->otherCharacters.clear();
  network->getClient()->otherBombs.clear();
  tombTexture = std::make_unique<sf::Texture>();
  speedItemTxt = std::make_unique<sf::Texture>();
  powerItemTxt = std::make_unique<sf::Texture>();
  speedItemTxt->loadFromFile("Data/Images/speedicon.png");
  powerItemTxt->loadFromFile("Data/Images/fire.png");
  bird = std::make_unique<Character>();
  racoon = std::make_unique<Character>();
  fox = std::make_unique<Character>();
  cat = std::make_unique<Character>();
  bird->innitCharacter(0, "Data/Images/characters/BIRDSPRITESHEET.png", sf::Vector2f (100,100),Character::RIGHT);
  racoon->innitCharacter(1, "Data/Images/characters/RACCOONSPRITESHEET.png", sf::Vector2f (window.getSize().x - 140,100),Character::LEFT);
  fox->innitCharacter(2, "Data/Images/characters/FOXSPRITESHEET.png", sf::Vector2f (window.getSize().x - 140,window.getSize().y - 140),Character::LEFT);
  cat->innitCharacter(3, "Data/Images/characters/CATSPRITESHEET.png", sf::Vector2f (100,window.getSize().y - 140),Character::RIGHT);
  bird->setDead(false);
  cat->setDead(false);fox->setDead(false);racoon->setDead(false);
  characters.push_back(std::move(bird));
  characters.push_back(std::move(cat));
  characters.push_back(std::move(fox));
  characters.push_back(std::move(racoon));
  tombTexture->loadFromFile("Data/Images/objects/tombstone.png");
}
void GamePlay::distributeCharacters()
{
  std::vector<int> otherPlayersList;
  otherPlayersList = network->getClient()->getOtherPlayers();
  playerCharacter = std::make_unique<Player>();
  int playerID = network->getClient()->getCharacterId();
  playerCharacter->assignCharacter(std::move(characters[playerID]));
  otherPlayersList.erase(
    std::remove(otherPlayersList.begin(), otherPlayersList.end(), playerID),
    otherPlayersList.end());
  for (int num : otherPlayersList)
  {
    network->getClient()->otherCharacters.push_back(std::move(characters[num]));
  }
}
void GamePlay::handleOwnCharacter(float dt)
{
  playerCharacter->changeDirection(dt);
  playerCharacter->getPlayerCharacter()->handleAnim(dt);
  playerCharacter->move(dt);
  for (const auto& tile : TILE_MAP_FlOOR[1])
  {
    if (playerCharacter->getPlayerCharacter()->getBoundsWithOffset().intersects(
          tile->GetSpite()->getGlobalBounds()))
    {
      playerCharacter->resetVellocity();
      playerCharacter->getPlayerCharacter()->GetObjSprite()->setPosition(
        playerCharacter->getPrevPos());
    }
  }
  for (const auto& tile : TILE_MAP_FlOOR[2])
  {
    if (playerCharacter->getPlayerCharacter()->getBoundsWithOffset().intersects(
          tile->GetSpite()->getGlobalBounds()))
    {
      playerCharacter->resetVellocity();
      playerCharacter->getPlayerCharacter()->GetObjSprite()->setPosition(
        playerCharacter->getPrevPos());
    }
  }
  handlePlayerExploding();
  handleItems();
}

void GamePlay::handleItems()
{
  for (const auto& item : network->getClient()->items)
  {
    if (
      item->isEnabled() &&
      playerCharacter->getPlayerCharacter()->getBoundsWithOffset().intersects(
        item->GetSpite()->getGlobalBounds()))
    {
      //itemSound.play();
      item->collect(this);
      item->setEnabled(false);
      ItemCollectedMessage msg;
      msg.id = item->getId();
      network->getClient()->sendItemCollectedMessage(msg);
    }
  }
  for (const auto& item : network->getClient()->items)
  {
    if (!item->isEnabled())
    {
      ItemCollectedMessage msg;
      msg.id = item->getId();
      network->getClient()->sendItemCollectedMessage(msg);
    }
  }
}
void GamePlay::handlePlayerExploding()
{
  for (const auto& bomb : network->getClient()->otherBombs)
  {
    if (
      bomb->isExploding() &&
      (playerCharacter->getPlayerCharacter()->getBoundsWithOffset().intersects(
        bomb->GetObjSprite()->getGlobalBounds())))
    {
      //bombSound.play();
      playerCharacter->getPlayerCharacter()->GetObjSprite()->setTexture(
        *tombTexture);
      playerCharacter->getPlayerCharacter()->setDead(true);
      looseText->setIsEnabled(true);
      PlayerKilledMessage msg;
      msg.id = playerCharacter->getPlayerCharacter()->getId();
      network->getClient()->sendPlayerDiedMsg(msg);
    }
  }
}
void GamePlay::handleOtherCharacters(float dt)
{
  for (const auto& character : network->getClient()->otherCharacters)
  {
    character->handleAnim(dt);
    character->updateInterpolation(dt);
    if (character->isDead())
    {
      if (!character->isTextureChanged())
      {
        character->GetObjSprite()->setTexture(*tombTexture);
        character->setTextureChanged(true);
      }
    }
  }
  bool isDead = true;
  for (const auto& character : network->getClient()->otherCharacters)
  {
    isDead &= character->isDead();
  }
  if (isDead)
  {
    winText->setIsEnabled(true);
    backToLobbyButton->setIsEnabled(true);
  }
}

void GamePlay::handleBombs(float dt)
{
  for (const auto& bomb : network->getClient()->otherBombs)
  {
    bomb->spawnBomb(dt);
  }
}

void GamePlay::handleExplodingTiles(float dt)
{
  for (const auto& tile : TILE_MAP_FlOOR[2])
  {
    for (const auto& bomb : network->getClient()->otherBombs)
    {
      if (
        bomb->isExploding() &&
        (tile->GetSpite()->getGlobalBounds().intersects(
          bomb->GetObjSprite()->getGlobalBounds())))
      {
        if(shouldGenerateItem())
        {
          generateItem(tile->GetSpite()->getPosition());
        }
        //bombSound.play();
        tile->GetSpite()->setTextureRect(sf::IntRect (0,0,0,0));
        tile->GetSpite()->setPosition(0,0);
      }
    }
  }
}
bool GamePlay::shouldGenerateItem()
{
  if (itemGenerationTimer.getElapsedTime().asSeconds() >= 1.0f)
  {
    itemGenerationTimer.restart();
    return (rand() % 10) == 0;
  }
  return false;
}
void GamePlay::generateItem(sf::Vector2f newPos)
{
  itemID ++;
  int itemType;
  if (rand() % 2 == 0)
  {
     itemType = 1;
  }
  else
  {
     itemType = 2;
  }
  ItemSpawnedMessage newItemMsg;
  newItemMsg.spawnPos = newPos;
  newItemMsg.id = itemID;
  newItemMsg.itemType = itemType;
  network->getClient()->sendItemSpawnedMessage(newItemMsg);
}

void GamePlay::sendCharacterUpdate()
{
  //limiting how often to send packet
  if (updateTimer.getElapsedTime() >= sf::seconds(0.02f))
  {
    sf::Vector2f charPos =
      playerCharacter->getPlayerCharacter()->GetObjSprite()->getPosition();
    int playerState = playerCharacter->getPlayerCharacter()->getDirection();
    int id          = playerCharacter->getPlayerCharacter()->getId();
    CharacterUpdatePacket playerUpdate;
    playerUpdate.newPosition = charPos;
    playerUpdate.characterID = id;
    playerUpdate.state       = playerState;
    network->getClient()->sendPlayerUpdate2(playerUpdate);
    updateTimer.restart();
  }
}

void GamePlay::innitSounds()
{
  /*buffer.loadFromFile("Data/sounds/2019-01-02_-_8_Bit_Menu_-_David_Renda_-_FesliyanStudios.com.wav");
  sound.setBuffer(buffer);
  sound.setLoop(true);
  sound.setVolume(10);
  sound.play();
  bombBuffer.loadFromFile("Data/sounds/Hit damage 1.wav");
  bombSound.setBuffer(bombBuffer);
  bombSound.setLoop(false);
  bombSound.setVolume(10);
  itemBuffer.loadFromFile("Data/sounds/Select 1.wav");
  itemSound.setBuffer(itemBuffer);
  itemSound.setLoop(false);
  itemSound.setVolume(10);
   */
}
GamePlay::GamePlay(sf::RenderWindow& window, Network* network, StateHandler& handler) : GameState(window), network(network), stateHandler(handler)
{


}


bool GamePlay::init()
{
  innitSounds();
  Map_Loading("Data/new tilemap/tile_map.tmx", "Data/new tilemap/tilemap_packed.png", tileMapFloor, TILE_MAP_FlOOR, 3);
  innitCharacters();
  distributeCharacters();
  innitBombs();
  font.loadFromFile("Data/Fonts/Font/kenvector_future.ttf");
  backToLobbyButton = std::make_unique<ButtonUI>(
    font, 20, CustomColors::TxtBlue , "Data/Images/ui/blue_button05.png",
    "Back to lobby", sf::Vector2f(40, 45), sf::Vector2f(25, 10));
  backToLobbyButton->setIsEnabled(false);
  winText =
    std::make_unique<CustomText>(font, 30, sf::Color::Green, "You won");
  winText->setPosition(window.getSize().x/2 - winText->getGlobalBounds().width/2, 49);
  winText->setIsEnabled(false);
  looseText =
    std::make_unique<CustomText>(font, 30, sf::Color::Red, "You lost please \n wait for the game to end");
  looseText->setPosition(window.getSize().x/2 - looseText->getGlobalBounds().width/2, 49);
  looseText->setIsEnabled(false);
  return true;
}

void GamePlay::update(float dt)
{
  handleExplodingTiles(dt);
  handleOwnCharacter(dt);
  sendCharacterUpdate();
  handleOtherCharacters(dt);
  handleBombs(dt);

  if (network->getClient()->isNewItemSpawned())
  {
    for (auto& item : network->getClient()->items)
    {
      std:: cout << item->type << "item type \n";
      if (item->type == 1)
      {
        item->GetSpite()->setTexture(*speedItemTxt);
        item->GetSpite()->setScale(0.1, 0.1);
      }
      else
      {
        item->GetSpite()->setTexture(*powerItemTxt);
        item->GetSpite()->setScale(0.04, 0.04);
      }
    }
    network->getClient()->setNewItemSpawned(false);
  }
}
void GamePlay::mouseClicked(sf::Event event) {
  if (backToLobbyButton->isSelected() && backToLobbyButton->getIsEnabled())
  {
      //sound.stop();
      StateMessage newSate;
      newSate.state = 1;
      network->getClient()->sendSateMessage(newSate);
      return;
  }
}

void GamePlay::keyPressed(sf::Event event)
{
  if (event.key.code == sf::Keyboard::Space)
  {
    sf::Vector2f spawnPos =
      playerCharacter->getPlayerCharacter()->GetObjSprite()->getPosition();
    BombSpawnMessage msg;
    msg.spawn_pos = spawnPos;
    msg.charID    = playerCharacter->getPlayerCharacter()->getId();
    for (int i = 0; i < network->getClient()->otherBombs.size(); i++)
    {
      if (playerCharacter->getPlayerCharacter()->getId() == i)
      {
        msg.radius = network->getClient()->otherBombs[i]->getRadius();
      }
    }
    sf::Packet bombMsg;
    bombMsg << msg;
    network->getClient()->sendBombSpawnMessage(msg);
  }
}

void GamePlay::render()
{
  window.clear(sf::Color::Black);
  DrawMap(TILE_MAP_FlOOR);
  playerCharacter->getPlayerCharacter()->drawObject();
  for (const auto& players : network->getClient()->otherCharacters)
  {
    players->drawObject();
  }
  for (const auto& bomb : network->getClient()->otherBombs)
  {
    bomb->draw();
  }
  looseText->draw();
  winText->draw();
  backToLobbyButton->draw();
  for (const auto& item : network->getClient()->items)
  {
    window.draw(*item->GetSpite());
  }
}
void GamePlay::textEntered(sf::Event event) {}
void GamePlay::mouseWheelScrolled(sf::Event event) {}
void GamePlay::mouseMoved(sf::Event event)
{
  backToLobbyButton->onSelected(event);
}
