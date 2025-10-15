#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "chess/game.h"

TEST_CASE("Game initialization") {
    chess::Game game;

    SUBCASE("Game should not be over at start") {
        CHECK_FALSE(game.isGameOver());
    }

    SUBCASE("Initial status should indicate game in progress") {
        std::string status = game.getStatus();
        CHECK(status.find("In Progress") != std::string::npos);
    }
}

TEST_CASE("Game status") {
    chess::Game game;

    SUBCASE("Status includes move count") {
        std::string status = game.getStatus();
        CHECK(status.find("Move") != std::string::npos);
    }
}
