#pragma once
#include "SFML/Graphics.hpp"
#include "CollideSide.hpp"

class Break
{
public:
    sf::Vector2f m_Size;
    sf::Vector2f m_Position;
    sf::Color m_Color;
    sf::RectangleShape m_Shape;
    int m_BreakLevel;
    int helth;

public:
    Break(sf::Vector2f size, sf::Vector2f position, int breakeLevel);
    ~Break();

    void draw(sf::RenderTarget *target);
    bool getDameg();
    CollideSide isCollideWith(sf::CircleShape *ball);
};