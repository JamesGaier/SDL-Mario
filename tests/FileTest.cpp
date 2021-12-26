#include <catch_amalgamated.hpp>
#include <filesystem>
#include <SDL.h>
#include "File.hpp"


namespace smb
{

TEST_CASE("File Utility Test", "[File Utility Functions]")
{
    auto absolutePath = file::toAbsolute("testFile.txt", "../tests");
    auto expectedPath = "../tests/testFile.txt";

    CHECK_THAT(absolutePath, 
            Catch::Matchers::EndsWith(expectedPath));
    

    auto fileData = file::read_file(absolutePath);
    auto expectedData = "Foo 123";
     
    CHECK_THAT(fileData, Catch::Matchers::StartsWith(expectedData));

    const auto coords = "1, 1, 2, 2\n"
                        "1, 3, 4, 5\n"
                        "1, 2, 4, 4\n";

    const std::vector<int> expected{1,1,2,2,1,3,4,5,1,2,4,4};

    CHECK(file::parse_coords(coords) == expected);

    const auto level = "0,2,\n"
                       "1,1,\n";

    const auto levelCoords = file::parse_level(level);
    
    CHECK(levelCoords[0][0] == 0);
    CHECK(levelCoords[0][1] == 2);
    CHECK(levelCoords[1][0] == 1);
    CHECK(levelCoords[1][1] == 1);

    const std::vector<SDL_Rect> expectedRect{
        SDL_Rect{1, 1, 2, 2},
        SDL_Rect{1, 3, 4, 5},
        SDL_Rect{1, 2, 4, 4}
    };

    auto result = file::parse_spritesheet(coords);

    auto equal = std::equal(result.begin(), result.end(), expectedRect.begin(), [](const SDL_Rect &lhs, const SDL_Rect &rhs) {
        return lhs.h == rhs.h && lhs.w == rhs.w 
        && lhs.x == rhs.x && lhs.y == rhs.y;
    });

    CHECK(equal);
}

}

