#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>
#include "TileType.h"

class TileMap {
private:
    int width, height;
    std::vector<TileType> tiles;

public:
    static const int TILE_X = 32;
    static const int TILE_Y = 32;

    TileMap(int width, int height)
        : width(width), height(height)
    {
        tiles.resize(width * height, TileType::Grass);
    }

    void setTile(int x, int y, TileType type) {
        if (x >= 0 && x < width && y >= 0 && y < height)
            tiles[y * width + x] = type;
    }

    TileType getTile(int x, int y) const {
        return tiles[y * width + x];
    }

    void draw(sf::RenderWindow& window) {
        sf::RectangleShape rect(sf::Vector2f(TILE_X, TILE_Y));

        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {

                TileType t = getTile(x, y);

                if (t == TileType::Grass)
                    rect.setFillColor(sf::Color::Green);
                else if (t == TileType::Wall)
                    rect.setFillColor(sf::Color(0, 0, 0, 0));

                rect.setPosition({ x * TILE_X, y * TILE_Y });
                window.draw(rect);

                sf::RectangleShape border(sf::Vector2f(TILE_X, TILE_Y));
                border.setPosition({ x * TILE_X, y * TILE_Y });
                border.setFillColor(sf::Color::Transparent);
                border.setOutlineColor(sf::Color::Black);
                border.setOutlineThickness(1);
                window.draw(border);
            }
        }
    }

    void save(const std::string& filename) {
        std::ofstream file(filename);
        for (auto& tile : tiles)
            file << static_cast<int>(tile) << " ";
    }

    void load(const std::string& filename) {
        std::ifstream file(filename);
        int v;

        for (auto& tile : tiles) {
            file >> v;
            tile = static_cast<TileType>(v);
        }
    }
};
