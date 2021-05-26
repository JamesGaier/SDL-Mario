#include "Util.hpp"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>


namespace smb
{
std::string read_file(const std::string& path)
{
    namespace fs = std::filesystem;
    fs::path programPath = fs::current_path();
    programPath /= "../res";
    programPath /= path;
    std::ifstream file{programPath.string()};
    std::stringstream ss;

    std::string line;
    while (getline(file, line))
    {
        ss << line;
    }
    return ss.str();
}

std::vector<SDL_Rect> parse_coords(const std::string& coords)
{
    std::vector<int> coords_num;
    auto idx_s = 0u;
    auto idx_e = 0u;
    while(idx_s < coords.length() && idx_s < coords.length())
    {
        while(isdigit(coords[idx_e]))
        {
            ++idx_e;
        }
        coords_num.push_back(std::stoi(coords.substr(idx_s, idx_e - idx_s)));
        idx_s = idx_e;

        while(coords[idx_s] == ' ' || coords[idx_s] == ',' || coords[idx_s] == '\n')
        {
            ++idx_s;
        }
        idx_e = idx_s;
    }

    

    std::vector<SDL_Rect> result;
    auto k = 0u;
    for(auto i = 0u; i < coords_num.size(); ++i)
    {
        if(k == 3 && i != 0)
        {
            result.push_back({coords_num[i - 3], coords_num[i - 2], coords_num[i - 1], coords_num[i]});
            k = 0;
        }
        else
        {
            ++k;
        }
    }

    return result;
}

}
