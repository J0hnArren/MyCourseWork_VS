#ifndef PLATFORMS
#define PLATFORMS
#include <SFML/Graphics.hpp>
#include "FilesBank.h"
#include <random>
#include <iostream>
#include <iterator>
#include <ctime>

/**
 @brief Класс платформ
 @details Генерирует платформы, устранавливает их текстры, делегирует их перемещение и рандомную расстановку
*/
class Platforms
{
public:
	Platforms() = default;
	Platforms(const Platforms&) = delete;
    /**
     @brief Конструктор генерации платформ
     @details Инициализирует следующие поля: winSize, File, W, cW, H, cH, lineX, lineY. Вызывает метод генерации
     платформ, и задает в std::vector<int> randLines значения
     @param windowSize размер текущего окна (экрана)
     @param file путь к тестуре платформ
    */
	Platforms(const sf::Vector2u &windowSize, const std::string& file);
	~Platforms() = default;

    /**
     @brief Передвижение платформ
     @details Метод двигает платформы, когда платформа уходит вниз экрана, задает ей новую рандомную координату,
     также случайным образом может дать платформе новый тип, может удалить платформу
     @param deltaTime скорость передвижения, зависящая от времени
     @param accY ускорение прыжка
     @param currPos координаты текущей позиции игрока
    */
	void PlatformMover(const float &deltaTime, const float &accY, const int &currTime) noexcept(false);
    /**
     @brief Возвращает рандомную координату по оси X
    */
    float RandCoordinateX(const float &coord, const float &prevCoord = 0);
    /**
     @brief Возвращает рандомную координату по оси Y
    */
    float RandCoordinateY(const float &coord, const float &prevCoord = 0);
    /**
     @brief Выбирает рандомную платформу из диапазона
     @param capacity диапазон
    */
    int RandPlatform(const int& capacity);
    /**
     @brief Очищает векторы platformsList и platformsCoords, а затем заново запускает генерацию
    */
    void Respawn();

    /**
     @brief Возвращает константную ссылку на std::vector<sf::RectangleShape>,
     тип - указатель на std::vector<sf::RectangleShape>
    */
    const std::vector<sf::RectangleShape>* GetPlatform() const;

private:
    /**
     @brief Метод устанавливает текстры платформы
     @param spr прямоугльник sf::RectangleShape, на который устранавливается текстура
     @param X, Y координаты платформы
     @param platformSkin номер платформы в банке текстур
    */
    void AddTextures(sf::RectangleShape &spr, const int& X, const int& Y, const int& platformSkin) const;
    /**
     @brief Генерация и случайная расстановка непересекающихся платформ на экране
    */
    void StartGeneration();

    std::random_device rd;
    sf::RectangleShape sprite;
	sf::Vector2u winSize;
    std::vector<std::tuple<float, float>> platformsCoords;
	std::vector<sf::RectangleShape> platformsList;
    std::vector<sf::RectangleShape>::iterator it;
	unsigned int lineX = 0, lineY = 0, moverCount = 0; // lineX * lineY = maximum number of existing platforms
	int W = 0, cW = 0, H = 0, cH = 0;
    sf::Vector2f startPos;
    float coordX = 0, p1 = 0;
    float coordY = 0, p2 = 0;
    int randPlatform = 0, timeToHide = 10;
    std::vector<int> randLines;

    std::string File;
};
#endif // PLATFORMS
