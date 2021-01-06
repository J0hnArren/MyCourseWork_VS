#ifndef FILESBANK_H
#define FILESBANK_H
#include <iosfwd>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <map>
#include <stdexcept>
#include <iostream>

/**
 @brief Класс хранения текстур, звуков, шрифтов
 @details Реализован по паттерну Синглтона Меерса
*/
class FilesBank
{
public:
    /**
     @brief возвращает локальную статическую переменную метода getInstance(), хранящего единственный экземпляр класса
    */
	static FilesBank& getInstance();
    /**
     @brief Метод осуществляет добавление текстуры
     @param fileType тип добавляемого файла
     @param fileName название добавляемого файла
    */
	void AddFiles(const std::string& fileType, const std::string& fileName) noexcept(false);
    /**
     @brief Метод осуществляет добавление звуков
     @param fileType тип добавляемого файла
     @param fileName название добавляемого файла
    */
    void AddSound(const std::string& fileType, const std::string& fileName) noexcept(false);
    /**
     @brief Метод осуществляет добавление шрифтов
     @param fileType тип добавляемого файла
     @param fileName название добавляемого файла
    */
    void AddFont(const std::string& fileType, const std::string& fileName) noexcept(false);

    /**
     @brief Возвращает константную ссылку на объект sf::Texture, тип - указатель на sf::Texture
    */
    sf::Texture* GetFile(const std::string& fileType, const int &fileNumber);
    /**
     @brief Возвращает константную ссылку на объект sf::SoundBuffer, тип - указатель на sf::SoundBuffer
    */
    sf::SoundBuffer* getSounds(const std::string& fileType, const int &musicNumber);
    /**
     @brief Возвращает константную ссылку на объект sf::Font, тип - указатель на sf::Font
    */
    sf::Font* getFonts(const std::string& fileType, const int &fontNumber);
private:
	FilesBank() = default;
	FilesBank(const FilesBank&) = delete;
	~FilesBank() = default;
	FilesBank& operator=(FilesBank const&) = delete;

    std::map<std::string, std::vector<sf::Texture>> singletonTextures;
    std::map<std::string, std::vector<sf::SoundBuffer>> sounds;
    std::map<std::string, std::vector<sf::Font>> fonts;

    /**
     @brief Проверяет правильность формата добавленного файла, инача выбрасывает исключение
     @details выбрасывает std::invalid_argument исключение
     @param fileName имя файла
    */
	static void FileFormatCheck(const std::string& fileName);
    /**
     @brief Проверяет правильность типа добавленной текстуры, инача выбрасывает исключение
     @details выбрасывает std::invalid_argument исключение
     @param ST_FileType тип файла
    */
	static void TexturesTypeCheck(const std::string &ST_FileType);
    /**
     @brief Проверяет правильность формата добавленного звука, инача выбрасывает исключение
     @details выбрасывает std::invalid_argument исключение
     @param ST_FileType тип файла
    */
    static void SoundTypeCheck(const std::string &ST_FileType);
    /**
     @brief Проверяет правильность формата добавленного шрифта, инача выбрасывает исключение
     @details выбрасывает std::invalid_argument исключение
     @param ST_FileType тип файла
    */
    static void FontTypeCheck(const std::string &ST_FileType);
    /**
     @brief Метод проверяет, загрузился ли файл
     @details выбрасывает std::runtime_error исключение
     @param fileName имя файла
    */
    static void FileLoadCheck(const std::string& fileName);

	sf::Texture texture;
    sf::SoundBuffer sound;
    sf::Font font;
};

#endif // !FILESBANK