#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Bird.hpp"
#include "Pipe.hpp"
#include "AssetManager.hpp"

enum class GameState {
    Ready,
    Playing,
    GameOver
};

class Game {
public:
    Game(int width, int height, const std::string& title);
    ~Game() = default;

    void Run();

private:
    void ProcessEvents();
    void Update(float dt);
    void Draw();
    void SpawnPipe();
    void Reset();
    bool CheckCollision();

    sf::RenderWindow _window;
    AssetManager _assets;
    
    GameState _state;
    Bird _bird;
    std::vector<Pipe> _pipes;
    
    float _pipeSpawnTimer;
    float _pipeSpawnTime;
    int _score;

    sf::Text _scoreText;
    sf::Text _messageText;
    bool _fontLoaded;
};
