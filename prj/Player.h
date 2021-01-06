#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <SFML/Graphics.hpp>
#include <iosfwd>
#include "FilesBank.h"

/**
 @brief Класс игрока
 @details Создает объект игрока, делегирует его анимацией и движениями
*/
class Player {
public:
    Player() = default;
    Player(const Player&) = default;
    /**
     @brief Конструктор с минимальным количеством параметров
     @details Инициализирует три поля, устнавливает текстуры игрока
     @param windowSize размер текущего окна (экрана)
     @param file_1, file_2 обе тустуры игрока, в левую и правую стороны
     @param score количество очков игрока
    */
    Player(const sf::Vector2u &windowSize, const std::string& file_1, const std::string& file_2, int& score);
    /**
     @brief Конструктор с минимальным количеством параметров
     @details Инициализирует три поля, устнавливает текстуры игрока
     @param windowSize размер текущего окна (экрана)
     @param file_1, file_2 обе тустуры игрока, в левую и правую стороны
     @param X, Y координаты текущего состояния игрока на текстуре
     @param W, H ширина и высота текущего состояния игрока на текстуре
     @param playerSkin номер текстуры в хранилище текстур
     @param score количество очков игрока
    */
    Player(
            const sf::Vector2u &windowSize,
            const std::string& file_1, const std::string& file_2,
            const int& X, const int& Y,
            const int& W, const int& H,
            const int& playerSkin, int& score
            );
    ~Player() = default;

    /**
     @brief Метод анимирования игрока
     @details Переставляя положение координат на текстуре и саму текстуру в зависимости от fps и нарпавления движения,
     метод анимирует текстуру игрока
    */
    void UpdatePlayerAnimation(int& fps);
    /**
     @brief Контроль и обновление движений
     @details Вызывает функцию void Controls(float& deltaTime, sf::Vector2f& currPos, int& gameTime),
     которая отвечает за нажатие кнопок, проверяет, как долго не двигался игрок, перемещает игрока
     на противоположную сторону экрана, когда он прыгает в боковой край
     @param deltaTime скорость передвижения, зависящая от времени
     @param currPos координаты текущей позиции игрока
     @param gameTime время игровой сессии
     @param AFK если игрок не двигался 30 секунд, то этот флаг говорит о том, что он прогирал
    */
    void Update(float& deltaTime, sf::Vector2f &currPos, int& gameTime, bool &AFK);

    /**
     @brief Возвращает ссылку на объект sf::RectangleShape
    */
    sf::RectangleShape* GetSprite();
    /**
     @brief Возвращает ссылку на поле accY
    */
    float* GetAcceleration();
private:
    bool turnLeft = false; // did the sprite turn
    bool fine = false; // need to take away points for the AFK

    /**
     @brief Обработка нажатия клавиш движения, также обновляет состояния флагов turnLest и fine
     @param deltaTime скорость передвижения, зависящая от времени
     @param currPos координаты текущей позиции игрока
     @param gameTime время игровой сессии
    */
    void Controls(float& deltaTime, sf::Vector2f& currPos, int& gameTime); //Keyboard
    /**
     @brief Метод прыжка, вызывается каждый раз, когда игрок попадает на платформу, не требует нажатия клавиш
    */
    void Jump(float& x, float& y);
    /**
     @brief Метод задает текстуры
    */
    void Initialize(const std::string& file_1, const std::string& file_2);

    float accX = 0, accY = 0;
    int X = 0, Y = 0, W = 0, H = 0, skin = 0;
    int stayingTime = 0; // time you are doing nothing
    int* totalScore {nullptr};
    sf::RectangleShape sprite;
    sf::Vector2u winSize = {0, 0};
};
#endif
