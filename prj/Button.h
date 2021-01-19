#ifndef HIGHERGROUND_CPP_BUTTON_H
#define HIGHERGROUND_CPP_BUTTON_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iosfwd>
#include "FilesBank.h"

/**
 @brief Класс создания кнопки
 @details Создает объект кномки со всеми ее атрибутами, в виде двух текстур (нажатой и обычной), шрифтов, надписей,
 соответствующих звуков.
*/
class Button {
public:
    Button() = default;
    Button(const Button&) = default;
    /**
     @brief Конструктор назвачает поля атрибутов кнопки
     @details Инициализирует следующие поля: size1, button, beginRect, sizeRect, size2, nextBeginRect, nextSizeRect, text
     @param texture_ ссылка на текстуру
     @param buttonSize константная ссылка на размер первого состояния кнопки
     @param beginPosTexture константная ссылка на координаты начала кнопки на текстуре
     @param textureRectSize константная ссылка на размер кнопки на текстуре
     @param nextButtonSize константная ссылка на размер второго состояния кнопки
     @param nextBeginPosTexture константная ссылка на начала координат второй кнопки
     @param nextTextureRectSize константная ссылка на размер воторой кнопки
     @param buttonName константная ссылка на надпись на кнопке
     @param font константная ссылка на шрифт надписи на кнопке
    */
    Button(
            sf::Texture &texture_,
            const sf::Vector2f &buttonSize,
            const sf::Vector2f &beginPosTexture,
            const sf::Vector2f &textureRectSize,
            const sf::Vector2f &nextButtonSize,
            const sf::Vector2f &nextBeginPosTexture,
            const sf::Vector2f &nextTextureRectSize,
            const std::string &buttonName,
            const sf::Font& font);
    ~Button() = default;

    /**
     @brief Устанавливает позицию кнопки
     @details Устанавливает новую позиуию квадрата кнопки, ее текста и контейнера, по которому будут кликать мышкой
     @param position константная ссылка на координаты, куда нужно установить позицию кнопки
    */
    void setPos(const sf::Vector2f &position);
    /**
     @brief Проверяет, нажали ли на кнопку
     @details Если на кпопку наверли мышкой и нажали, то будет произведено соответствующее дейстиве, метод также
     отвечает на смену текстур кноки и ее звуков, в записимости от наведения и не наведения на нее
     @param window окно приложения в fullscreen
     @param soundClick звук нажатия на кнопку
     @param soundRoll звук наведения мышкой на кнопку
    */
    bool Clicked(sf::RenderWindow& window, sf::Sound& soundClick, sf::Sound& soundRoll);

    sf::Text text;
    sf::RectangleShape button;
private:
    sf::Clock clock;
    sf::IntRect container;

    sf::Vector2f size1;
    sf::Vector2f beginRect;
    sf::Vector2f sizeRect;
    sf::Vector2f size2;
    sf::Vector2f nextBeginRect;
    sf::Vector2f nextSizeRect;

    bool isClick = true;
};


#endif //HIGHERGROUND_CPP_BUTTON_H
