#include <catch_amalgamated.hpp>
#include "File.hpp"
#include <filesystem>


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
}

}

