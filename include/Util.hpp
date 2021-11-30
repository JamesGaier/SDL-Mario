#pragma once
#include <SDL.h>
#include <array>
#include <memory>
#include <vector>

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


std::string read_file(const std::string &path);

std::string toAbsolute(const std::string &path, const std::string &parent = "../res");

std::vector<int> parse_coords(const std::string &coords);

std::vector<std::vector<int>> parse_level(const std::string &coords);

std::vector<SDL_Rect> parse_spritesheet(const std::string &coords);

SDL_Texture *loadImage(const std::string &path, SDL_Renderer *renderer);

} // namespace smb
