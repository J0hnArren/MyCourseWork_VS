#ifndef HIGHERGROUND_CPP_GAMEMENU_H
#define HIGHERGROUND_CPP_GAMEMENU_H
#include "Records.h"
#include <SFML/Graphics.hpp>
#include "FilesBank.h"
#include <Button.h>
#include "Player.h"
#include "Platforms.h"

/**
 @brief Класс делегирующий игровые меню
 @details Подгружает в конструкторе изображения, содержит функции для разлиных видов меню и ввода никнейма
*/
class GameMenu {
public:
    GameMenu() = default;
    /**
     @brief Конструктор, принимающий размер окна и объект класса Records
     @details Инициализирует соответствующие поля, вызывает три функции, которые инициализируют поля текстов, шрифтов
     и кнопок
    */
    GameMenu(const sf::Vector2u &windowSize, Records &records_);
    GameMenu(const GameMenu&) = delete;
    ~GameMenu() = default;

    /**
     @brief Метод главного меню
     @details Создает, подгружает и отрисовывает главное игровое меню из которого есть доступ к самой игре,
     к таблице рекордов и выходу из игры
     @param window окно приложения в fullscreen
     @param player объект класса Player, содержащий его текстуру, отрисовку его анимаций и обработку его движений
     @param bgImage текстура игрового фона
    */
    bool Menu(sf::RenderWindow &window, const sf::Sprite &bgImage, Player &player);
    /**
     @brief Игровая пауза
     @details Создает, подгружает и отрисовывает главное игровое меню из которого есть доступ к самой игре,
     к таблице рекордов и выходу из игры
     @param window окно приложения в fullscreen
     @param player объект класса Player, содержащий его текстуру, отрисовку его анимаций и обработку его движений
     @param bgImage текстура игрового фона
     @param pauseTime время в паузе, будет отниматься от игрового, т. к. это не считается временем игровой сессии
    */
    bool Pause(sf::RenderWindow &window, const sf::Sprite &bgImage, Platforms &platforms, Player &player, int &pauseTime);
    /**
     @brief Выход из игры
     @param window окно приложения в fullscreen
    */
    bool Exit(sf::RenderWindow &window) const;
    /**
     @brief Попробовать играть снова, после поражения
     @details При поражении, на экран будет выводиться это меню, где будет дан выбор играть снова, либо посмотреть
     таблицу рекордов, либо вернуться в главное меню
     @param window окно приложения в fullscreen
     @param player объект класса Player, содержащий его текстуру, отрисовку его анимаций и обработку его движений
     @param bgImage текстура игрового фона
     @param platforms платформы в игре
    */
    bool TryAgain(sf::RenderWindow &window, const sf::Sprite &bgImage, Platforms &platforms, Player &player);
    /**
     @brief Возвращает введеный никнейм для сохранения и записи его в файл
    */
    std::string GetNickName();
private:
    /**
     @brief Инициализирует текст для меню
    */
    void inline InitializeText();
    /**
     @brief Инициализирует кпоки для всех типов меню
    */
    void inline InitializeButtons();
    /**
     @brief Инициализирует все типы лого для всех меню
    */
    void inline InitializeLogos();
    /**
     @brief Открывает меню с таблицей рекордов
     @details Выводит таблицу с отсортированными по количеству очков списком из никнейма, количества очков и временем,
     проведенным в игровой сессии
     @param window окно приложения в fullscreen
     @param player объект класса Player, содержащий его текстуру, отрисовку его анимаций и обработку его движений
     @param bgImage текстура игрового фона
    */
    void ShowRecords(sf::RenderWindow &window, const sf::Sprite &bgImage, Player &player);
    /**
     @brief Создает прямоугольник, по нажатию на который мы можем сменить никнейм
     @param text текст по которому определяется размер никнейма, т. е. квадрата
    */
    static sf::IntRect NickNameArea(sf::Text& text);
    /**
     @brief Метод, обрабатывающий ввод нового никнейма
     @param event текущее событие
     @param text текст, в который будет записан новый никнейм
    */
    static bool enterText(sf::Event& event, sf::Text& text);
    /**
     @brief Открывает поток, записывая имя в файл
    */
    void write();
    /**
     @brief Вспомогательный метод для GameMenu::write(), преобразовывает тип никнейма перед записью
     @param tempNick временная переменная для записи никнейма
    */
    void writeName(sf::Text &tempNick);
    const std::string path = "src/top/";
    sf::Text NickName;
    Records records;

    sf::Vector2u winSize;

    sf::Clock clock;
    sf::Text textLogo, textPause, name;
    bool exit = false;
    bool MainMenu = true;
    std::vector<Button> buttons;
    sf::RectangleShape menuSquare;
};

#endif //HIGHERGROUND_CPP_GAMEMENU_H
