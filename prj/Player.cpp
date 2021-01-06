#include "Player.h"

Player::Player(const sf::Vector2u &windowSize, const std::string& file_1, const std::string& file_2, int& score)
    : Player(windowSize, file_1, file_2, 17, 12, 44, 40, 0, score) {
    winSize = windowSize;
    totalScore = &score;

    Initialize(file_1, file_2);
}

Player::Player(
        const sf::Vector2u &windowSize,
        const std::string& file_1, const std::string& file_2,
        const int& x, const int& y,
        const int& w, const int& h,
        const int& playerSkin, int& score) {
    winSize = windowSize;
    X = x; Y = y; W = w; H = h; skin = playerSkin;
    totalScore = &score;

    Initialize(file_1, file_2);
}

void Player::Initialize(const std::string& file_1, const std::string& file_2){
    FilesBank::getInstance().AddFiles("player", file_1);
    FilesBank::getInstance().AddFiles("player", file_2);
    sprite.setSize(sf::Vector2f(winSize.x / 43.64f, winSize.y / 26.f));
    sprite.setTexture(FilesBank::getInstance().GetFile("player", skin));
    sprite.setTextureRect(sf::IntRect(X, Y, H, W));
    sprite.setPosition(winSize.x * 2.3f / 5.f, winSize.y * 4.f / 5.f);
}


void Player::Controls(float& deltaTime, sf::Vector2f& currPos, int& gameTime) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        currPos.x -= deltaTime / 1.5f;
        turnLeft = true;
        fine = false;
        stayingTime = gameTime;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        currPos.x += deltaTime/ 1.5f;
        turnLeft = false;
        fine = false;
        stayingTime = gameTime;
    }
}

void Player::Update(float& deltaTime, sf::Vector2f& currPos, int& gameTime, bool &AFK) {
    // Keyboard
    Controls(deltaTime, currPos, gameTime);
    if (gameTime - stayingTime == 10 && fine){
        *totalScore -= 3;
        fine = true;
    } else if (gameTime - stayingTime == 20 && fine){
        *totalScore -= 30;
        fine = true;
    } else if (gameTime - stayingTime == 30 && fine){
        *totalScore -= 300;
        fine = true;
        AFK = true;
    }
    fine = true;

    Jump(currPos.x, currPos.y);
    sprite.setPosition(currPos.x, currPos.y);

    // Checks player's position at the both borders of the map
    // left side
    if (currPos.x < -sprite.getTextureRect().width) {
        sprite.setPosition(winSize.x, currPos.y);
    }
    // right side
    else if (currPos.x > winSize.x) {
        sprite.setPosition(0, currPos.y);
    }
}

void Player::Jump(float& x, float& y){
    accY += 0.7f; // acceleration
    //std::cout << accY << std::endl;
    y += accY;
//    if (y > winSize.y - sprite.getTextureRect().width * 3.f){
//        accY = -17; // high
//    }
}

void Player::UpdatePlayerAnimation(int& fps) {
    int spritePos = 0;
    if (turnLeft) {
        sprite.setTexture(FilesBank::getInstance().GetFile("player", skin + 1));
        //choose a correct part of sprite to make an animation
        if (fps > 70) { spritePos = 938; fps = 0; }
        else if (fps > 60) { spritePos = 838; }
        else if (fps > 50) { spritePos = 738; }
        else if (fps > 40) { spritePos = 638; }
        else if (fps > 30) { spritePos = 538; }
        else if (fps > 20) { spritePos = 438; }
        else if (fps > 10) { spritePos = 338; }
        else if (fps > 0) { spritePos = 238; }

        sprite.setTextureRect(sf::IntRect(spritePos, Y, W, H));
    } else{
        sprite.setTexture(FilesBank::getInstance().GetFile("player", skin));
        if (fps > 70) { spritePos = 17; fps = 0; }
        else if (fps > 60) { spritePos = 116; }
        else if (fps > 50) { spritePos = 215; }
        else if (fps > 40) { spritePos = 315; }
        else if (fps > 30) { spritePos = 415; }
        else if (fps > 20) { spritePos = 516; }
        else if (fps > 10) { spritePos = 617; }
        else if (fps > 0) { spritePos = 717; }

        sprite.setTextureRect(sf::IntRect(spritePos, Y, W, H));
    }
}

sf::RectangleShape* Player::GetSprite() {
    return &sprite;
}

float* Player::GetAcceleration(){
    return &accY;
}