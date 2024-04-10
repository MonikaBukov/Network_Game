//
// Created by monik on 23/10/2023.
//

#ifndef SFMLGAME_GAMEPLAY_H
#define SFMLGAME_GAMEPLAY_H
#include "../GameObjects/Bomb.h"
#include "../GameObjects/Character.h"
#include "../GameObjects/IItemConfig.h"
#include "../GameObjects/Player.h"
#include "../GameObjects/UI/ButtonUI.h"
#include "../GameObjects/UI/CustomText.h"
#include "../Tmx/Tile.h"
#include "GameState.h"
#include "StateHandler.h"
#include "tmxlite/Map.hpp"
#include "tmxlite/TileLayer.hpp"

class GamePlay : public GameState, public IItemConfig
{
 public:
  GamePlay(sf::RenderWindow& window,Network* network, StateHandler& handler);
  std::unique_ptr<sf::Texture> tileMapFloor =  std::make_unique<sf::Texture>();
  std::vector<std::vector<std::unique_ptr<Tile>>> TILE_MAP_FlOOR;
  std::unique_ptr<sf::Texture> tileMapWall =  std::make_unique<sf::Texture>();
  std::vector<std::vector<std::unique_ptr<Tile>>> TILE_MAP_Wall;
  std::vector<std::unique_ptr<Character>> characters;
   bool init()override;
   void update(float dt);
   sf::Clock updateTimer;
   sf::Clock itemGenerationTimer;
   void render() override;
   void mouseClicked(sf::Event event) override;
   void keyPressed(sf::Event event) override;
   void textEntered(sf::Event event) override;
   void mouseWheelScrolled(sf::Event event) override;
   void mouseMoved(sf::Event event) override;
   void increaseSpeed(int speed) override;
   void increaseRadius(float radius) override;

   //tile map
   void Map_Loading(const std::string& tmxPath, const std::string& imgPath,
                    std::unique_ptr<sf::Texture>& tileMap,
                    std::vector<std::vector<std::unique_ptr<Tile>>>& TILE_MAP,
                    float scale);
   void DrawMap(std::vector<std::vector<std::unique_ptr<Tile>>>& TILE_MAP);
   void SetTileWithID(std::unique_ptr<sf::Texture>& tileMap,
                      std::vector<std::vector<std::unique_ptr<Tile>>>& TILE_MAP,
                      const unsigned int MAP_COLUMNS, const unsigned int MAP_ROWS,
                      const tmx::Vector2u& tile_size, const tmx::TileLayer::Tile& tile,
                      float scale, std::size_t currentLayerIndex);
   // other functions
  StateHandler&  stateHandler;
  Network* network;
  void innitCharacters();
  void distributeCharacters();
  void sendCharacterUpdate();
  void handleOwnCharacter(float dt);
  void handleOtherCharacters(float dt);
  void innitBombs();
  void handleBombs(float dt);
  void handleExplodingTiles(float dt);

 private:
  // game play variables
  std::unique_ptr<Character> bird;
  std::unique_ptr<Character> cat;
  std::unique_ptr<Character> fox;
  std::unique_ptr<Character> racoon;
  std::unique_ptr<Player> playerCharacter;
  std::unique_ptr<sf::Texture>  tombTexture;
  std::unique_ptr<sf::Texture>  speedItemTxt;
  std::unique_ptr<sf::Texture>  powerItemTxt;

 /* sf::SoundBuffer buffer;
  sf::Sound sound;
  sf::SoundBuffer bombBuffer;
  sf::Sound bombSound;
  sf::SoundBuffer itemBuffer;
  sf::Sound itemSound;
  */

  int itemID = 0;

  //ui variables

  sf::Font font;
  std::unique_ptr<ButtonUI> backToLobbyButton;
  std::unique_ptr<CustomText> winText;
  std::unique_ptr<CustomText> looseText;


  bool shouldGenerateItem();
  void generateItem(sf::Vector2f newPos);
  void handleItems();
  void handlePlayerExploding();
  void innitSounds();
};

#endif // SFMLGAME_GAMEPLAY_H
