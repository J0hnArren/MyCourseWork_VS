#include "Collision.h"

Collision::Collision(int& score) {
    totalScore = &score;
}

bool Collision::CollisionCheck(
        sf::RectangleShape &player, float &accY,
        const std::vector<sf::RectangleShape> &platforms,
        const float &scaleValue, sf::Sound &sound0, sf::Sound &sound1, sf::Sound &sound2) {
    isCollided = false;
    const float playerX = player.getPosition().x;
    const float playerY = player.getPosition().y;
    const int swordSize = 17;
    // if player's texture turn to left side
    if (player.getTextureRect().left % 10 == 8){
        for (const sf::RectangleShape &platform : platforms){
            if ((playerX < platform.getPosition().x + 192)
            && (playerX + (44 - swordSize) * scaleValue  > platform.getPosition().x)
            && (playerY + 40 * scaleValue > platform.getPosition().y)
            && (playerY + 40 * scaleValue < platform.getPosition().y + 32) && (accY > 0)){
                Acceleration(accY, platform, sound0, sound1, sound2);
                isCollided = true;
            }
        }
        // right side
    } else {
        for (const sf::RectangleShape &platform : platforms){
            if ((playerX + swordSize * scaleValue < platform.getPosition().x + 192)
             && (playerX + 44 * scaleValue > platform.getPosition().x)
             && (playerY + 40 * scaleValue > platform.getPosition().y)
             && (playerY + 40 * scaleValue < platform.getPosition().y + 32) && (accY > 0)){
                Acceleration(accY, platform, sound0, sound1, sound2);
                isCollided = true;
            }
        }
    }
    if (playerY + 47 < 0){
        player.setPosition(playerX, 0);
    }

    return isCollided;
}

void Collision::Acceleration(
        float &accY, const sf::RectangleShape &platform,
        sf::Sound &sound0, sf::Sound &sound1, sf::Sound &sound2) const{
    if (platform.getTextureRect().top == 128){
        accY = speed;
        sound0.play();
        *totalScore += 10;
    } else if (platform.getTextureRect().top == 64){
        accY = speed * 2.f;
        sound1.play();
        *totalScore += 50;
    } else if (platform.getTextureRect().top == 160){
        accY = speed * 3.f;
        sound2.play();
        *totalScore += 100;
    } else if (platform.getTextureRect().top == 96){
        accY = speed / 20.f;
        sound0.play();
        *totalScore -= 1;
    }
}