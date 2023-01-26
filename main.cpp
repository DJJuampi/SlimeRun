
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
    player player1;
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

//Enemy sprites

    sf::Texture enemy1Texture;
    if (!enemy1Texture.loadFromFile("assets/enemy.png")) {
         std::cout<< "Could not load enemy texture";
         return 0;
       }
    sf::Sprite enemy1Sprite;
    enemy1Sprite.setTexture(enemy1Texture);

    sf::Texture enemy2Texture;
    if (!enemy2Texture.loadFromFile("assets/enemy2.png")) {
        std::cout << "Could not load enemy texture";
        return 0;
    }
    sf::Sprite enemy2Sprite;
    enemy2Sprite.setTexture(enemy2Texture);

    sf::Texture enemy3Texture;
    if (!enemy3Texture.loadFromFile("assets/enemy3.png")) {
        std::cout << "Could not load enemy texture";
        return 0;
    }
    sf::Sprite enemy3Sprite;
    enemy3Sprite.setTexture(enemy3Texture);
    
    enemy2Sprite.scale(sf::Vector2f(0.2, 0.2));
    enemy3Sprite.scale(sf::Vector2f(0.2, 0.2));

    sf::Vector2f enem1Position(1280, 620);
    sf::Vector2f enem2Position(1280, 320);
    sf::Vector2f enem3Position(1280, 120);

    enemy1Sprite.setPosition(enem1Position);
    enemy2Sprite.setPosition(enem2Position);
    enemy3Sprite.setPosition(enem3Position);
    
    //Attack Vfx
    sf::Texture AttackTextureBottom;
    sf::Sprite AttackSpriteBottom;
    if (!AttackTextureBottom.loadFromFile("assets/attackBottom.png")) {
        std::cout << "Could not load attack texture";
        return 0;
    };
    sf::Vector2f AttackPositionBottom(100, 320);
    AttackSpriteBottom.setTexture(AttackTextureBottom);
    AttackSpriteBottom.setPosition(AttackPositionBottom);
    
    sf::Texture AttackTextureTop;
    sf::Sprite AttackSpriteTop;
    if (!AttackTextureTop.loadFromFile("assets/attackTop.png")) {
        std::cout << "Could not load attack texture";
        return 0;
    };
    sf::Vector2f AttackPositionTop(100, 120);
    AttackSpriteTop.setTexture(AttackTextureTop);
    AttackSpriteTop.setPosition(AttackPositionTop);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close();

        }
        // Attacks against enemy 2 and 3
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
            if (player1.AttackBottom == true) {

            }
        };

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
            if (player1.AttackTop == true) {

            }
        };


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

        enem2Position.x += xVelocity;
        enemy2Sprite.setPosition(enem2Position);

        enem3Position.x += xVelocity;
        enemy3Sprite.setPosition(enem3Position);
        
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
        window.draw(AttackSpriteTop);
        window.draw(AttackSpriteBottom);
        window.draw(playerSprite);
        window.draw(enemy2Sprite);
        window.draw(enemy3Sprite);
        window.draw(enemy1Sprite);
        window.display();
    }



    return 0;
}