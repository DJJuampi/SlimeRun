
#include "SFML/Graphics.hpp"
#include <iostream>

using namespace sf;
using namespace std;

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Slime Runner");
    window.setFramerateLimit(60);

    //Enemy Movement and sprite

        sf::Texture enemy1Texture;
        if (!enemy1Texture.loadFromFile("assets/enemy.png")) {
            std::cout<< "Could not load enemy texture";
            return 0;
        }
    sf::Sprite enemy1Sprite;
    enemy1Sprite.setTexture(enemy1Texture);
    enemy1Sprite.scale(sf::Vector2f(0.2, 0.2));

    sf::RectangleShape rect;
    sf::Vector2f enem1Position(1280, 620);

    enemy1Sprite.setPosition(enem1Position);
    // enemy1Sprite.setSize(sf::Vector2f(100, 100));
    
   


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close();
        }
      
        
        // float yVelocity = 3; Possibly use to make enemy harder by moving up and down
        float xVelocity = -3;

        if (enem1Position.x < 0 || enem1Position.x > 1170)  enem1Position.x = 1170;

        enem1Position.x += xVelocity;
        enemy1Sprite.setPosition(enem1Position);

        //render
        window.clear();
        window.draw(enemy1Sprite);
        window.display();
    }



    return 0;
}