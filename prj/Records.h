#ifndef HIGHERGROUND_CPP_RECORDS_H
#define HIGHERGROUND_CPP_RECORDS_H
#include <SFML/Graphics.hpp>
#include "FilesBank.h"
#include <iosfwd>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

/**
 @brief Структура хранения информации о рекорде
 @details Записывает таблицу рекордов, считывает ее и выводит на экран
*/
struct Top
{
    bool operator==(const Top &rhs) const;
    bool operator!=(const Top &rhs) const { return !operator==(rhs); }
    std::string name;
    int scores = 0;
    int time = 0;
};

/**
 @brief Класс для создания таблицы рекордов
 @details Записывает таблицу рекордов, считывает ее и выводит на экран
*/
class Records {
public:
    /**
     @brief Конструктор, принимающий путь к файлу и размер топа
     @details Инициализирует поле с путем к файлу, куда будут записаны рекорды в количестве указанного вторым
     параметром размером топа
    */
    Records(std::string Path, const int& SizeTop);
    Records() = default;
    Records(const Records&) = default;

    /**
     @brief Метод считывает информацию из файла data.txt
    */
    bool read();
    /**
     @brief Метод проверяет, является ли новый результат достаточным, чтобы попасть в топ 5,
     если да, то вызавается метод записи
     @param score количество очков
    */
    bool isNewRecord(const int& score);
    /**
     @brief Метод записывает в файл новый результат, если такой игрок уже есть в топе, то его результат обновится
     и отсортируется по количеству очков
     @param name Никнейм игрока
     @param score количество очков
     @param gameTime игровое время
    */
    bool write(const std::string &name, const int &score, const int& gameTime);
    /**
     @brief Метод выводит топ
     @details Выводится таблица топа, хранимая в std::vector<Top> top, задается цвет текста, устранавливается шрифт
     @param textSize размер текста в топе
     @param color цвет текста в топе
    */
    sf::Text ShowTable(const int& textSize, const sf::Color& color);
private:
    std::vector<Top> top;
    sf::Text text;
    /**
     @brief Вспомогательный метод для основго метода bool write(const std::string &name, const int &point, const int &time)
    */
    bool write();
    /**
     @brief Метод добавляет проблелы
    */
    static std::string AddSpace(const int& count);
    std::string path;
    Top defaultTop;
    int sizeTop = 0;
};


#endif //HIGHERGROUND_CPP_RECORDS_H
