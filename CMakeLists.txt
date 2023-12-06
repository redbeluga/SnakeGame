cmake_minimum_required(VERSION 3.0.0)
project(Snake VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

set(SOURCES
  src/main.cpp

  src/gameobjects/GameObject.cpp
  src/gameobjects/SnakeObject.cpp
  src/gameobjects/AppleObject.cpp

  src/sprites/SpriteManager.cpp

  src/scenes/Scene.cpp
  src/scenes/GameScene.cpp
  src/scenes/EndScene.cpp
  src/scenes/MainMenuScene.cpp
  src/scenes/SceneManager.cpp

  src/fonts/FontManager.cpp
)

add_executable(Snake ${SOURCES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

find_package(SFML 2.6.0 COMPONENTS graphics window system REQUIRED)

target_link_libraries(Snake sfml-graphics sfml-window sfml-system)
target_include_directories(Snake PRIVATE ${SFML_INCLUDE_DIR})
target_include_directories(Snake PRIVATE include)
target_include_directories(Snake PRIVATE src)
target_link_directories(Snake PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -w")
