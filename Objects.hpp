#include "Includes.hpp"

class Object {
protected:
    sf::CircleShape shape;
public:
    virtual void drawFigure(sf::RenderWindow&) = 0;
    Object(sf::Color, sf::Vector2f);
};

Object::Object(sf::Color color, sf::Vector2f position) {
    shape.setFillColor(color);
    shape.setPosition(position);
}

class Sun : public Object {
public:
    Sun() : Object(sf::Color(255, 255, 0), sf::Vector2f(1700, 0)) { shape.setRadius(100); }
    void drawFigure(sf::RenderWindow& window) override {
        window.draw(shape);
    }
};
