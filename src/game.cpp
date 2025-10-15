#include "chess/game.h"
#include <iostream>

namespace chess {

Game::Game() : gameOver(false), moveCount(0) {
    std::cout << "Initializing chess game...\n";
}

void Game::run() {
    std::cout << "Welcome to Accessible Chess!\n";
    std::cout << "This is a chess game designed with accessibility in mind.\n\n";

    displayBoard();

    std::cout << "\nGame setup complete. Ready to play!\n";
    std::cout << "Status: " << getStatus() << "\n";
}

void Game::displayBoard() const {
    std::cout << "\n  a b c d e f g h\n";
    std::cout << "8 r n b q k b n r 8\n";
    std::cout << "7 p p p p p p p p 7\n";
    std::cout << "6 . . . . . . . . 6\n";
    std::cout << "5 . . . . . . . . 5\n";
    std::cout << "4 . . . . . . . . 4\n";
    std::cout << "3 . . . . . . . . 3\n";
    std::cout << "2 P P P P P P P P 2\n";
    std::cout << "1 R N B Q K B N R 1\n";
    std::cout << "  a b c d e f g h\n";
}

bool Game::makeMove(const std::string& move) {
    if (gameOver) {
        return false;
    }

    moveCount++;
    // Move implementation will go here
    return true;
}

bool Game::isGameOver() const {
    return gameOver;
}

std::string Game::getStatus() const {
    if (gameOver) {
        return "Game Over";
    }
    return "In Progress - Move " + std::to_string(moveCount);
}

} // namespace chess
