#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include <thread>
#include <chrono>
#include <time.h>
#include "SFML/Graphics.hpp"
#include <windows.h>
#include "World.hpp"
#include "Map.hpp"
const int WIDTH = 1920;
const int HEIGHT = 1080;
#include "Player.hpp"
#include "Menu.hpp"
#include "Objects.hpp"


float update(Player& player, sf::Clock& clock) {
    float time = clock.getElapsedTime().asMicroseconds();
    clock.restart();
    time /= 800;
    player.Move(time);
    //std::cout << ' ' << player.getDir() << '\n';
    switch (player.getDir()) {
        case RIGHT:
            player.setDX(player.getSpeed());
            break;
        case LEFT:
            player.setDX(-player.getSpeed());
            break;
        case JUMP:
            break;
        case STOP:
            player.setDX(0);
            player.setDY(0);
            break;
    }
    player.setX(player.getX() + player.getDX()*time);
    player.checkCollisionWithMap(player.getDX(), 0.0);
    if (!player.OnGround())  player.setY(player.getY() + player.getDY()*time);
    player.checkCollisionWithMap(0.0, player.getDY());
    if (!player.IsMove()) player.setSpeedToZero();
    player.setSpritePosition_run();
    player.setSpritePosition_idle();
    player.setSpritePosition_jump();
    player.setDY(player.getDY() + 0.0015*time);
    return time;
}
