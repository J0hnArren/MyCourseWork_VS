#include "Button.h"

Button::Button(
        sf::Texture &texture_, // texture with both button states
        const sf::Vector2f &buttonSize, // size of 1 rectangle
        const sf::Vector2f &beginPosTexture, // 1 texture start position in pixel
        const sf::Vector2f &textureRectSize, // 1 texture size in pixels
        const sf::Vector2f &nextButtonSize, // size of 2 rectangle
        const sf::Vector2f &nextBeginPosTexture, // 2 texture start position
        const sf::Vector2f &nextTextureRectSize, // 2 texture size in pixels
        const std::string &buttonName, // text on the button
        const sf::Font &font) {
    size1 = buttonSize;
    button.setSize(size1);
    button.setOrigin(size1.x / 2, size1.y / 2);
    button.setTexture(&texture_);
    beginRect = beginPosTexture;
    sizeRect = textureRectSize;
    button.setTextureRect(sf::IntRect(beginRect.x, beginRect.y, sizeRect.x, sizeRect.y));

    size2 = nextButtonSize * 0.75f;
    nextBeginRect = nextBeginPosTexture;
    nextSizeRect = nextTextureRectSize;

    text.setFont(*FilesBank::getInstance().getFonts("timer", 0));
    text.setString(buttonName);
    text.setCharacterSize(80);
    text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2);
}

void Button::setPos(const sf::Vector2f &position) {
    button.setPosition(position);
    text.setPosition(button.getPosition().x, button.getPosition().y - 20);
    container = sf::IntRect(button.getPosition().x - size1.x / 2,
                            button.getPosition().y - size1.y / 2,
                            size1.x, size1.y);
}

bool Button::Clicked(sf::RenderWindow& window, sf::Sound& soundClick, sf::Sound& soundRoll) {
    int currentFrame = clock.getElapsedTime().asMilliseconds() / 16;
    isClick = false;

    if (container.contains(sf::Mouse::getPosition(window))) {
        button.setSize(size2);
        button.setOrigin(size2.x / 2, size2.y / 2);
        button.setTextureRect(
                sf::IntRect(nextBeginRect.x, nextBeginRect.y, nextSizeRect.x, nextSizeRect.y)
        );
        text.setCharacterSize(90);
        if (currentFrame > 10){
            soundRoll.play();
        }
        text.setPosition(button.getPosition().x - 20, button.getPosition().y - 40);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && currentFrame > 20) {
            isClick = true;
            soundClick.play();
            clock.restart();
        }
    } else {
        button.setSize(size1);
        button.setOrigin(size1.x / 2, size1.y / 2);
        button.setTextureRect(
                sf::IntRect(beginRect.x, beginRect.y, sizeRect.x, sizeRect.y)
        );
        text.setCharacterSize(80);
        text.setPosition(button.getPosition().x, button.getPosition().y - 20);
    }

    return isClick;
}
