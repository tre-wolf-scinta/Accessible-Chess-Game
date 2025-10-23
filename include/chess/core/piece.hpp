#pragma once
#include <cstdint>
#include <string>

enum class Color : std::uint8_t {
    White = 0,
    Black = 1
};

enum class PieceType : std::uint8_t {
    None = 0,
    Pawn = 1,
    Knight = 2,
    Bishop = 3,
    Rook = 4,
    Queen = 5,
    King = 6
};

struct Piece {
    // --- INTERNAL VALUES ---
    // A single byte to hold all piece info using bitfields for memory efficiency
    std::uint8_t data{ 0 };

    // Bitmasks for piece type and color
    static constexpr std::uint8_t kTypeMask = 0b0000'0111; // lower 3 bits for piece type
    static constexpr std::uint8_t kColorMask = 0b0000'1000; // 1 bit for color
    static constexpr std::uint8_t kColorShift = 3;

    // --- CONSTRUCTORS ---
    constexpr Piece() noexcept = default; // Empty by default, data == 0

    // Parameterized constructor
    constexpr Piece(PieceType type, Color color) noexcept
        : data{ static_cast<std::uint8_t>(static_cast<std::uint8_t>(type) & kTypeMask)
              | static_cast<std::uint8_t>(static_cast<std::uint8_t>(color) << kColorShift) } {
    }

    // --- MEMBER FUNCTIONS ---
    [[nodiscard]] constexpr bool isEmpty() const noexcept {
        return (data & kTypeMask) == 0;
    }

    // Getter: Piece type
    [[nodiscard]] constexpr PieceType getType() const noexcept {
        return static_cast<PieceType>(data & kTypeMask);
    }

    // Getter: Piece color
    [[nodiscard]] constexpr Color getColor() const noexcept {
        // extract bit 3 and shift it down to bit 0 -> 0 or 1
        return static_cast<Color>((data & kColorMask) >> kColorShift);
    }

    // Helper: ASCII-only lowercasing allows calling toChar without locale dependencies
    static constexpr char ascii_tolower(char c) noexcept {
        return (c >= 'A' && c <= 'Z') ? static_cast<char>(c + ('a' - 'A')) : c;
    }

    // Helper: Display piece as single char for debugging and board rendering
    [[nodiscard]] constexpr char toChar() const noexcept {
        if (isEmpty()) return '.';
        char c = '?';
        switch (getType()) {
        case PieceType::Pawn:   c = 'P'; break;
        case PieceType::Rook:   c = 'R'; break;
        case PieceType::Bishop: c = 'B'; break;
        case PieceType::Knight: c = 'N'; break;
        case PieceType::Queen:  c = 'Q'; break;
        case PieceType::King:   c = 'K'; break;
        case PieceType::None:   c = '.'; break;
        }
        if (getColor() == Color::Black) {
            c = ascii_tolower(c);
        }
        return c;
    }

    // Helper: Converts piece type and color to string for screen reader consumption
    [[nodiscard]] std::string toString() const {
        if (isEmpty()) return "Empty";
        const char* typeStr = "Unknown";
        switch (getType()) {
        case PieceType::Pawn:   typeStr = "Pawn";  break;
        case PieceType::Knight: typeStr = "Knight"; break;
        case PieceType::Bishop: typeStr = "Bishop"; break;
        case PieceType::Rook:   typeStr = "Rook";   break;
        case PieceType::Queen:  typeStr = "Queen";  break;
        case PieceType::King:   typeStr = "King";   break;
        case PieceType::None:   typeStr = "None";   break;
        }
        const char* colorStr = (getColor() == Color::White) ? "White" : "Black";
        return std::string(colorStr) + " " + typeStr;
    }

    // Comparison operator to check equality between two Piece objects
    [[nodiscard]] constexpr bool operator==(const Piece& other) const noexcept {
        return data == other.data;
    }
};
