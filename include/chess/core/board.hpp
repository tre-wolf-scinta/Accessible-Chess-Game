#pragma once
#include "piece.hpp"
#include "coord.hpp"
#include "move.hpp"
#include <array>
#include <vector>
#include <string>
#include <string_view>
#include <optional>
#include <cstdint>

class Board {
public:
// -CONSTANTS 
  static constexpr std::uint8_t kBoardSize = 8;
  static constexpr std::uint8_t kStartingRank_White = 0;
  static constexpr std::uint8_t kStartingRank_Black = 7;
  static constexpr std::uint8_t kPawnRank_White = 1;
  static constexpr std::uint8_t kPawnRank_Black = 6;

// CONSTRUCTORS 
  Board() noexcept;

// Rule of 5: Use defaults for modern C++
  Board(const Board&) = default;
  Board(Board&&) noexcept = default;
  Board& operator=(const Board&) = default;
  Board& operator=(Board&&) noexcept = default;
  ~Board() = default;

// BOARD INITIALIZATION 
  void setupStartingPosition() noexcept;
  void clear() noexcept;

// --- PIECE ACCESS ---
  [[nodiscard]] constexpr Piece getPiece(Coord pos) const noexcept {
    if (!pos.isValid()) return Piece{};
    return board_[pos.rank][pos.file];
  }

  constexpr void setPiece(Coord pos, Piece piece) noexcept {
    if (pos.isValid()) {
      board_[pos.rank][pos.file] = piece;
    }
  }

  [[nodiscard]] constexpr bool isEmpty(Coord pos) const noexcept {
    return getPiece(pos).isEmpty();
  }

// GAME STATE 
  [[nodiscard]] constexpr Color getCurrentTurn() const noexcept {
    return currentTurn_;
  }

  constexpr void switchTurn() noexcept {
    currentTurn_ = (currentTurn_ == Color::White) ? Color::Black : Color::White;
  }

  [[nodiscard]] constexpr std::uint16_t getFullmoveNumber() const noexcept {
    return fullmoveNumber_;
  }

  [[nodiscard]] constexpr std::uint8_t getHalfmoveClock() const noexcept {
    return halfmoveClock_;
  }

  [[nodiscard]] constexpr std::optional<Coord> getEnPassantTarget() const noexcept {
    return enPassantTarget_;
  }

// CASTLING RIGHTS 
  [[nodiscard]] constexpr bool canCastleKingside(Color color) const noexcept {
    std::uint8_t mask = (color == Color::White) ? kCastleWhiteKingside : kCastleBlackKingside;
  return (castlingRights_ & mask) != 0;
  }

  [[nodiscard]] constexpr bool canCastleQueenside(Color color) const noexcept {
    std::uint8_t mask = (color == Color::White) ? kCastleWhiteQueenside : kCastleBlackQueenside;
  return (castlingRights_ & mask) != 0;
  }

  constexpr void removeCastlingRights(Color color, bool kingside, bool queenside) noexcept {
    if (color == Color::White) {
      if (kingside) castlingRights_ &= ~kCastleWhiteKingside;
      if (queenside) castlingRights_ &= ~kCastleWhiteQueenside;
    } else {
      if (kingside) castlingRights_ &= ~kCastleBlackKingside;
      if (queenside) castlingRights_ &= ~kCastleBlackQueenside;
    }
  }

// MOVE EXECUTION
  bool makeMove(const Move& move) noexcept;

// MOVE VALIDATION
  [[nodiscard]] bool isValidMove(const Move& move) const noexcept;
  [[nodiscard]] std::vector<Move> getLegalMoves(Coord pos) const;
  [[nodiscard]] std::vector<Move> getAllLegalMoves(Color color) const;

// CHECKMATE DETECTION
  [[nodiscard]] bool isSquareAttacked(Coord pos, Color byColor) const noexcept;
  [[nodiscard]] bool isInCheck(Color color) const noexcept;
  [[nodiscard]] bool isCheckmate(Color color) const noexcept;
  [[nodiscard]] bool isStalemate(Color color) const noexcept;

// DISPLAY
  [[nodiscard]] std::string toASCII() const;
  [[nodiscard]] std::string toAccessibleString() const;
  [[nodiscard]] std::string toFEN() const;

// UTILITY
  [[nodiscard]] constexpr bool isWithinBounds(std::int8_t file, std::int8_t rank) const noexcept {
    return file >= 0 && file < kBoardSize && rank >= 0 && rank < kBoardSize;
  }

  [[nodiscard]] std::optional<Coord> findKing(Color color) const noexcept;

private:
// INTERNAL STATE
// 8x8 board (64 bytes total - each Piece is 1 byte)
  std::array<std::array<Piece, kBoardSize>, kBoardSize> board_{};

// Game state packed efficiently
  Color currentTurn_{ Color::White };
  std::uint8_t castlingRights_{ 0b0000'1111 }; // 4 bits: KQkq
  std::uint8_t halfmoveClock_{ 0 };
  std::uint16_t fullmoveNumber_{ 1 };
  std::optional<Coord> enPassantTarget_{ std::nullopt };

// Castling rights bitmasks
  static constexpr std::uint8_t kCastleWhiteKingside  = 0b0001;
  static constexpr std::uint8_t kCastleWhiteQueenside = 0b0010;
  static constexpr std::uint8_t kCastleBlackKingside  = 0b0100;
  static constexpr std::uint8_t kCastleBlackQueenside = 0b1000;

// MOVE GENERATION HELPERS
  void generatePawnMoves(Coord pos, std::vector<Move>& moves) const;
  void generateKnightMoves(Coord pos, std::vector<Move>& moves) const;
  void generateBishopMoves(Coord pos, std::vector<Move>& moves) const;
  void generateRookMoves(Coord pos, std::vector<Move>& moves) const;
  void generateQueenMoves(Coord pos, std::vector<Move>& moves) const;
  void generateKingMoves(Coord pos, std::vector<Move>& moves) const;

// Sliding piece helper
  void generateSlidingMoves(Coord pos, const std::array<std::pair<std::int8_t, std::int8_t>, 4>& directions,
                           std::vector<Move>& moves) const;

// MOVE VALIDATION HELPERS
  [[nodiscard]] bool wouldBeInCheck(const Move& move, Color color) const noexcept;
  [[nodiscard]] bool isPathClear(Coord from, Coord to) const noexcept;

// CASTLING HELPERS
  void handleCastlingRightsUpdate(const Move& move) noexcept;
  [[nodiscard]] bool isCastlingMove(const Move& move) const noexcept;
  void executeCastling(const Move& move) noexcept;
};
