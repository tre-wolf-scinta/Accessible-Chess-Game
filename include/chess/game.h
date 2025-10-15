#ifndef CHESS_GAME_H
#define CHESS_GAME_H

#include <string>

namespace chess {

class Game {
public:
    Game();
    ~Game() = default;

    void run();
    void displayBoard() const;
    bool makeMove(const std::string& move);
    bool isGameOver() const;
    std::string getStatus() const;

private:
    bool gameOver;
    int moveCount;
};

} // namespace chess

#endif // CHESS_GAME_H
