#include "Bird.hpp"

Bird::Bird() 
    : _velocity(0.0f), _gravity(1200.0f), _jumpForce(-400.0f), _startX(100.0f), _startY(300.0f) {
    _birdShape.setRadius(15.0f);
    _birdShape.setOrigin(15.0f, 15.0f);
    _birdShape.setFillColor(sf::Color::Yellow);
    _birdShape.setOutlineColor(sf::Color::White);
    _birdShape.setOutlineThickness(2.0f);
    Reset();
}

void Bird::Update(float dt) {
    _velocity += _gravity * dt;
    _birdShape.move(0.0f, _velocity * dt);

    // Optional: add a slight rotation based on velocity
    float angle = _velocity * 0.1f;
    if (angle > 90.0f) angle = 90.0f;
    if (angle < -25.0f) angle = -25.0f;
    _birdShape.setRotation(angle);
}

void Bird::Draw(sf::RenderWindow& window) {
    window.draw(_birdShape);
}

void Bird::Tap() {
    _velocity = _jumpForce;
}

void Bird::Reset() {
    _velocity = 0.0f;
    _birdShape.setPosition(_startX, _startY);
    _birdShape.setRotation(0.0f);
}

const sf::FloatRect Bird::GetBounds() const {
    return _birdShape.getGlobalBounds();
}

const sf::Vector2f& Bird::GetPosition() const {
    return _birdShape.getPosition();
}
