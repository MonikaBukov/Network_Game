//
// Created by monik on 23/10/2023.
//

#include "GameMenu.h"
#include <future>


GameMenu::GameMenu(sf::RenderWindow& window, Network* network, StateHandler& handler) : GameState(window), network(network), stateHandler(handler)
{
}
void GameMenu::createUserNameInput()
{
 userNameInput = std::make_unique<InputFieldUI>(window, font, 20, CustomColors::TxtBlue, CustomColors::BcktBlue, sf::Vector2f(35, 45), sf::Vector2f(30, 8), 10);
 textInputTittle.setFont(font);
 textInputTittle.setPosition((userNameInput->getPos().x),userNameInput->getPos().y - 50);
 textInputTittle.setCharacterSize(24);
 textInputTittle.setString("Please enter your name:");
}

bool GameMenu::init()
{
  /*
  clickBuffer.loadFromFile("Data/sounds/Text 1.wav");
  clickSound.setBuffer(clickBuffer);
  clickSound.setLoop(false);
  clickSound.setVolume(10);
   */
  std::string buttonFilePath = "Data/Images/ui/blue_button05.png";
  if(!font.loadFromFile("Data/Fonts/Font/kenvector_future.ttf")){std::cerr << "Failed to load font.";}
  createUserNameInput();
  joinButton = std::make_unique<ButtonUI>(
    font, 20, CustomColors::TxtBlue , buttonFilePath,
    "Join Game", sf::Vector2f(55, 45), sf::Vector2f(25, 10));
  hostButton = std::make_unique<ButtonUI>(
    font, 20, CustomColors::TxtBlue , buttonFilePath,
    "Host Game", sf::Vector2f(20, 45), sf::Vector2f(25, 10));
  hostButton->setIsEnabled(false);
  joinButton->setIsEnabled(false);
  cantJoinText =
    std::make_unique<CustomText>(font, 30, sf::Color::White, "Sorry the lobby is full right now");
  cantJoinText->setPosition(20, 20);
  cantJoinText->setIsEnabled(false);

  return true;
}
void GameMenu::update(float dt)
{
  if (network->getClient()->isCollectionAllowed())
  {
    stateHandler.setState(new GameLobby(window, network, stateHandler));
  }
}

void GameMenu::render()
{
  userNameInput->draw();
  hostButton->draw();
  joinButton->draw();
  cantJoinText->draw();
  if (userNameInput->getIsEnabled())
  {
    window.draw(textInputTittle);
  }
}
void GameMenu::mouseClicked(sf::Event event)
{
  // just a local IP as for public IP I would have to connect to a website which, and request the information, but it might not work on school computer or for other security reasons
  sf::IpAddress localAddress = network->localIP;
  if (joinButton->isSelected() && joinButton->getIsEnabled())
  {
   // clickSound.play();
    if (network->clientConnect(localAddress))
    {
      network->getClient()->setServerHost(false);
      if(!cantJoinText->getIsEnabled())
      {
        cantJoinText->setIsEnabled(true);
      }
    }
  }
  else if (hostButton->isSelected() && hostButton->getIsEnabled())
  {
   // clickSound.play();
    if (!network->serverCreate)
    {
      network->createServer();
      network->clientConnect(localAddress);
      network->getClient()->setServerHost(true);
      stateHandler.setState(new GameLobby(window, network, stateHandler));
      return;
    }
  }
}
void GameMenu::keyPressed(sf::Event event)
{
  if (event.type == sf::Event::KeyPressed)
  {
    if (event.key.code == sf::Keyboard::Enter)
    {
      if (userNameInput->getIsEnabled())
      {
        std::string newName;
        newName = userNameInput->getInputText();
        if (!newName.empty())
        {
          network->getClient()->setUserName(newName);
          userNameInput->setIsEnabled(false);
          hostButton->setIsEnabled(true);
          joinButton->setIsEnabled(true);
        }
      }
    }
  }
}

void GameMenu::textEntered(sf::Event event)
{
  userNameInput->handleEvent(event);
}
void GameMenu::mouseWheelScrolled(sf::Event event) {

}
void GameMenu::mouseMoved(sf::Event event) {
  //sf::Vector2i mousePos = sf::Mouse::getPosition(window);
  hostButton->onSelected(event);
  joinButton->onSelected(event);

}
