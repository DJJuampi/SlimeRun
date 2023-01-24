
#include "SFML/Graphics.hpp"

using namespace sf;
using namespace std;

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Slime Runner");
    window.setFramerateLimit(60);

    
    
   


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close();
        }
        //Enemy Movement and sprite

        sf::RectangleShape rect;
        sf::Vector2f rectanglePosition(1280, 720 - 100);

        rect.setPosition(rectanglePosition);
        rect.setSize(sf::Vector2f(100, 100));
        
        // float yVelocity = 3; Possibly use to mak eenemy harder by moving up and down
        float xVelocity = -3;

        if (rectanglePosition.x < 0 || rectanglePosition.x > 1280 - 100)  rectanglePosition.x = 1280 - 100;

        rectanglePosition.x += xVelocity;
        rect.setPosition(rectanglePosition);

        //render
        window.clear();
        window.draw(rect);
        window.display();
    }



    return 0;
}