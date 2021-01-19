#include "Player.h"
#include "Collision.h"
#include "Platforms.h"
#include "GameMenu.h"
#include <sstream>

/**
 @brief Булевая переменная для хранения состояния игрока (true - можно играть, false - проиграл)
*/
bool isAlive = true;
/**
 @brief Булевая переменная для проверки активности игрока; после 30 секунд бездействия, игрок проигрывает
*/
bool AFK = false;
/**
 @brief Глобальная переменная для хранения набранных игроком очков за одну игровую сессию
*/
int score = 0;

/**
 @brief Главная функция отрисовки игрового процесса
 @details Отрисовывает игровой процесс, обновляя анимацию игрока, следя за его передвижениями,
 его коллизиями с платформами, соответствующими звуками, передвижениями платформ, отрисовкой игрового времени и
 количества очков в одной игровой сессии. Также проверяет не проиграл ли игрок, в случае поражения выдает специальное
 меню и сохраняет данные игровой сессии: никнейм, время игры, количество очков.
 @param window окно приложения в fullscreen
 @param player1 объект класса Player, содержащий его текстуру, отрисовку его анимаций и обработку его движений
 @param collision проверка коллизий игрока и платформ, а также соответстсующие им звуки
 @param records проверка необходимости записи нового рекорда
 @param platforms осуществляет генерацию платформ и их перемещение
 @param timerText игровой таймер, который выводится на экран
 @param scaleText количество очков, выводимых на экран
 @param windowSize размер окна
 @param bgSprite текстура игрового фона
 @param scaleValue значение на котрое будет увеличена текстура игрока, также нужна в классе Collision
 @param gameMenu содержит основное меню, меню с таблицей рекордов и меню паузы
 @param sound0, sound1, sound2, deathSound игровые звуки
*/
void GameProcess(sf::RenderWindow &window, Player &player1, Collision &collision, Records &records,
                 Platforms &platforms, sf::Text &timerText, sf::Text &scoreText, const sf::Vector2u &windowSize,
                 const sf::Sprite &bgSprite, const float &scaleValue, GameMenu &gameMenu,
                 sf::Sound &sound0, sf::Sound &sound1, sf::Sound &sound2, sf::Sound &deathSound);
/**
 @brief Проверка состояния игрока
 @details Проверяет состояние игрока, если isAlive = false или AFK = true, то выводит из функции GameProcess() и выдает меню
 @param player1 объект класса Player, содержащий его текстуру, отрисовку его анимаций и обработку его движений
 @param windowSize размер окна
 @param gameTime текущее время игровой сессии
*/
bool DeathCheck(Player &player, const sf::Vector2u &windowSize, const int &gameTime);
/**
 @brief Перезагрузка уровня
 @details Возвращяет игрока на исходную позиции, заново генерирует платформы, обнуляет заработанные за игровую сессию очки
 @param platforms осуществляет генерацию платформ и их перемещение
 @param windowSize размер окна
 @param player1 объект класса Player, содержащий его текстуру, отрисовку его анимаций и обработку его движений
*/
void ReloadScreen(Platforms &platforms, const sf::Vector2u &windowSize, Player &player1);

/** @file */
/**
@brief Стартовая функция всего проекта
@details Создает отрисовываемое впоследствии окно, подгружает текстуры, шрифт, звуки, музыку, и делегирует всеми меню
*/
int main()
{
    sf::RenderWindow window(
            sf::VideoMode::getFullscreenModes()[0],
            "Hello there!",
            sf::Style::Fullscreen
            );
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(120);

    // winSize size
    sf::Vector2u windowSize = window.getSize();
    std::cout << windowSize.x << " X " << windowSize.y;

    // Music
    sf::Music track1, track2, track3, track4;
    track1.openFromFile("src/audio/Track_01.ogg");
//    track2.openFromFile("src/audio/Track_02.ogg");
//    track3.openFromFile("src/audio/Track_03.ogg");
//    track4.openFromFile("src/audio/Track_04.ogg");
    //track1.play();
    track1.setLoop(true);

    //background image
    sf::Sprite bgSprite;
    FilesBank::getInstance().AddFiles("bg", "bg0.png");
    FilesBank::getInstance().AddFiles("bg", "bg1.png");
    FilesBank::getInstance().AddFiles("bg", "bg2.png");
    bgSprite.setTexture(*FilesBank::getInstance().GetFile("bg", 2));
    sf::Vector2u bgSize = FilesBank::getInstance().GetFile("bg", 2)->getSize();

    sf::Vector2f scale;
    scale.x = windowSize.x * 1.0f / bgSize.x,
    scale.y = windowSize.y * 1.0f / bgSize.y;
    bgSprite.setScale(scale);

    // Font & Text
    FilesBank::getInstance().AddFont("timer", "nightmare.otf");
    // Create a text which uses our font
    sf::Text timerText, scoreText;
    timerText.setFont(*FilesBank::getInstance().getFonts("timer", 0));
    timerText.setCharacterSize(45);
    timerText.setStyle(sf::Text::Regular);
    scoreText.setFont(*FilesBank::getInstance().getFonts("timer", 0));
    scoreText.setCharacterSize(40);
    scoreText.setStyle(sf::Text::Regular);

    // Sounds
    FilesBank::getInstance().AddSound("jump", "hopper_jump.ogg"); // 0 - usual jump
    FilesBank::getInstance().AddSound("jump", "thud_jump.ogg"); // 1 - louder jump
    FilesBank::getInstance().AddSound("jump", "trampoline.ogg"); // 2 - highest jump
    FilesBank::getInstance().AddSound("button", "ui_button_confirm.wav"); // 0 - rolling buttons
    FilesBank::getInstance().AddSound("button", "button.ogg"); // 1 - click
    FilesBank::getInstance().AddSound("other", "hit3.ogg"); // death sound
    FilesBank::getInstance().AddSound("other", "The-Witcher-3-Quest-complete-sound.ogg"); // records table sound
    sf::Sound sound0(*FilesBank::getInstance().getSounds("jump", 0));
    sf::Sound sound1(*FilesBank::getInstance().getSounds("jump", 1));
    sf::Sound sound2(*FilesBank::getInstance().getSounds("jump", 2));
    sf::Sound deathSound(*FilesBank::getInstance().getSounds("other", 0));
    sound0.setVolume(40);
    sound1.setVolume(40);
    sound2.setVolume(40);

    //main hero sprite
    Player player1(windowSize, "hero.png", "hero1.png", score);
    const float scaleValue = 3;
    player1.GetSprite()->setScale(sf::Vector2f(scaleValue, scaleValue));

    // ShowRecords
    Records records("src/top/", 5);

    // Menu
    GameMenu gameMenu(windowSize, records);

    //Platforms
    Platforms platforms(windowSize, "platforms.png"); // all platforms texture

    // Collision
    Collision collision(score);

    // Delegate with different menus
    while (gameMenu.Exit(window)){
        if (isAlive) {
            gameMenu.Menu(window, bgSprite, player1);
            GameProcess(window, player1, collision, records, platforms, timerText, scoreText, windowSize,
                        bgSprite, scaleValue, gameMenu, sound0, sound1, sound2, deathSound);
            ReloadScreen(platforms, windowSize, player1);
        } else {
            if (gameMenu.TryAgain(window, bgSprite, platforms, player1)){
                isAlive = true;
                ReloadScreen(platforms, windowSize, player1);
            } else {
                ReloadScreen(platforms, windowSize, player1);
                GameProcess(window, player1, collision, records, platforms, timerText, scoreText, windowSize,
                            bgSprite, scaleValue,gameMenu, sound0, sound1, sound2, deathSound);
                ReloadScreen(platforms, windowSize, player1);
            }
        }
    }

    return 0;
}

void GameProcess(sf::RenderWindow &window, Player &player1, Collision &collision, Records &records,
                 Platforms &platforms, sf::Text &timerText, sf::Text &scoreText, const sf::Vector2u &windowSize,
                 const sf::Sprite &bgSprite, const float &scaleValue, GameMenu &gameMenu,
                 sf::Sound &sound0, sf::Sound &sound1, sf::Sound &sound2, sf::Sound &deathSound){
    // Music
    sf::Music track4;
    track4.openFromFile("src/audio/Track_04.ogg");
    track4.play();
    track4.setLoop(true);

    int fps = 0; // fps need for player animation update
    int gameTime = 0, pauseTime = 0; // total time in the game/pause
    sf::Clock clock, gameTimeClock;
    sf::Vector2f currPos; // player's current position on the screen
    while (window.isOpen())
    {
        float deltaTime = clock.getElapsedTime().asMicroseconds() / 750.f;
        clock.restart();
        gameTime = int(gameTimeClock.getElapsedTime().asSeconds()) - pauseTime;

        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(bgSprite);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab) || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
            track4.pause();
            if (gameMenu.Pause(window, bgSprite, platforms, player1, pauseTime)){
                gameTimeClock.restart();
                return;
            }
            track4.play();
        } else {
            ++fps;
            //std::cout << fps << "\n";

            // Platforms drawing
            if (player1.GetSprite()->getPosition().y < windowSize.y / 2.f) {
                player1.GetSprite()->setPosition(player1.GetSprite()->getPosition().x, windowSize.y / 2.f);
                platforms.PlatformMover(deltaTime, *player1.GetAcceleration(), gameTime);
            }
            for (const sf::RectangleShape &sp : *platforms.GetPlatform()) {
                window.draw(sp);
            }
            // Checking for movements
            currPos = player1.GetSprite()->sf::Transformable::getPosition();
            player1.Update(deltaTime, currPos, gameTime, AFK);

            // Updating animation
            player1.UpdatePlayerAnimation(fps);
            window.draw(*player1.GetSprite());

            // Checking for collisions
            collision.CollisionCheck(
                    *player1.GetSprite(), *player1.GetAcceleration(), *platforms.GetPlatform(), scaleValue,
                    sound0, sound1, sound2
            );

            // Timer
            std::ostringstream gameTimeString;
            gameTimeString << gameTime;
            timerText.setString("Time: " + gameTimeString.str());
            timerText.setPosition(windowSize.x - timerText.getLocalBounds().width - 30, 20);
            window.draw(timerText);

            // Score
            std::ostringstream totalScore;
            totalScore << score;
            scoreText.setString("Score: " + totalScore.str());
            scoreText.setPosition(windowSize.x - scoreText.getLocalBounds().width - 30, 60);
            window.draw(scoreText);

            // Are the character alive?
            if (!DeathCheck(player1, windowSize, gameTime)){
                if (records.isNewRecord(score)) {
                    try {
                        records.read();
                        if (!records.write(gameMenu.GetNickName(), score, gameTime))
                            throw std::runtime_error("HigherGround.cpp: line 202: could not load from file");
                    } catch (std::runtime_error &e) {
                        std::cout << e.what() << "\n";
                    }
                }
                deathSound.play();
                return;
            }
        }

        window.display();
    }
}

bool DeathCheck(Player &player, const sf::Vector2u &windowSize, const int &gameTime){
    isAlive = true;

    if (gameTime < 3) {
        if (player.GetSprite()->getPosition().y > windowSize.y - player.GetSprite()->getTextureRect().width * 3.f){
            *player.GetAcceleration() = -17.f; // high
        }
    } else if (player.GetSprite()->getPosition().y > windowSize.y){
            isAlive = false;
            return isAlive;
    }

    if (AFK){
        isAlive = false;
    }
    AFK = false;

    return isAlive;
}

void ReloadScreen(Platforms &platforms, const sf::Vector2u &windowSize, Player &player1){
    score = 0;
    platforms.Respawn();
    player1.GetSprite()->setPosition(windowSize.x * 2.3f / 5.f, windowSize.y * 4.f / 5.f);
}