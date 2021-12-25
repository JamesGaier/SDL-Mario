#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <filesystem>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

namespace smb
{

enum class TileType
{
    AIR = 0,
    GROUND = 1,
    SPAWN,
    BREAKABLE,
    UP_PIPE,
    LEFT_PIPE,
    RIGHT_PIPE,
    DOWN_PIPE,
    MUSHROOM,
    QUESTION,
    INVISIBLE,
    SOLID,
    FLAG_POLE,
    CASTLE
};

enum class TileColor
{
    BROWN,
    BLUE,
    WHITE,
    GREEN
};

namespace file
{
    std::string toAbsolute(const std::string &path, const std::string &parent = "../src");
    std::string read_file(const std::string &path);
    std::vector<int> parse_coords(const std::string &coords);
    std::vector<std::vector<int>> parse_level(const std::string &level);
    std::vector<SDL_Rect> parse_spritesheet(const std::string &coords);
    SDL_Texture *loadImage(const std::string &path, SDL_Renderer *renderer);
}

} // namespace smb
