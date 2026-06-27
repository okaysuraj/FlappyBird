cmake_minimum_required(VERSION 3.14)
project(FlappyBird VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Disable building SFML examples and docs to speed up the build
set(SFML_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(SFML_BUILD_DOC OFF CACHE BOOL "" FORCE)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.1
)
FetchContent_MakeAvailable(SFML)

add_executable(FlappyBird
    main.cpp
    Game.cpp
    Bird.cpp
    Pipe.cpp
    AssetManager.cpp
)

target_link_libraries(FlappyBird PRIVATE sfml-graphics sfml-window sfml-system sfml-audio)

# Workaround for UCRT missing __iob_func which is expected by precompiled extlibs in SFML (like libFLAC)
target_sources(sfml-audio PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/ucrt_workaround.cpp)

