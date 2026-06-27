#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class Pipe {
public:
    Pipe(float startX, float gapY, float gapHeight, float width, float screenHeight);
    ~Pipe() = default;

    void Update(float dt);
    void Draw(sf::RenderWindow& window);
    
    bool IsOutOfBounds() const;
    bool HasPassed() const;
    void SetPassed();

    const sf::FloatRect GetTopBounds() const;
    const sf::FloatRect GetBottomBounds() const;

private:
    sf::RectangleShape _topPipe;
    sf::RectangleShape _bottomPipe;
    float _movementSpeed;
    bool _passed;
};
