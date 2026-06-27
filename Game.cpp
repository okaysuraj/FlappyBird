#include "Game.hpp"
#include <cstdlib>
#include <ctime>

Game::Game(int width, int height, const std::string& title) 
    : _window(sf::VideoMode(width, height), title), 
      _state(GameState::Ready),
      _pipeSpawnTimer(0.0f),
      _pipeSpawnTime(1.5f),
      _score(0),
      _fontLoaded(false) {
    
    _window.setFramerateLimit(60);
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    // Try to load a default font
    sf::Font font;
    if (font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf")) {
        _assets.LoadFont("arial", "C:\\Windows\\Fonts\\arial.ttf");
        _scoreText.setFont(_assets.GetFont("arial"));
        _scoreText.setCharacterSize(36);
        _scoreText.setFillColor(sf::Color::White);
        _scoreText.setPosition(width / 2.0f - 20.0f, 20.0f);
        
        _messageText.setFont(_assets.GetFont("arial"));
        _messageText.setCharacterSize(24);
        _messageText.setFillColor(sf::Color::White);
        _messageText.setPosition(width / 2.0f - 150.0f, height / 2.0f - 50.0f);
        _fontLoaded = true;
    }
}

void Game::Run() {
    sf::Clock clock;

    while (_window.isOpen()) {
        float dt = clock.restart().asSeconds();
        
        ProcessEvents();
        Update(dt);
        Draw();
    }
}

void Game::ProcessEvents() {
    sf::Event event;
    while (_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            _window.close();
        }

        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
            if (_state == GameState::Ready) {
                _state = GameState::Playing;
                _bird.Tap();
            } else if (_state == GameState::Playing) {
                _bird.Tap();
            } else if (_state == GameState::GameOver) {
                Reset();
                _state = GameState::Ready;
            }
        }

        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            if (_state == GameState::Ready) {
                _state = GameState::Playing;
                _bird.Tap();
            } else if (_state == GameState::Playing) {
                _bird.Tap();
            } else if (_state == GameState::GameOver) {
                Reset();
                _state = GameState::Ready;
            }
        }
    }
}

void Game::Update(float dt) {
    if (_state == GameState::Playing) {
        _bird.Update(dt);

        _pipeSpawnTimer += dt;
        if (_pipeSpawnTimer > _pipeSpawnTime) {
            SpawnPipe();
            _pipeSpawnTimer = 0.0f;
        }

        for (auto it = _pipes.begin(); it != _pipes.end();) {
            it->Update(dt);
            
            if (!it->HasPassed() && _bird.GetPosition().x > it->GetTopBounds().left + it->GetTopBounds().width) {
                it->SetPassed();
                _score++;
            }

            if (it->IsOutOfBounds()) {
                it = _pipes.erase(it);
            } else {
                ++it;
            }
        }

        if (CheckCollision()) {
            _state = GameState::GameOver;
        }
    }
    
    if (_fontLoaded) {
        _scoreText.setString(std::to_string(_score));
        
        if (_state == GameState::Ready) {
            _messageText.setString("Press SPACE or CLICK to start");
        } else if (_state == GameState::GameOver) {
            _messageText.setString("GAME OVER!\nPress SPACE to restart");
        }
    }
}

void Game::Draw() {
    _window.clear(sf::Color(135, 206, 235)); // Sky blue background

    for (auto& pipe : _pipes) {
        pipe.Draw(_window);
    }
    
    _bird.Draw(_window);

    if (_fontLoaded) {
        if (_state == GameState::Playing || _state == GameState::GameOver) {
            _window.draw(_scoreText);
        }
        if (_state == GameState::Ready || _state == GameState::GameOver) {
            _window.draw(_messageText);
        }
    }

    _window.display();
}

void Game::SpawnPipe() {
    float gapY = static_cast<float>(rand() % 300 + 50); // Random gap position between 50 and 350
    float gapHeight = 150.0f;
    float width = 60.0f;
    float startX = static_cast<float>(_window.getSize().x);
    float screenHeight = static_cast<float>(_window.getSize().y);

    _pipes.emplace_back(startX, gapY, gapHeight, width, screenHeight);
}

void Game::Reset() {
    _bird.Reset();
    _pipes.clear();
    _score = 0;
    _pipeSpawnTimer = 0.0f;
}

bool Game::CheckCollision() {
    const sf::FloatRect& birdBounds = _bird.GetBounds();

    // Check collision with ground/ceiling
    if (birdBounds.top < 0 || birdBounds.top + birdBounds.height > _window.getSize().y) {
        return true;
    }

    // Check collision with pipes
    for (const auto& pipe : _pipes) {
        if (birdBounds.intersects(pipe.GetTopBounds()) || birdBounds.intersects(pipe.GetBottomBounds())) {
            return true;
        }
    }

    return false;
}
