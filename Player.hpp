#pragma once
#include "Includes.hpp"

enum Direction {STOP = 0, RIGHT, LEFT, JUMP};
float timer = 0;
class Player {
private:
    float dx = 0, dy = 0, x, y;
    sf::Image image_run;
    sf::Sprite sprite_run;
    sf::Texture texture_run;
    float CurrentFrame_run = 0;
    float speed = 0;

    sf::Image image_jump;
    sf::Sprite sprite_jump;
    sf::Texture texture_jump;
    float CurrentFrame_jump = 0;

    sf::Image image_idle;
    sf::Sprite sprite_idle;
    sf::Texture texture_idle;
    float CurrentFrame_idle = 0;

    bool isMove, onGround;

    Direction dir;
public:
    const int w_sprite = 48, h_sprite = 48;
    Player(std::string);

    void SetOnGroundFalse () { onGround = false; }
    void setSpritePosition_run() { sprite_run.setPosition(this->x /*+ w_sprite/2*/,this->y /*+h_sprite/2)*/); }
    void setSpritePosition_idle() { sprite_idle.setPosition(this->x, this->y); }
    void setSpritePosition_jump() { sprite_jump.setPosition(this->x, this->y); }
    void setSpeedToZero() { speed = 0; }
    void setDX(float dx) { this->dx = dx; }
    void setDY(float dy) { this->dy = dy; }
    void setX(float x) {this->x = x; }
    void setY(float y) {this->y = y; }

    float getX() const { return x; }
    float getY() const { return y; }
    float getDX() const { return dx; }
    float getDY() const { return dy; }
    float getSpeed() const { return speed; }
    bool IsMove() const { return isMove; }
    bool OnGround() const { return onGround; }
    Direction getDir() const { return dir; }
    sf::Sprite getSprite_run()  const { return sprite_run;  }
    sf::Sprite getSprite_jump() const { return sprite_jump; }
    sf::Sprite getSprite_idle() const { return sprite_idle; }

    void Move(float);
    void checkCollisionWithMap(float, float);
    void drawPlayer(sf::RenderWindow&);
};

Player::Player(std::string sprite_path) {
    image_run.loadFromFile(sprite_path + "_run.png");
    image_run.createMaskFromColor(sf::Color(255,255,255));
    texture_run.loadFromImage(image_run);
    sprite_run.setTexture(texture_run);
    sprite_run.setTextureRect(sf::IntRect(0,0,48,48));


    image_jump.loadFromFile(sprite_path + "_jump.png");
    image_jump.createMaskFromColor(sf::Color(255,255,255));
    texture_jump.loadFromImage(image_jump);
    sprite_jump.setTexture(texture_jump);
    sprite_jump.setTextureRect(sf::IntRect(0,0,48,48));

    image_idle.loadFromFile(sprite_path + "_idle.png");
    image_idle.createMaskFromColor(sf::Color(255,255,255));
    texture_idle.loadFromImage(image_idle);
    sprite_idle.setTexture(texture_idle);
    sprite_idle.setTextureRect(sf::IntRect(0,0,48,48));

    x = 100, y = 100;
    isMove = false; onGround = false;
}


void Player::Move(float time) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        sprite_run.setScale(-1,1);
        sprite_jump.setScale(-1,1);
        dir = LEFT;
        speed = 0.1;

        if (onGround) {
            CurrentFrame_jump = 0;
            CurrentFrame_run += 0.005*time;
            if (CurrentFrame_run >=6) CurrentFrame_run = 0;
            sprite_run.setTextureRect(sf::IntRect(48*static_cast<int>(CurrentFrame_run), 0, 48, 48));
        }

        if (!onGround) {
            dir = JUMP;
            CurrentFrame_jump += 0.005*time;
            if (CurrentFrame_jump >= 4) CurrentFrame_jump = 0;
            sprite_jump.setTextureRect(sf::IntRect(48*static_cast<int>(CurrentFrame_jump), 0, 48, 48));
        }

    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        sprite_run.setScale(1,1);
        sprite_jump.setScale(1,1);
        dir = RIGHT;
        speed = 0.1;
        if (onGround) {
            CurrentFrame_jump = 0;
            CurrentFrame_run += 0.005*time;
            if (CurrentFrame_run >=6) CurrentFrame_run = 0;
            sprite_run.setTextureRect(sf::IntRect(48*static_cast<int>(CurrentFrame_run), 0, 48, 48));
        }
        if (!onGround) {
            dir = JUMP;
            CurrentFrame_jump += 0.005*time;
            if (CurrentFrame_jump >= 4) CurrentFrame_jump = 0;
            sprite_jump.setTextureRect(sf::IntRect(48*static_cast<int>(CurrentFrame_jump), 0, 48, 48));
        }
    }
    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) && onGround) {
        if (dir == RIGHT) sprite_idle.setScale(1,1);
        if (dir == LEFT)  sprite_idle.setScale(-1,1);
        dy = -0.6; SetOnGroundFalse();
        dir = JUMP;
        //speed = 0.1;
    }

     if (!speed && onGround) {
        if (dir == RIGHT) sprite_idle.setScale(1,1);
        if (dir == LEFT)  sprite_idle.setScale(-1,1);
        dir = STOP;
        CurrentFrame_idle += 0.005*time;
        if (CurrentFrame_idle >=4) CurrentFrame_idle = 0;
        sprite_idle.setTextureRect(sf::IntRect(48*static_cast<int>(CurrentFrame_idle), 0, 48, 48));
    }
    if (!onGround) {
        /*CurrentFrame_jump += 0.005*time;
        if (dir == RIGHT) sprite_run.setScale(1,1);
        if (dir == LEFT) sprite_run.setScale(-1,1);
        if (CurrentFrame_jump >= 4) CurrentFrame_jump = 0;
        sprite_jump.setTextureRect(sf::IntRect(48*static_cast<int>(CurrentFrame_jump), 0, 48, 48));
        std::cout << static_cast<int>(CurrentFrame_jump) << '\n'; */

    }
    //if (onGround && timer != 0) {std::cout << static_cast<int>(timer) << '\n'; timer = 0;}

}

void Player::checkCollisionWithMap(float Dx, float Dy) {
    for (int i = y/64; i < (y + h_sprite)/64; i++) {
        for (int j = x/64; j < (x + w_sprite)/64; j++) {
            if (Map[i][j] == '0') {
                if (Dy > 0) { y = i*64 - h_sprite; Dy = 0; onGround = true; }
                if (Dy < 0) { y = i*64 + 64; Dy = 0; }
                if (Dx > 0) { x = j * 64 - w_sprite; }
                if (Dx < 0) { x = j * 64 + 64; }
            }
        }
    }
}

void Player::drawPlayer(sf::RenderWindow& window) {
    switch (this->dir) {
            case RIGHT:
                window.draw(this->sprite_run);
                break;
            case LEFT:
                window.draw(this->sprite_run);
                break;
            case JUMP:
                window.draw(this->sprite_jump);
                break;
            case STOP:
                window.draw(this->sprite_idle);
                break;
        }
}
