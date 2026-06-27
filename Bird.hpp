#pragma once

#include <SFML/Graphics.hpp>

class Bird {
public:
    Bird();
    ~Bird() = default;

    void Update(float dt);
    void Draw(sf::RenderWindow& window);
    void Tap();
    void Reset();

    const sf::FloatRect GetBounds() const;
    const sf::Vector2f& GetPosition() const;

private:
    sf::CircleShape _birdShape;
    float _velocity;
    float _gravity;
    float _jumpForce;
    float _startX;
    float _startY;
};
