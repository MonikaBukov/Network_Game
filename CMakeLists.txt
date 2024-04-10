cmake_minimum_required(VERSION 3.14)
project(SFMLGame)

set(CMAKE_CXX_STANDARD 17)

if(WIN32)
    set(SFML_STATIC_LIBRARIES TRUE)
    set(CMAKE_EXE_LINKER_FLAGS "-static")
endif()

# set(CMAKE_PREFIX_PATH C:/)
find_package(SFML 2.5.1 COMPONENTS system window graphics network audio)

set(SOURCE_FILES src/main.cpp src/Game.cpp src/Game.h src/Networking/Server.cpp src/Networking/Server.h
        src/Networking/Client.cpp src/Networking/Client.h  src/Tmx/FreeFuncs.cpp src/Tmx/ImageLayer.cpp
        src/Tmx/LayerGroup.cpp src/Tmx/Map.cpp src/Tmx/miniz.c src/Tmx/miniz.h src/Tmx/Object.cpp src/Tmx/ObjectGroup.cpp
        src/Tmx/ObjectTypes.cpp src/Tmx/Property.cpp src/Tmx/TileLayer.cpp src/Tmx/Tileset.cpp src/Tmx/Tile.cpp src/Tmx/Tile.h
        src/Tmx/detail/pugiconfig.hpp src/Tmx/detail/pugixml.cpp src/Tmx/detail/pugixml.hpp src/GameStates/GameState.h src/GameStates/StateHandler.cpp src/GameStates/StateHandler.h src/GameStates/GameMenu.cpp src/GameStates/GameMenu.h src/GameStates/GamePlay.cpp src/GameStates/GamePlay.h src/GameWindow.h src/GameStates/GameLobby.cpp src/GameStates/GameLobby.h src/GameObjects/GameObject.cpp src/GameObjects/GameObject.h src/GameObjects/GameObjectFunctions/Collider.cpp src/GameObjects/GameObjectFunctions/Collider.h src/GameObjects/UI/UIElement.cpp src/GameObjects/UI/UIElement.h src/GameObjects/GameObjectFunctions/Animation.cpp src/GameObjects/GameObjectFunctions/Animation.h src/GameObjects/Player.cpp src/GameObjects/Player.h src/GameObjects/Character.cpp src/GameObjects/Character.h src/GameObjects/UI/InputFieldUI.cpp src/GameObjects/UI/InputFieldUI.h src/GameObjects/UI/ButtonUI.cpp src/GameObjects/UI/ButtonUI.h src/GameObjects/UI/ChatBoxUI.cpp src/GameObjects/UI/ChatBoxUI.h src/ChatMessage.h src/ChatMessage.cpp src/GameObjects/UI/CustomColours.h src/Networking/Network.cpp src/Networking/Network.h src/GameObjects/UI/CustomText.cpp src/GameObjects/UI/CustomText.h src/GameObjects/UI/BackgroundImage.cpp src/GameObjects/UI/BackgroundImage.h src/GameObjects/Bomb.cpp src/GameObjects/Bomb.h src/GameObjects/Item.cpp src/GameObjects/Item.h src/GameObjects/IItemConfig.h)
add_executable(SFMLGame ${SOURCE_FILES})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")

target_link_libraries (SFMLGame sfml-graphics sfml-window sfml-system sfml-network sfml-audio)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Data/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Data/)
