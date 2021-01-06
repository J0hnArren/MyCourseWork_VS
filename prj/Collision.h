#ifndef COLLISION
#define COLLISION
#include <SFML/Graphics.hpp>
#include "FilesBank.h"

 ///@brief Класс обработки коллизий
class Collision
{
public:
	Collision() = default;
    /**
     @brief Конструктор инициализирует поле totalScore
     @param score ссылка на количество очков
    */
	explicit Collision(int& score);
	Collision(const Collision&) = delete;
	~Collision() = default;

    /**
     @brief Метод обработки коллизий
     @details Проверяет положение игрока и каждой платформы, если текстура игрока (за исключением меча игрока)
     соприкасаются с платформой, то в зависимости от типа платформы игрок отпрыгнет соответствующим образом, либо
     не отпрыгнет вовсе
     @param player ссылка на объект игрока
     @param accY ссылка на значение ускорения прыжка (высоту)
     @param platforms константная ссылка на вектор с платформами
     @param scaleValue константная ссылка на значение увеличения текстуры игрока
     @param sound0, sound1, sound2 звуки отпрыгивания от разных платформ
    */
	bool CollisionCheck(
	        sf::RectangleShape &player, float &accY,
	        const std::vector<sf::RectangleShape> &platforms,
	        const float &scaleValue,
            sf::Sound &sound0, sf::Sound &sound1, sf::Sound &sound2
	        );
private:
    /**
     @brief Константный метод, который задает высоту прыжка в зависимости от типа платформы
     @param accY ссылка на значение ускорения прыжка (высоту)
     @param platforms константная ссылка на вектор с платформами
     @param sound0, sound1, sound2 звуки отпрыгивания от разных платформ
    */
    void Acceleration(
            float &accY, const sf::RectangleShape &platform,
            sf::Sound &sound0, sf::Sound &sound1, sf::Sound &sound2) const;

    const float speed = -20;
    int* totalScore {nullptr};
    bool isCollided = false;
};
#endif //COLLISION