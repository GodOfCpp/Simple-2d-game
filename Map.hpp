#pragma once
#include "Includes.hpp"

const int HEIGHT_MAP = 17;
const int WIDTH_MAP = 30;

std::vector<std::vector<sf::IntRect>> tiles(14, std::vector<sf::IntRect>(7));

void getTiles() {
    for (int i = 0; i < 14; i++) {
        for (int j = 0; j < 7; j++) {
            tiles[i][j] = sf::IntRect(i*64,j*64,64,64);
        }
    }
}

sf::String Map[HEIGHT_MAP] = {
"                              ",
"                              ",
"                              ",
"                              ",
"                              ",
"                              ",
"                              ",
"                              ",
"000000000000000000000000000000",
"ggggggggggggggggggggggggggwwww",
"ggggggggggggggggggggggggggwwww",
"ggggggggggggggggggggggggggwwww",
"ggggggggggggggggggggggggggwwww",
"ggggggggggggggggggggggggggwwww",
"ggggggggggggggggggggggggggwwww",
"ggggggggggggggggggggggggggwwww",
"ggggggggggggggggggggggggggwwww",
};

sf::Image map_image;
sf::Texture map_texture;
sf::Sprite map_sprite;

void InitMap() {
    map_image.loadFromFile("Sprites\\Map_tiles.png");
    map_image.createMaskFromColor(sf::Color(255,255,255));
    map_texture.loadFromImage(map_image);
    map_sprite.setTexture(map_texture);
}

void draw_map(sf::RenderWindow& window) {
    for (int i = 0; i < HEIGHT_MAP; i++)
    for (int j = 0; j < WIDTH_MAP; j++) {
        //if (Map[i][j] == ' ') { map_sprite.setTextureRect(tiles[6][0]); map_sprite.setPosition(j*64, i*64); }
        if (Map[i][j] == 'g') { map_sprite.setTextureRect(tiles[3][0]); map_sprite.setPosition(j*64, i*64); }
        if (Map[i][j] == 'u') { map_sprite.setTextureRect(tiles[4][0]); map_sprite.setPosition(j*64, i*64); }
        if (Map[i][j] == '0') { map_sprite.setTextureRect(tiles[0][0]); map_sprite.setPosition(j*64, i*64);    }
        if (Map[i][j] == 'w') { map_sprite.setTextureRect(tiles[4][1]); map_sprite.setPosition(j*64, i*64);    }
        window.draw(map_sprite);
    }
}



