#include "SFML/Graphics.hpp"

#include "Break.hpp"
#include "CollideSide.hpp"

// TODO: move to palyer class and use sfml intersect
void collideWithBorder(sf::Vector2f *ballSpeed, sf::CircleShape *ball, sf::RenderWindow *window)
{
    sf::Vector2f position = ball->getPosition();
    sf::Vector2u windowSize = window->getSize();

    if (position.x + 12 >= windowSize.x)
        ballSpeed->x *= -1;
    if (position.x <= 0)
        ballSpeed->x *= -1;

    if (position.y + 12 >= windowSize.y)
        ballSpeed->y *= -1;
    if (position.y <= 0)
        ballSpeed->y *= -1;
}

void collideWithPaddel(sf::Vector2f *ballSpeed, sf::CircleShape *ball, sf::RectangleShape *paddel)
{
    if (ball->getGlobalBounds().intersects(paddel->getGlobalBounds()))
        ballSpeed->y *= -1;
}

void collideWithBreakes(sf::Vector2f *ballSpeed, sf::CircleShape *ball, std::vector<Break> *breaks)
{
    for (int i = 0; i < breaks->size(); i++)
    {
        bool collided = true;
        switch (breaks->at(i).isCollideWith(ball))
        {
        case Up:
            ballSpeed->y *= -1;
            break;
        case Down:
            ballSpeed->y *= -1;
            break;
        case Right:
            ballSpeed->x *= -1;
            break;
        case Left:
            ballSpeed->x *= -1;
            break;
        case None:
            collided = false;
            break;
        default:
            break;
        }
        if (collided)
        {
            if (breaks->at(i).getDameg())
                breaks->erase(breaks->begin() + i);
            return;
        }
    }
}

int main(int argc, char const *argv[])
{
    sf::RenderWindow window(sf::VideoMode(640, 640), "break out game");
    window.setFramerateLimit(60);

    sf::CircleShape ball(6);
    ball.setPosition({(float)(window.getSize().x / 2), (float)(window.getSize().y / 2)});
    sf::Vector2f ballSpeed{-2, -2};

    sf::RectangleShape paddle({150, 20});
    paddle.setPosition({(float)((window.getSize().x / 2) - 75), (float)(window.getSize().y - 50)});
    float paddleVX = 3, paddleVY = 0;

    sf::Vector2f breaksOffset{45, 50};
    sf::Vector2f braeakSize{50, 20};
    sf::Vector2f breakeOffsetAll{5, 5};

    std::vector<Break> breaks;

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            Break breaki(
                braeakSize,
                // TDDO: update with ely baly balk
                {breaksOffset.x + breakeOffsetAll.x + i * breakeOffsetAll.x + i * braeakSize.x,
                 breaksOffset.y + breakeOffsetAll.y + j * breakeOffsetAll.y + j * braeakSize.y},
                (i % 2 == 0) ? 1 : 2);
            breaks.push_back(breaki);
        }
    }

    sf::Clock deltaClock;
    bool inspector = true;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if (event.type == sf::Event::MouseMoved)
            {
                paddle.setPosition({(float)sf::Mouse::getPosition(window).x - 75, paddle.getPosition().y});
            }
        }
        sf::Vector2f ballPosition = ball.getPosition();
        collideWithBorder(&ballSpeed, &ball, &window);
        collideWithPaddel(&ballSpeed, &ball, &paddle);
        collideWithBreakes(&ballSpeed, &ball, &breaks);

        ball.setPosition({ballPosition.x + ballSpeed.x, ballPosition.y + ballSpeed.y});

        window.clear(sf::Color(51, 67, 67, 1.0));

        for (int i = 0; i < breaks.size(); i++)
            breaks[i].draw(&window);

        window.draw(ball);
        window.draw(paddle);


        window.display();
    }
    return 0;
}
