#include <catch_amalgamated.hpp>
#include <sstream>
#include "Math.hpp"


namespace smb
{

TEST_CASE("Math Test", "[Math]")
{
    SECTION("Fill Out Vector, Test Operators")
    {

        math::Vec2f defaultVector;
        CHECK(defaultVector.x == 0);
        CHECK(defaultVector.y == 0);

        math::Vec2f vector{2.2f, 5.3f}; 
        CHECK(vector.x == 2.2f);
        CHECK(vector.y == 5.3f);

        SECTION("Add two vectors")
        {
            math::Vec2f vectorA{2.0f, 4.0f}; 
            math::Vec2f vectorB{1.1f, 2.2f}; 
            auto result = vectorA + vectorB; 
            math::Vec2f expected{3.1f, 6.2f}; 

            CHECK(result.x == expected.x);
            CHECK(result.y == expected.y);
        }

        SECTION("Subtract two vectors")
        {
            math::Vec2f vectorA{2.0f, 4.0f}; 
            math::Vec2f vectorB{1.1f, 2.2f}; 
            auto result = vectorA - vectorB; 
            math::Vec2f expected{0.9f, 1.8f}; 

            CHECK(result.x == expected.x);
            CHECK(result.y == expected.y);
        }

        SECTION("Add a vector and a float")
        {

            math::Vec2f vectorA{3.0f, 1.0f}; 
            math::Vec2f expected{8.0f, 6.0f}; 
            SECTION("Float on the left")
            {
                auto result = 5 + vectorA;

                CHECK(result.x == expected.x);
                CHECK(result.y == expected.y);
            }

            SECTION("Float on the right")
            {
                auto result = vectorA + 5;

                CHECK(result.x == expected.x);
                CHECK(result.y == expected.y);
            }
        }

        SECTION("Subtract a vector and a float")
        {
            math::Vec2f vectorA{3.0f, 1.0f}; 
            SECTION("Float on the left")
            {
                math::Vec2f expected{2.0f, 4.0f}; 
                auto result = 5 - vectorA;

                CHECK(result.x == expected.x);
                CHECK(result.y == expected.y);
            }

            SECTION("Float on the right")
            {
                math::Vec2f expected{-2.0f, -4.0f}; 
                auto result = vectorA - 5;

                CHECK(result.x == expected.x);
                CHECK(result.y == expected.y);
            }
        }

        SECTION("Multiply a vector and a float")
        {
            math::Vec2f vectorA{5.0f, 2.2f}; 
            math::Vec2f expected{25.0f, 11.0f}; 
            SECTION("Float on the left")
            {
                auto result =  5 * vectorA ; 
                
                CHECK(result.x == expected.x);
                CHECK(result.y == expected.y);
            }

            SECTION("Float on the right")
            {
                auto result =  vectorA * 5; 
                
                CHECK(result.x == expected.x);
                CHECK(result.y == expected.y);
            }
        }
        
        SECTION("Divide a vector and a float")
        {
            math::Vec2f vectorA{5.0f, 2.2f}; 

            SECTION("Float on the left")
            {
                math::Vec2f expected{0.4f, 0.91f}; 

                auto result = 2 / vectorA;
                CHECK(result.x == expected.x);

                Catch::Approx approx = Catch::Approx(result.y).epsilon(0.01);

                CHECK(approx == expected.y);
            }

            SECTION("Float on the right")
            {
                math::Vec2f expected{2.5f, 1.1f}; 

                auto result = vectorA / 2;
                CHECK(result.x == expected.x);
                CHECK(result.y == expected.y);
            }
        }
    }

    SECTION("Fill Out Rectangle, Test << operator")
    {
        // Filling out fields
        math::Vec2f position{2.1f, 3.0f};
        math::Vec2f size{32.0f, 64.0f};
        math::Rect tile{position, size}; 

        CHECK(tile.pos.x == 2.1f);
        CHECK(tile.pos.y == 3.0f);
        CHECK(tile.size.x == 32.0f);
        CHECK(tile.size.y == 64.0f);

        // Checking that ostream is printing out values to stdout properly
        std::stringstream ss;
        ss << tile;

        CHECK(ss.str() == "[Rect] position x: 2.1"
                "  position y: 3  size x: 32  size y: 64");
    }
}

}

