#include "Break.hpp"

Break::Break(sf::Vector2f size, sf::Vector2f position, int breakeLevel)
    : m_Size(size), m_Position(position), m_BreakLevel(breakeLevel)
{
    switch (breakeLevel)
    {
    case 1:
        m_Color = sf::Color::Red;
        break;
    case 2:
        m_Color = sf::Color::Magenta;
        break;

    default:
        break;
    }

    m_Shape = sf::RectangleShape(m_Size);
    m_Shape.setPosition(position);
    m_Shape.setFillColor(m_Color);
    helth = m_BreakLevel;
}

Break::~Break()
{
}

void Break::draw(sf::RenderTarget *target)
{
    target->draw(m_Shape);
}

bool Break::getDameg()
{
    helth -= 1;
    switch (helth)
    {
    case 1:
        m_Color = sf::Color::Red;
        break;
    case 2:
        m_Color = sf::Color::Magenta;
        break;

    default:
        break;
    }
    m_Shape.setFillColor(m_Color);
    return helth == 0 ? true : false;
}

CollideSide Break::isCollideWith(sf::CircleShape *ball)
{
    sf::FloatRect rightSide({m_Position.x + m_Size.x, m_Position.y, 0.5f, m_Size.y});
    sf::FloatRect leftSide({m_Position.x, m_Position.y, 0.5f, m_Size.y});

    sf::FloatRect upSide({m_Position.x, m_Position.y, m_Size.x, 0.5f});
    sf::FloatRect downSide({m_Position.x, m_Position.y + m_Size.y, m_Size.x, 0.5f});

    if (ball->getGlobalBounds().intersects(rightSide))
        return Right;
    else if (ball->getGlobalBounds().intersects(leftSide))
        return Left;
    else if (ball->getGlobalBounds().intersects(upSide))
        return Up;
    else if (ball->getGlobalBounds().intersects(downSide))
        return Down;

    return None;
}