#pragma once
#include <expected>
#include <string>
#include <cctype>
#include <cstdint>

struct Coord {
	// Using uint8_t to save memory 
	std::uint8_t file;	// Internal values 0 - 7 representing vertical columns on board
	std::uint8_t rank;	// Internal values 0 - 7 representing horizontal rows on board
	static constexpr uint8_t kInvalid = 255;  // Sentinel value for default constructor

// default constructor with sentinel values
	constexpr Coord() noexcept : file{kInvalid}, rank{kInvalid} {}
// parameterized constructor used by game logic to  create Coord when passed numeric values
	constexpr Coord(std::uint8_t f, std::uint8_t r) noexcept : file(f), rank(r) {}

// Helper method checks if Coord is within valid chessboard range
	[[nodiscard]] constexpr bool isValid() const noexcept {
		return file < 8 && rank < 8;
	}
// Factory constructor builds Coord from algebraic notation (e.g., "E4" = Coord{4, 3})
	[[nodiscard]] static std::expected<Coord, std::string> fromString(const std::string& notation) noexcept {
		if (notation.size() != 2) {
			return std::unexpected("Invalid format. Coordinate must be 2 characters like A2 or E4");
		}

		// Normalize file and rank args
		char fc = static_cast<char>(std::tolower(static_cast<unsigned char>(notation[0])));
		char rc = notation[1];
		// Check if file and rank are within valid ranges - if not throw exception
		if (fc < 'a' || fc > 'h' || rc < '1' || rc > '8') {
			return std::unexpected("Coordinate is off the board. Valid files are A-H and valid ranks are 1-8.");
		}
		std::uint8_t f = static_cast<std::uint8_t>(fc - 'a');  // Convert 'a' -> 0, 'b' -> 1...
		std::uint8_t r = static_cast<std::uint8_t>(rc - '1');  // Convert 'char to 0-7 range'1' -> 0, '2' -> 1...
	return Coord(f, r);
	}

// Helper function converts Coord back to string for display purposes
	std::string toString() const {
		if (!isValid())  {
			return "Invalid coordinates";
		}

		char fc = static_cast<char>('a' + file);
		char rc = static_cast<char>('1' + rank);
	return std::string{ fc, rc };
	}

// Comparison operator allows easy equality checks between two Coord objects
	[[nodiscard]] constexpr bool operator==(const Coord& other) const noexcept {
		return file == other.file && rank == other.rank;
	}
};