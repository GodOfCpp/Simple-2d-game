#pragma once
#include "Includes.hpp"

enum Menu {QUIT = 0, START, ABOUT} button;

class Button {
public:
    sf::Image img;
    sf::Texture texture;
    sf::Sprite sprite;
    Button(std::string path) {
        img.loadFromFile("Sprites//"+path);
        img.createMaskFromColor(sf::Color(255,255,255));
        texture.loadFromImage(img);
        sprite.setTexture(texture);
    }

};

Button start("Start_button.png"), about("About_button.png"), quit("Exit_button.png");


bool menu(sf::RenderWindow& window) {
    sf::Texture t_bg;
    t_bg.loadFromFile("Sprites//Background.png");
    sf::Sprite s_bg(t_bg);


    start.sprite.setPosition(100, 200);
    about.sprite.setPosition(110, 400);
    quit.sprite.setPosition(100, 600);
    s_bg.setPosition(0,0);

    while (true) {
        int counter = 0;
        start.sprite.setColor(sf::Color::White);
        about.sprite.setColor(sf::Color::White);
        quit.sprite.setColor(sf::Color::White);
        window.clear(sf::Color(129,181,221));

        if (sf::IntRect(100, 200, 250, 90).contains(sf::Mouse::getPosition(window))) { start.sprite.setColor(sf::Color::Green); button = START; }
		else if (sf::IntRect(110, 400, 240, 90).contains(sf::Mouse::getPosition(window))) { about.sprite.setColor(sf::Color::Green); button = ABOUT; }
		else if (sf::IntRect(100, 600, 250, 90).contains(sf::Mouse::getPosition(window))) { quit.sprite.setColor(sf::Color::Green); button = QUIT; }

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
		    switch (button) {
                case START:
                    return true;
                    break;
                case QUIT:
                    window.close();
                    return 0;
                    //
		    }
			/*if (button == START) //если нажали первую кнопку, то выходим из меню
			//if (menuNum == 2) { window.draw(sprite_about); window.display(); while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)); }
			else if (button == QUIT)  { window.close(); i } */

		}

		window.draw(s_bg);
		window.draw(start.sprite);
		//window.draw(options.sprite);
		//window.draw(score.sprite);
		//window.draw(help.sprite);
		window.draw(about.sprite);
		window.draw(quit.sprite);

		window.display();
    }
}

