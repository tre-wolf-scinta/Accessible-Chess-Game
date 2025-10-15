#include <iostream>
#include "chess/game.h"

int main() {
    std::cout << "Accessible Chess Game\n";
    std::cout << "=====================\n\n";

    chess::Game game;
    game.run();

    return 0;
}
