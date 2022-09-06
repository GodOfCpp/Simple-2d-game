#include "Includes.hpp"


//main logic, returns true if we exiting game or will to open menu
bool startGame(sf::RenderWindow& window) {
    sf::Clock clock; //время для игры
    InitMap(); //создаем карту
    sf::Event event;
    Sun sun;
    bool pause = false;

    Player player("Sprites//2 Punk//Punk");
    getTiles();

    while (window.isOpen()) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {pause = true; /*askMenu.draw(window);*/}
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {pause = false;}
       // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {return false;}
        if(pause) {clock.restart(); continue; }
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
        }

        float time = update(player, clock);
        window.clear(sf::Color(170,230,255));
        draw_map(window);
        player.drawPlayer(window);
        sun.drawFigure(window);
        window.display();
    }

}

//This is main method to play the game (including menu e.t.c.)
void gameRunning(sf::RenderWindow& window) {
    if (startGame(window)) { gameRunning(window); }
   // if (menu(window)) gameRunning(window);
}



int main()
{
    //ShowWindow(GetConsoleWindow(), SW_HIDE);
    sf::RenderWindow window(sf::VideoMode(WIDTH,HEIGHT), "Game(Demo).exe"/*, sf::Style::Fullscreen*/); //
    gameRunning(window);
    return 0;
}
