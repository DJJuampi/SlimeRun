
#include "SFML/Graphics.hpp"
#include <iostream>
#include <sstream>
#include <string>

template <typename T>
std::string toString(T arg)
{
    std::stringstream ss;
    ss << arg;
    return ss.str();
}
using namespace sf;
using namespace std;
class player {
public:
    int Points = 0;

    bool AttackTop = false;
    bool AttackBottom = false;
};
int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Slime Runner");
    window.setFramerateLimit(60);
//Player sprite
   
    float JumpVelocity = -10;
    bool AuthJump = false;
    bool descent = false;
    int cont = 0;

    sf::Texture playerTexture;
    if (!playerTexture.loadFromFile("assets/player.png")) {
        std::cout << "Could not load player texture";
        return 0;
    }
    sf::Sprite playerSprite;

    playerSprite.setTexture(playerTexture);
    playerSprite.scale(sf::Vector2f(0.2, 0.2));
    sf::Vector2f playerPosition(100, 620);
    playerSprite.setPosition(playerPosition);

//Enemy Movement and sprite

    sf::Texture enemy1Texture;
    if (!enemy1Texture.loadFromFile("assets/enemy.png")) {
         std::cout<< "Could not load enemy texture";
         return 0;
       }
    sf::Sprite enemy1Sprite;
    enemy1Sprite.setTexture(enemy1Texture);
    // enemy1Sprite.scale(sf::Vector2f(0.2, 0.2));

    sf::RectangleShape rect;
    sf::Vector2f enem1Position(1280, 620);

    enemy1Sprite.setPosition(enem1Position);
    
    player player1;


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close();

        }
        // Player jump
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            AuthJump = true;
        };

        if (AuthJump == true) {
                if (playerPosition.y > 450 && descent == false) {
                    playerPosition.y += JumpVelocity;
                    playerSprite.setPosition(playerPosition);
                    if (playerPosition.y <= 460) {
                        JumpVelocity = -4;
                    }
                }
                else if (playerPosition.y < 620) {
                    descent = true;
                    playerPosition.y -= JumpVelocity;
                    playerSprite.setPosition(playerPosition);
                    if (playerPosition.y >= 620) {
                        descent = false;
                        AuthJump = false;
                    }
                }
                if (descent == true && playerPosition.y >= 470) {
                    JumpVelocity = -8;
                }
        }

        // float yVelocity = 3; Possibly use to make enemy harder by moving up and down
        float xVelocity = -8;

        if (enem1Position.x < 0 || enem1Position.x > 1170)  enem1Position.x = 1170;

        enem1Position.x += xVelocity;
        enemy1Sprite.setPosition(enem1Position);
        
        //collision
        
        if (playerSprite.getGlobalBounds().intersects(enemy1Sprite.getGlobalBounds())) {
            return 0;
        }

        //Fonts and text
        sf::Font font;
        if (!font.loadFromFile("assets/font.ttf")) {
            std::cout << "Could not load font";
            return 0;
        }
       
        sf::Text text;
        sf::Text Points(toString<int>(player1.Points), font);

        text.setFont(font);
        text.setString("Puntaje: ");
        Points.setPosition(1, 28);

        //Point gain
        player1.Points = player1.Points + 1;

        //render
        window.clear();
        window.draw(text);
        window.draw(Points);
        window.draw(playerSprite);
        window.draw(enemy1Sprite);
        window.display();
    }



    return 0;
}