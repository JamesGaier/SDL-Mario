#pragma once
#include "File.hpp"
#include <SDL.h>
#include <map>
#include <vector>

namespace smb
{

struct Resource
{
    std::vector<SDL_Rect> coords;
    SDL_Texture *texture;
};

class ResourceFactory
{
  public:
    static void loadResource(const std::string &coordsFile, const std::string &imageFile, const std::string &name,
                             SDL_Renderer *renderer);

    static Resource *getResource(const std::string &name);

  private:
    inline static std::map<std::string, Resource> resources;
};

} // namespace smb
