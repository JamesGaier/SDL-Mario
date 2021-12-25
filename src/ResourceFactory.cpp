#include "ResourceFactory.hpp"

namespace smb
{

void ResourceFactory::loadResource(const std::string &coordsFile, const std::string &imageFile,
                                    const std::string &name, SDL_Renderer *renderer)
{
    auto tilesStr = file::read_file(coordsFile);
    auto tiles = file::parse_spritesheet(tilesStr);

    auto *image{file::loadImage(file::toAbsolute(imageFile), renderer)};
    resources.emplace(name, Resource{tiles, image});
}

Resource *ResourceFactory::getResource(const std::string &name)
{
    if (resources.count(name) != 0)
    {
        return &resources.at(name);
    }
    else
    {
        return nullptr;
    }
}

} // namespace smb
