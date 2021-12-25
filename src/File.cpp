#include "File.hpp"

namespace smb::file
{
    std::string toAbsolute(const std::string &path, const std::string &parent)
    {
        namespace fs = std::filesystem;
        fs::path programPath = fs::current_path().parent_path();
        programPath /= parent;
        programPath /= path;
        return programPath.string();
    }

    std::string read_file(const std::string &path)
    {
        auto absPath = toAbsolute(path);
        std::ifstream file{absPath};
        std::stringstream ss;

        std::string line;
        while (getline(file, line))
        {
            ss << line;
            ss << '\n';
        }
        return ss.str();
    } 


    std::vector<int> parse_coords(const std::string &coords)
    {
        std::vector<int> coords_num;
        auto idx_s = 0u;
        auto idx_e = 0u;
        while (idx_s < coords.length() && idx_e < coords.length())
        {
            while (isdigit(coords[idx_e]))
            {
                ++idx_e;
            }
            coords_num.push_back(std::stoi(coords.substr(idx_s, idx_e - idx_s)));
            idx_s = idx_e;

            while (coords[idx_s] == ' ' || coords[idx_s] == ',' || coords[idx_s] == '\n')
            {
                ++idx_s;
            }
            idx_e = idx_s;
        }

        return coords_num;
    }

    std::vector<std::vector<int>> parse_level(const std::string &level)
    {
        std::vector<std::vector<int>> result;
        auto idx_s = 0u;
        auto idx_e = 0u;
        auto row = 0u;

        for (auto i = 0u; i < level.length(); ++i)
        {
            if (level[i] == '\n')
            {
                result.push_back(std::vector<int>{});
            }
        }

        while (idx_s < level.length() && idx_e < level.length())
        {
            while (isdigit(level[idx_e]))
            {
                ++idx_e;
            }

            result[row].push_back(std::stoi(level.substr(idx_s, idx_e - idx_s)));
            idx_s = idx_e;

            while (level[idx_s] == ' ' || level[idx_s] == ',' || level[idx_s] == '\n')
            {
                if (level[idx_s] == '\n')
                {
                    ++row;
                }
                ++idx_s;
            }
            idx_e = idx_s;
        }

        return result;
    }

    std::vector<SDL_Rect> parse_spritesheet(const std::string &coords)
    {
        auto coords_num = parse_coords(coords);
        std::vector<SDL_Rect> result;
        auto k = 0u;
        for (auto i = 0u; i < coords_num.size(); ++i)
        {
            if (k == 3 && i != 0)
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

    SDL_Texture *loadImage(const std::string &path, SDL_Renderer *renderer)
    {
        SDL_Surface *loadedSurface = IMG_Load(path.c_str());

        if (loadedSurface == nullptr)
        {
            std::stringstream ss;
            ss << "Unable to load image " << path.c_str() << "SDL_image Error: " << IMG_GetError();
            throw std::runtime_error(ss.str());
        }
        else
        {
            auto *texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
            if (texture == nullptr)
            {
                std::cout << "Unable to create texture from " << path << "! SDL Error: " << SDL_GetError() << std::endl;
            }

            SDL_FreeSurface(loadedSurface);
            return texture;
        }
    }

}
