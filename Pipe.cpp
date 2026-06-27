#include "Pipe.hpp"

Pipe::Pipe(float startX, float gapY, float gapHeight, float width, float screenHeight) 
    : _movementSpeed(250.0f), _passed(false) {
    
    // Top Pipe
    _topPipe.setSize(sf::Vector2f(width, gapY));
    _topPipe.setPosition(startX, 0.0f);
    _topPipe.setFillColor(sf::Color::Green);
    _topPipe.setOutlineColor(sf::Color::Black);
    _topPipe.setOutlineThickness(2.0f);

    // Bottom Pipe
    float bottomY = gapY + gapHeight;
    _bottomPipe.setSize(sf::Vector2f(width, screenHeight - bottomY));
    _bottomPipe.setPosition(startX, bottomY);
    _bottomPipe.setFillColor(sf::Color::Green);
    _bottomPipe.setOutlineColor(sf::Color::Black);
    _bottomPipe.setOutlineThickness(2.0f);
}

void Pipe::Update(float dt) {
    _topPipe.move(-_movementSpeed * dt, 0.0f);
    _bottomPipe.move(-_movementSpeed * dt, 0.0f);
}

void Pipe::Draw(sf::RenderWindow& window) {
    window.draw(_topPipe);
    window.draw(_bottomPipe);
}

bool Pipe::IsOutOfBounds() const {
    return _topPipe.getPosition().x + _topPipe.getSize().x < 0;
}

bool Pipe::HasPassed() const {
    return _passed;
}

void Pipe::SetPassed() {
    _passed = true;
}

const sf::FloatRect Pipe::GetTopBounds() const {
    return _topPipe.getGlobalBounds();
}

const sf::FloatRect Pipe::GetBottomBounds() const {
    return _bottomPipe.getGlobalBounds();
}
