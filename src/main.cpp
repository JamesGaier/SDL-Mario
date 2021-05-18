#include "Game.hpp"


int main(int argv, char* argc[])
{
    auto window = std::make_unique<smb::Game>("Super Mario Brothers clone", 800, 600);
}