#pragma once
#include <cstdint>
#include <string>
#include <optional>  // For later use in Move

// Forward declaration for Move
enum class PieceType : std::uint8_t;

enum class Color : std::uint8_t {
	White,
	Black
};

enum class PieceType : std::uint8_t {
	Pawn,
	Rook,
	Bishop,
	Knight,
	Queen,
	King
};

struct Piece {}
// --- INTERNAL VALUES ---
// A single byte to hold all piece info using bitfields for memory efficiency
  std::uint8_t data;

// Bitmasks for piece type and color
  static constexpr std::uint8_t kTypeMask = 0b0111;  // Lower 3 bits for piece type
  static constexpr std::uint8_t kColorMask = 0b1000; // 1 bit for color

// --- CONSTRUCTORS ---
// Default constructor with 0 sentinel value indicating no piece
  constexpr Piece() noexcept : data{ 0 } {}
// Parameterized constructor
  constexpr Piece(PieceType type, Color color) noexcept
    : data(static_cast<std::uint8_t>(type) | (static_cast<std::uint8_t>(color) << 3)) {}

// --- MEMBER FUNCTIONS ---
// Getter: Piece type
  [[nodiscard]] constexpr PieceType getType() const noexcept {
    return static_cast<PieceType>(data & kTypeMask);
  }

// // Getter: Piece color
  [[nodiscard]] constexpr Color getColor() const noexcept {
	return static_cast<Color>(data & kColorMask);
  }

// Helper: Display piece as single char for debugging and board rendering
  [[nodiscard]] constexpr char toChar() const noexcept {
	  char c = ' ';
	  switch (getType()) {
	  case PieceType::Pawn: c = 'P';
	  case PieceType::Rook:  c = 'R';
	  case PieceType::Bishop:  c = 'B';
	  case PieceType::Knight:  c = 'N';
	  case PieceType::Queen:  c = 'Q';
	  case PieceType::King:  c = 'K';
	  }
	  return (getColor() == Color::White) ? c : static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
  }

// Helper: Converts piece type and color to string for screenreader consumption
  [[nodiscard]] std::string toString() const {
	  std::string colorStr = (getColor() == Color::White) ? "White" : "Black";
	std::string typeStr;
	switch (getType()) {
	case PieceType::Pawn:   typeStr = "Pawn"; break;
	case PieceType::Rook:   typeStr = "Rook"; break;
	case PieceType::Bishop: typeStr = "Bishop"; break;
	case PieceType::Knight: typeStr = "Knight"; break;
	case PieceType::Queen:  typeStr = "Queen"; break;
	case PieceType::King:   typeStr = "King"; break;
	default:                typeStr = "Unknown"; break;
	}
	return colorStr + " " + typeStr;
  }

// Comparison operator to check equality between two Piece objects
  [[nodiscard]] constexpr bool operator==(const Piece& other)  const noexcept {
    return data == other.data;
  }
; };