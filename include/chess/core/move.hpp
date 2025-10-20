#pragma once
#include "piece.h"
#include "coord.h"

struct Move {
    Coord from{};
    Coord to{};
    PieceType promotion{ PieceType::None };

    // Constructors
    constexpr Move() noexcept = default;
    constexpr Move(Coord f, Coord t, PieceType promo = PieceType::None) noexcept
        : from(f), to(t), promotion(promo) {
    }

    // Equality 
    [[nodiscard]] constexpr bool operator==(const Move& other) const noexcept = default;

    // Query helpers
    [[nodiscard]] constexpr bool isPromotion() const noexcept {
        return promotion != PieceType::None;
    }
};
