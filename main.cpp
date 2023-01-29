
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
    int MaxJumpHeight;
    sf::Vector2f Pos;
    player(sf::Vector2f y, int x);

    bool AttackTop = false;
    bool AttackBottom = false;

    bool FirstAttack = false;
    bool SecondAttack = false;

};
player::player(sf::Vector2f y, int x) {
    Pos = y;
    MaxJumpHeight = x;
};
class Timer {
public:
    int Stop;
    int Time;
    Timer(int y, int x);
};
Timer::Timer(int y, int x) {
    Stop = y;
    Time = x;
};


class Animation {
public:
    Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime);


    void Update(int row, float deltatime);
    sf::IntRect uvRect;

private:
    sf::Vector2u imageCount;
    sf::Vector2u currentImage;

    float totalTime;
    float switchTime;
};


Animation::Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime) 
{
    this->imageCount = imageCount;
    this->switchTime = switchTime;
    totalTime = 0.0f;
    currentImage.x = 0;

    uvRect.width = texture->getSize().x / float(imageCount.x);
    uvRect.height = texture->getSize().y / float(imageCount.y);
};


void Animation::Update(int row, float deltatime) {
    currentImage.y = row;
    totalTime += deltatime;

    if (totalTime >= switchTime) {
        totalTime -= switchTime;
        currentImage.x++;

        if (currentImage.x >= imageCount.x) {
            currentImage.x = 0;
        };
    };

    uvRect.left = currentImage.x * uvRect.width;
    uvRect.top = currentImage.y * uvRect.height;
}


int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Slime Runner");
    window.setFramerateLimit(60);
    srand(time(NULL));

 //Timers

    Timer AtkBot(0, 29), AtkTop(0,29), AtkBotCooldown(0, 100), AtkTopCooldown(0, 100);
    bool AtkBotOnCooldown = false;
    bool AtkTopOnCooldown = false;
    int KilledSomething = false;

//Animations variables
    float deltatime = 0.0f;
    sf::Clock clock;

//Player sprites
    player player1 (sf::Vector2f(100, 600), 350);
    float JumpVelocity = -10;
    bool AuthJump = false;
    bool descent = false;
    int cont = 0;
    int JumpStartPos = player1.Pos.y;
   
    sf::Texture playerTexture1;
    if (!playerTexture1.loadFromFile("assets/player_walk_animation_1.png")) {
        std::cout << "Could not load player texture";
        return 0;
    }
    Animation playerRun1(&playerTexture1, sf::Vector2u(5, 1), 0.1f);
    sf::Sprite playerSprite1;

    playerSprite1.setTexture(playerTexture1);
    playerSprite1.scale(sf::Vector2f(5, 5));
    playerSprite1.setPosition(player1.Pos);



    sf::Texture playerTexture2;
    if (!playerTexture2.loadFromFile("assets/player_walk_animation_2.png")) {
        std::cout << "Could not load player texture";
        return 0;
    }
    Animation playerRun2(&playerTexture2, sf::Vector2u(6, 1), 0.1f);
    sf::Sprite playerSprite2;

    playerSprite2.setTexture(playerTexture2);
    playerSprite2.scale(sf::Vector2f(5, 5));
    playerSprite2.setPosition(player1.Pos);



    sf::Texture playerTexture3;
    if (!playerTexture3.loadFromFile("assets/player_walk_animation_3.png")) {
        std::cout << "Could not load player texture";
        return 0;
    }
    Animation playerRun3(&playerTexture3, sf::Vector2u(6, 1), 0.1f);
    sf::Sprite playerSprite3;

    playerSprite3.setTexture(playerTexture3);
    playerSprite3.scale(sf::Vector2f(5, 5));
    playerSprite3.setPosition(player1.Pos);

// Music and sound effects


//Enemy sprites

    sf::Texture enemy1Texture;
    if (!enemy1Texture.loadFromFile("assets/enemy.png")) {
         std::cout<< "Could not load enemy texture";
         return 0;
       }
    Animation enem1run(&enemy1Texture, sf::Vector2u(4, 1), 0.2f);
    sf::Sprite enemy1Sprite;
    enemy1Sprite.setTexture(enemy1Texture);

    sf::Texture enemy2Texture;
    if (!enemy2Texture.loadFromFile("assets/enemy2.png")) {
        std::cout << "Could not load enemy texture";
        return 0;
    }
    Animation enem2run(&enemy2Texture, sf::Vector2u(4, 1), 0.2f);
    sf::Sprite enemy2Sprite;
    enemy2Sprite.setTexture(enemy2Texture);

    sf::Texture enemy3Texture;
    if (!enemy3Texture.loadFromFile("assets/enemy3.png")) {
        std::cout << "Could not load enemy texture";
        return 0;
    }
    Animation enem3run(&enemy3Texture, sf::Vector2u(4, 1), 0.2f);
    sf::Sprite enemy3Sprite;
    enemy3Sprite.setTexture(enemy3Texture);
    
    enemy1Sprite.scale(sf::Vector2f(5, 5));
    enemy2Sprite.scale(sf::Vector2f(8, 8));
    enemy3Sprite.scale(sf::Vector2f(8, 8));

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
    Animation attackBottomVfx(&AttackTextureBottom, sf::Vector2u(6, 1), 0.1f);
    sf::Vector2f AttackPositionBottom(3000, 320);
    AttackSpriteBottom.setTexture(AttackTextureBottom);
    AttackSpriteBottom.setPosition(AttackPositionBottom);
    AttackSpriteBottom.scale(sf::Vector2f(8, 8));
    
    sf::Texture AttackTextureTop;
    sf::Sprite AttackSpriteTop;
    if (!AttackTextureTop.loadFromFile("assets/attackTop.png")) {
        std::cout << "Could not load attack texture";
        return 0;
    };
    Animation attackTopVfx(&AttackTextureTop, sf::Vector2u(6, 1), 0.1f);
    sf::Vector2f AttackPositionTop(3000, 120);
    AttackSpriteTop.setTexture(AttackTextureTop);
    AttackSpriteTop.setPosition(AttackPositionTop);
    AttackSpriteTop.scale(sf::Vector2f(8, 8));
    //Background

    sf::Texture Background1Texture;
    sf::Texture Background2Texture;
    if (!Background1Texture.loadFromFile("assets/forest_background.png") || !Background2Texture.loadFromFile("assets/forest_background.png")) {
        std::cout << "Could not load forest background texture";
        return 0;
    };
    sf::Sprite Background1Sprite;
    sf::Sprite Background2Sprite;
    sf::Vector2f Background1Position(0, 0);
    sf::Vector2f Background2Position(2000, 0);
    
    Background1Sprite.scale(sf::Vector2f(1.6, 1.6));
    Background1Sprite.setTexture(Background1Texture);
    Background1Sprite.setPosition(Background1Position);

    Background2Sprite.scale(sf::Vector2f(1.6, 1.6));
    Background2Sprite.setTexture(Background2Texture);
    Background2Sprite.setPosition(Background2Position);
    
    sf::Texture BackgroundCityTexture;
    sf::Sprite BackgroundCitySprite;
    if (!BackgroundCityTexture.loadFromFile("assets/city_background.png")) {
        std::cout << "Could not load city background texture";
        return 0;
    };
    sf::Vector2f BackgroundCityPosition(0, -1000);
    BackgroundCitySprite.scale(sf::Vector2f(1.8, 1.8));
    BackgroundCitySprite.setTexture(BackgroundCityTexture);
    BackgroundCitySprite.setPosition(BackgroundCityPosition);

    float xVelocity1 = -8;
    float xVelocity2 = -8;
    float xVelocity3 = -8;
    float ScollSpeed = -2;
    float ScrollSpeed2 = -0.2;

    while (window.isOpen())
    {
        deltatime = clock.restart().asSeconds();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close();

        }

        // Attacks against enemy 2 and 3
        if (AtkBot.Stop == 0) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
                player1.AttackBottom = true;
            }
        }
        if (AtkTop.Stop == 0) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
                player1.AttackTop = true;

            }
        };

     // Player jump
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            AuthJump = true;
        };

        if (AuthJump == true) {
            if (player1.Pos.y > player1.MaxJumpHeight && descent == false) {
                player1.Pos.y += JumpVelocity;
                playerSprite1.setPosition(player1.Pos);
                playerSprite2.setPosition(player1.Pos);
                playerSprite3.setPosition(player1.Pos);
                if (player1.Pos.y <= player1.MaxJumpHeight) {
                    JumpVelocity = -4;
                }
            }
            else if (player1.Pos.y < JumpStartPos) {
                descent = true;
                player1.Pos.y -= JumpVelocity;
                playerSprite1.setPosition(player1.Pos);
                playerSprite2.setPosition(player1.Pos);
                playerSprite3.setPosition(player1.Pos);
                if (player1.Pos.y >= JumpStartPos) {
                    descent = false;
                    AuthJump = false;
                }
            }
            if (descent == true && player1.Pos.y >= player1.MaxJumpHeight - 20) {
                JumpVelocity = -8;
            }
        }

       

     //Looping behaviour
        if (enem1Position.x < -200 || enem1Position.x > 1370) {
            enem1Position.x = 1370;
           xVelocity1 = rand() % 15 + 9;
           xVelocity1 *= -1;
        }
        if (Background1Position.x < -2400) {
            Background1Position.x = 1896;
        }
        if (Background2Position.x < -2400) {
            Background2Position.x = 1896;
        }
        if (enem2Position.x < -200 || enem2Position.x > 1370)  return 0;
        if (enem3Position.x < -200 || enem3Position.x > 1370)  return 0;

        enem1Position.x += xVelocity1;
        enemy1Sprite.setPosition(enem1Position);
        
        Background1Position.x += ScollSpeed;
        Background1Sprite.setPosition(Background1Position);
        Background2Position.x += ScollSpeed;
        Background2Sprite.setPosition(Background2Position);
        BackgroundCityPosition.x += ScrollSpeed2;
        BackgroundCitySprite.setPosition(BackgroundCityPosition);



        if (player1.FirstAttack == true) {
            enem2Position.x += xVelocity2;
            enemy2Sprite.setPosition(enem2Position);
           
        }
        if (player1.SecondAttack == true) {
            enem3Position.x += xVelocity3;
            enemy3Sprite.setPosition(enem3Position);
            
        }

     //collision
        
        if (playerSprite1.getGlobalBounds().intersects(enemy1Sprite.getGlobalBounds())) {
            
        }
        if (AttackSpriteBottom.getGlobalBounds().intersects(enemy2Sprite.getGlobalBounds())) {
            enem2Position.x = 1370;
            xVelocity2 = rand() % 20 + 1;
            xVelocity2 *= -1;
        }
        if (AttackSpriteTop.getGlobalBounds().intersects(enemy3Sprite.getGlobalBounds())) {
            enem3Position.x = 1370;
            xVelocity3 = rand() % 30 + 1;
            xVelocity3 *= -1;
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
       
     //Release of other enemies
        if (player1.Points >= 300 && player1.FirstAttack == false) {
            player1.FirstAttack = true;
            JumpStartPos = JumpStartPos - 25;
        }
        if (player1.Points >= 600 && player1.FirstAttack == false) {
            player1.SecondAttack = true;
            JumpStartPos = JumpStartPos - 50;
        }
       
     //render
        window.clear();
        window.draw(BackgroundCitySprite);
        window.draw(Background1Sprite);
        window.draw(Background2Sprite);
       
     // Timer for the bottom attack and cooldown
    


        if (player1.AttackBottom == true && AtkBot.Stop <= AtkBot.Time && player1.FirstAttack == true && AtkBotOnCooldown == false) {
            AtkBot.Stop = AtkBot.Stop + 1;
            AttackSpriteBottom.setPosition(100, 320);
            window.draw(AttackSpriteBottom);
            attackBottomVfx.Update(0, deltatime);
            AttackSpriteBottom.setTextureRect(attackBottomVfx.uvRect);
           

            if (AttackSpriteBottom.getGlobalBounds().intersects(enemy2Sprite.getGlobalBounds())) {
                player1.Points = player1.Points + 500;
                KilledSomething = true;
            }
        }
        if (AtkBot.Stop >= AtkBot.Time) {
            player1.AttackBottom = false;
            AtkBot.Stop = 0;
            AttackSpriteBottom.setPosition(AttackPositionBottom);
                if(KilledSomething == false) AtkBotOnCooldown = true;
            KilledSomething = false;
        }
        
        if (AtkBotOnCooldown == true) AtkBotCooldown.Stop = AtkBotCooldown.Stop + 1;
    
        if (AtkBotCooldown.Stop >= AtkBotCooldown.Time) {
            AtkBotOnCooldown = false;
            AtkBotCooldown.Stop = 0;
        }
        //Timer for Top Attack
        if (player1.AttackTop == true && AtkTop.Stop <= AtkTop.Time && player1.SecondAttack == true && AtkTopOnCooldown == false) {
            AtkTop.Stop = AtkTop.Stop + 1;
            AttackSpriteTop.setPosition(100, 120);
            window.draw(AttackSpriteTop);
            attackTopVfx.Update(0, deltatime);
            AttackSpriteTop.setTextureRect(attackTopVfx.uvRect);
           
            if (AttackSpriteTop.getGlobalBounds().intersects(enemy2Sprite.getGlobalBounds())) {
                player1.Points = player1.Points + 500;
                KilledSomething = true;
            }
        }

        if (AtkTop.Stop >= AtkTop.Time) {
            player1.AttackTop = false;
            AtkTop.Stop = 0;
            AttackSpriteTop.setPosition(AttackPositionTop);
            if (KilledSomething == false) AtkTopOnCooldown = true;
            KilledSomething = false;
        }


        if (AtkTopOnCooldown == true) AtkTopCooldown.Stop = AtkTopCooldown.Stop + 1;

        if (AtkTopCooldown.Stop >= AtkTopCooldown.Time) {
            AtkTopOnCooldown = false;
            AtkTopCooldown.Stop = 0;
        }
        //Animation loops and render

        playerRun1.Update(0, deltatime);
        playerSprite1.setTextureRect(playerRun1.uvRect);

        playerRun2.Update(0, deltatime);
        playerSprite2.setTextureRect(playerRun2.uvRect);

        playerRun3.Update(0, deltatime);
        playerSprite3.setTextureRect(playerRun3.uvRect);

        enem1run.Update(0, deltatime);
        enemy1Sprite.setTextureRect(enem1run.uvRect);
       
        enem2run.Update(0, deltatime);
        enemy2Sprite.setTextureRect(enem2run.uvRect);

        enem3run.Update(0, deltatime);
        enemy3Sprite.setTextureRect(enem3run.uvRect);

        if (player1.FirstAttack == false && player1.SecondAttack == false) {
            window.draw(playerSprite1);
        }
        if (player1.FirstAttack == true && player1.SecondAttack == false) {
            window.draw(playerSprite2);
        }
        if (player1.FirstAttack == true && player1.SecondAttack == true) {
            window.draw(playerSprite3);
        }

        window.draw(text);
        window.draw(Points);
        window.draw(enemy2Sprite);
        window.draw(enemy3Sprite);
        window.draw(enemy1Sprite);
        window.display();
    }



    return 0;
}