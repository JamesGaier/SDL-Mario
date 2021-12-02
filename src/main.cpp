#include "Game.hpp"

int main()
{
    constexpr static auto WIDTH = 1600;
    constexpr static auto HEIGHT = 960;
    constexpr static auto TITLE = "Super Mario Brothers clone";
    auto window = std::make_unique<smb::Game>(TITLE, WIDTH, HEIGHT);
}