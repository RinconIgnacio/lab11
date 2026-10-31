#ifndef ARCADE_CARD_H
#define ARCADE_CARD_H

#include <ostream>
#include <string>

/// @file card.h
/// @brief A playing card.

/// The four suits.
enum class Suit {
  clubs,    ///< clubs
  diamonds, ///< diamonds
  hearts,   ///< hearts
  spades,   ///< spades
};

/// One playing card: a rank from 1 (ace) to 13 (king) and a suit.
class Card {
public:
  /// Make the ace of spades.
  Card();

  /// Make a card
  /// @param rank 1 = ace, 2 to 10, 11 = jack, 12 = queen, 13 = king
  /// @param suit the suit
  Card(int rank, Suit suit);

  /// @return the rank, 1 to 13
  int rank() const;

  /// @return the suit
  Suit suit() const;

  /// @return short text such as "AS", "10H", or "KD"
  std::string to_string() const;

  // TODO(student): Lab 11. The signatures are given; read each one before you
  // write the body. Think about which parts are `const` and why.

  /// Two cards are equal when both rank and suit match.
  bool operator==(const Card &other) const;

  /// Order by rank first, then by suit (clubs < diamonds < hearts < spades).
  bool operator<(const Card &other) const;

private:
  int m_rank;
  Suit m_suit;
};

/// Write a card as its short text, for example "AS" or "10H". No spaces, no
/// newline. A non-member function: the stream is the left operand, so it cannot
/// be a member of Card.
/// @return @p out, so that calls can be chained
std::ostream &operator<<(std::ostream &out, const Card &card);

#endif // ARCADE_CARD_H
