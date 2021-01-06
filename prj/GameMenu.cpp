#include "GameMenu.h"

GameMenu::GameMenu(const sf::Vector2u &windowSize, Records &records_) {
    winSize = windowSize;
    records = records_;

    // Initializing text, rectangles ans fonts
    InitializeButtons();
    InitializeText();
    InitializeLogos();
}

bool GameMenu::Menu(sf::RenderWindow &window, const sf::Sprite &bgImage, Player &player) {
    MainMenu = true;
    int buttonNumber = -1;
    buttons[0].text.setString("Play");
    buttons[2].text.setString("Exit");
    buttons[2].text.setScale(1,1);
    buttons[0].text.setOrigin(buttons[0].text.getGlobalBounds().width / 2, buttons[0].text.getGlobalBounds().height / 2);
    buttons[2].text.setOrigin(buttons[2].text.getGlobalBounds().width / 2, buttons[2].text.getGlobalBounds().height / 2);

    float interval = 0;
    for (Button &b : buttons) {
        b.setPos(sf::Vector2f(winSize.x / 2.f, winSize.y / 4.f + interval));
        interval += 200;
    }
    name.setPosition(menuSquare.getGlobalBounds().width * 0.9f, winSize.y / 4.f + interval - 60);
    NickName.setPosition(name.getPosition().x + name.getGlobalBounds().width + 30, name.getPosition().y);

    sf::Music track3;
    track3.openFromFile("src/audio/Track_03.ogg");
    track3.setVolume(20);
    track3.play();
    track3.setLoop(true);

    sf::Sound soundRoll(*FilesBank::getInstance().getSounds("button", 0));
    sf::Sound soundClick(*FilesBank::getInstance().getSounds("button", 1));
    soundClick.setVolume(20);
    soundRoll.setVolume(10);

    write();

    clock.restart();
    int fps = 0;
    sf::Vector2i mousePos;
    bool isEdit = false;
    sf::Text oldNick = NickName;
    sf::IntRect nickNameArea = NickNameArea(NickName);
    while (MainMenu) {

        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();

            mousePos = sf::Mouse::getPosition(window);
            bool isClick = sf::Mouse::isButtonPressed(sf::Mouse::Left);
            if (isClick && nickNameArea.contains(mousePos) && !isEdit) {
                isEdit = true;
            }
            if (isEdit) {
                isEdit = enterText(event, NickName);
                if (!isEdit && NickName.getString().getSize() < 2) {
                    NickName = oldNick;
                }
                else if (!isEdit) {
                    writeName(NickName);
                    NickNameArea(NickName);
                }
            }
        }
        window.clear();

        window.draw(bgImage);
        window.draw(menuSquare);
        window.draw(textLogo);
        window.draw(name);
        window.draw(NickName);

        ++fps;
        player.UpdatePlayerAnimation(fps);
        window.draw(*player.GetSprite());

        int currFrame = clock.getElapsedTime().asMilliseconds() / 16;
        if (currFrame > 10) {
            for (std::ptrdiff_t i = 0; i < buttons.size(); ++i) {
                window.draw(buttons[i].button);
                window.draw(buttons[i].text);

                if (buttons[i].Clicked(window, soundClick, soundRoll)) {
                    buttonNumber = i;
                }
            }
        }
        window.display();
        switch (buttonNumber) {
            case -1:
                continue;
            case 0:
                MainMenu = false;
                track3.stop();
                break;
            case 1:
                ShowRecords(window, bgImage, player);
                buttonNumber = -1;
                clock.restart();
                break;
            case 2:
                MainMenu = false;
                exit = true;
                Exit(window);
                break;
            default:
                window.close();
                return MainMenu;

        }
    }
    return MainMenu;
}

void GameMenu::write(){
    std::string line;
    std::ifstream reader(path + "name.txt");
    if (reader.is_open()) {
        if (reader.peek() != EOF) {
            getline(reader, line);
            reader.close();
            NickName.setString(line);
        }
        else {
            NickName.setString("Player");
            writeName(NickName);
        }
    }
}

void GameMenu::writeName(sf::Text &tempNick){
    std::string str = tempNick.getString().toAnsiString();
    std::ofstream writer(path + "name.txt");
    if (writer.is_open()) {
        writer << str << '\n';
        writer.close();
    }
}

bool GameMenu::enterText(sf::Event& event, sf::Text& text) {
    std::string str = text.getString().toAnsiString();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
        return false;
    } else if (event.type == sf::Event::TextEntered) {
        if (event.text.unicode < 128)
        {
            if (event.text.unicode == 8 && !str.empty()) {
                str.resize(str.size() - 1);
                text.setString(str);
            } else if (str.size() != 12 && event.text.unicode != 32) { // max 12 symbols in nickname
                if (event.text.unicode != 8)
                    str += static_cast<char>(event.text.unicode);
                text.setString(str);
            }
        }
    }
    return true;
}

sf::IntRect GameMenu::NickNameArea(sf::Text& text) {
    return sf::IntRect(text.getPosition().x - text.getGlobalBounds().width,
                       text.getPosition().y - text.getGlobalBounds().height / 2,
                       text.getLocalBounds().width * 2, text.getLocalBounds().height);
}

std::string GameMenu::GetNickName() {
    std::string nick_ = std::string(NickName.getString().toAnsiString());
    return nick_;
}

bool GameMenu::Pause(
        sf::RenderWindow &window, const sf::Sprite &bgImage, Platforms &platforms, Player &player, int &pauseTime
        ){
    buttons[0].text.setString("Continue");
    buttons[2].text.setString("Back to menu");
    buttons[2].text.setScale(0.7f, 0.7f);
    buttons[0].text.setOrigin(buttons[0].text.getGlobalBounds().width / 2 - 20, buttons[0].text.getGlobalBounds().height / 2);
    buttons[2].text.setOrigin(buttons[2].text.getLocalBounds().width / 2, buttons[2].text.getLocalBounds().height / 2);

    MainMenu = true;
    int buttonNumber = -1;
    int totalPauseTime = pauseTime;

    float interval = 0;
    for (Button &b : buttons) {
        b.setPos(sf::Vector2f(winSize.x / 2.f, winSize.y / 4.f + interval));
        interval += 200;
    }

    sf::Sound soundRoll(*FilesBank::getInstance().getSounds("button", 0));
    sf::Sound soundClick(*FilesBank::getInstance().getSounds("button", 1));
    soundClick.setVolume(20);
    soundRoll.setVolume(10);

    sf::Clock gameTimeClock;
    clock.restart();
    while (MainMenu) {

        pauseTime = int(gameTimeClock.getElapsedTime().asSeconds());

        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();

        window.draw(bgImage);

        for (const sf::RectangleShape &sp : *platforms.GetPlatform()) {
            window.draw(sp);
        }
        window.draw(*player.GetSprite());
        window.draw(menuSquare);
        window.draw(textPause);

        int currFrame = clock.getElapsedTime().asMilliseconds() / 16;
        if (currFrame > 10) {
            for (std::ptrdiff_t i = 0; i < buttons.size(); ++i) {
                window.draw(buttons[i].button);
                window.draw(buttons[i].text);

                if (buttons[i].Clicked(window, soundClick, soundRoll)) {
                    buttonNumber = i;
                }
            }
        }
        window.display();
        switch (buttonNumber) {
            case -1:
                continue;
            case 0:
                MainMenu = false;
                break;
            case 1:
                ShowRecords(window, bgImage, player);
                buttonNumber = -1;
                clock.restart();
                break;
            case 2:
                MainMenu = true;
                return MainMenu;
            default:
                window.close();
                return MainMenu;

        }
    }
    pauseTime += totalPauseTime;
    return MainMenu;
}

bool GameMenu::Exit(sf::RenderWindow &window) const {
     if (exit)
         window.close();
    return !exit;
}

bool GameMenu::TryAgain(sf::RenderWindow &window, const sf::Sprite &bgImage, Platforms &platforms, Player &player){
    buttons[0].text.setString("Try again");
    buttons[2].text.setString("Back to menu");
    buttons[2].text.setScale(0.7f, 0.7f);
    buttons[0].text.setOrigin(buttons[0].text.getGlobalBounds().width / 2 - 20, buttons[0].text.getGlobalBounds().height / 2);
    buttons[2].text.setOrigin(buttons[2].text.getLocalBounds().width / 2, buttons[2].text.getLocalBounds().height / 2);

    MainMenu = true;
    int buttonNumber = -1;

    float interval = 0;
    for (Button &b : buttons) {
        b.setPos(sf::Vector2f(winSize.x / 2.f, winSize.y / 4.f + interval));
        interval += 200;
    }

    sf::Sound soundRoll(*FilesBank::getInstance().getSounds("button", 0));
    sf::Sound soundClick(*FilesBank::getInstance().getSounds("button", 1));
    soundClick.setVolume(20);
    soundRoll.setVolume(10);

    clock.restart();
    while (MainMenu) {

        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();

        window.draw(bgImage);

        for (const sf::RectangleShape &sp : *platforms.GetPlatform()) {
            window.draw(sp);
        }
        window.draw(*player.GetSprite());
        window.draw(menuSquare);
        window.draw(textPause);

        int currFrame = clock.getElapsedTime().asMilliseconds() / 16;
        if (currFrame > 10) {
            for (std::ptrdiff_t i = 0; i < buttons.size(); ++i) {
                window.draw(buttons[i].button);
                window.draw(buttons[i].text);

                if (buttons[i].Clicked(window, soundClick, soundRoll)) {
                    buttonNumber = i;
                }
            }
        }
        window.display();
        switch (buttonNumber) {
            case -1:
                continue;
            case 0:
                MainMenu = false;
                break;
            case 1:
                ShowRecords(window, bgImage, player);
                buttonNumber = -1;
                clock.restart();
                break;
            case 2:
                return MainMenu;
            default:
                window.close();
                return MainMenu;

        }
    }
    return MainMenu;
}

void GameMenu::ShowRecords(sf::RenderWindow &window, const sf::Sprite &bgImage, Player &player){
    // Opening records menu sound
    sf::Sound sound(*FilesBank::getInstance().getSounds("other", 1));
    sound.play();

    // Edit logo
    textPause.setString("Records:");
    textPause.setOrigin(textPause.getGlobalBounds().width / 2, textPause.getGlobalBounds().height / 2);
    textPause.setPosition(menuSquare.getGlobalBounds().width, menuSquare.getGlobalBounds().height * 0.05f);

    // Edit buttons
    buttons[2].text.setString("Back to menu");
    buttons[2].text.setScale(0.7f, 0.7f);
    buttons[2].text.setOrigin(buttons[2].text.getLocalBounds().width / 2, buttons[2].text.getLocalBounds().height / 2);

    MainMenu = true;
    int buttonNumber = -1;

    float interval = 0;
    for (Button &b : buttons) {
        b.setPos(sf::Vector2f(winSize.x / 2.f, winSize.y / 4.f + interval));
        interval += 200;
    }

    sf::Sound soundRoll(*FilesBank::getInstance().getSounds("button", 0));
    sf::Sound soundClick(*FilesBank::getInstance().getSounds("button", 1));
    soundClick.setVolume(20);
    soundRoll.setVolume(10);

    // Creating table
    records.read();
    sf::Text results(records.ShowTable(50, sf::Color(sf::Color::Red)));
    results.setPosition(winSize.x / 2.f, textLogo.getGlobalBounds().height + 210);

    clock.restart();
    int fps = 0;
    while (MainMenu) {

        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();

        window.draw(bgImage);
        window.draw(menuSquare);
        window.draw(textPause);
        window.draw(results);
        ++fps;
        player.UpdatePlayerAnimation(fps);
        window.draw(*player.GetSprite());

        int currFrame = clock.getElapsedTime().asMilliseconds() / 16;
        if (currFrame > 10) {
            window.draw(buttons[2].button);
            window.draw(buttons[2].text);

            if (buttons[2].Clicked(window, soundClick, soundRoll)) {
                buttonNumber = 2;
            }
        }
        window.display();
        if (buttonNumber == 2){
            textPause.setString("Paused");
            textPause.setOrigin(textPause.getGlobalBounds().width / 2, textPause.getGlobalBounds().height / 2);
            buttons[2].text.setString("Exit");
            buttons[2].text.setScale(1,1);
            buttons[2].text.setOrigin(
                    buttons[2].text.getGlobalBounds().width / 2, buttons[2].text.getGlobalBounds().height / 2
                    );
            return;
        }
    }
}

void GameMenu::InitializeButtons() {
    FilesBank::getInstance().AddFiles("button", "magicButtons.png");

    std::string nameOfButtons[] = { "Play", "Records", "Exit" };
    for (const std::string &nameOfButton : nameOfButtons) {
        buttons.emplace_back(
                *FilesBank::getInstance().GetFile("button", 0),
                sf::Vector2f(winSize.x / 6.45f, winSize.y / 9.36f),
                sf::Vector2f(78, 220),
                sf::Vector2f(445, 173),
                sf::Vector2f(winSize.x / 3.7f, winSize.y / 3.3f),
                sf::Vector2f(678, 151),
                sf::Vector2f(519, 326),
                nameOfButton,
                *FilesBank::getInstance().getFonts("timer", 0)
        );
    }
}

void GameMenu::InitializeText() {
    textPause.setFont(*FilesBank::getInstance().getFonts("timer", 0));
    textPause.setString("Paused");
    textPause.setCharacterSize(120);
    textPause.setOrigin(textPause.getGlobalBounds().width / 2, textPause.getGlobalBounds().height / 2);

    name.setFont(*FilesBank::getInstance().getFonts("timer", 0));
    name.setString("Name: ");
    name.setCharacterSize(40);
    name.setOrigin(name.getGlobalBounds().width / 2, name.getGlobalBounds().height / 2);
}

void GameMenu::InitializeLogos() {
    menuSquare.setPosition(sf::Vector2f(winSize.x * 0.25f, 0));
    menuSquare.setSize(sf::Vector2f(winSize.x * 0.5f, winSize.y));
    menuSquare.setFillColor(sf::Color(20,20,20, 180));
    textPause.setPosition(menuSquare.getGlobalBounds().width, menuSquare.getGlobalBounds().height * 0.05f);

    textLogo.setFont(*FilesBank::getInstance().getFonts("timer", 0));
    textLogo.setString("Higher Ground");
    textLogo.setCharacterSize(120);
    textLogo.setOrigin(textLogo.getGlobalBounds().width / 2, textLogo.getGlobalBounds().height / 2);
    textLogo.setPosition(menuSquare.getGlobalBounds().width, menuSquare.getGlobalBounds().height * 0.05f);

    NickName.setFont(*FilesBank::getInstance().getFonts("timer", 0));
    NickName.setOrigin(name.getGlobalBounds().width / 2, name.getGlobalBounds().height / 2);
    NickName.setCharacterSize(40);
}