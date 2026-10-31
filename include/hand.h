#ifndef ARCADE_HAND_H
#define ARCADE_HAND_H

#include <ostream>

#include "card.h"

/// @file hand.h
/// @brief The cards one player or the dealer is holding.

/// The most cards a hand can hold. Twenty-one cannot be passed with more than
/// eleven cards.
inline constexpr int max_hand = 11;

/// A blackjack hand. The cards are stored inside the object, in the order they
/// were added.
///
/// A Hand has no pointers, so the compiler-generated copy constructor,
/// assignment, and destructor are correct. Do not write them.
class Hand {
public:
  /// Make an empty hand.
  Hand();

  /// Add a card to the end of the hand.
  /// @pre count() < max_hand
  /// @return this hand, so that chained calls work
  Hand &operator+=(const Card &card);

  /// Read the card at a position (0 is the first card added).
  /// @pre 0 <= index < count(). This is a precondition, not a checked error; a
  ///      later week replaces it with an exception.
  /// @return a read-only reference to the card
  const Card &operator[](int index) const;

  /// @return how many cards are in the hand
  int count() const;

  /// The blackjack total. Number cards count their rank; jack, queen, and king
  /// count 10. An ace counts 11 unless that would make the total go over 21, in
  /// which case it counts 1. Every ace is decided separately, so A, A, 9 is 21.
  /// @return the best total, or 0 for an empty hand
  int value() const;

  /// @return true if the hand is exactly two cards that total 21
  bool is_blackjack() const;

  /// @return true if value() is over 21
  bool is_bust() const;

  /// Remove every card.
  void clear();

private:
  Card m_cards[max_hand];
  int m_count;
};

/// Write the cards in order, separated by single spaces, with no trailing space
/// or newline. For example "AS 9H". An empty hand writes nothing.
/// @return @p out, so that calls can be chained
std::ostream &operator<<(std::ostream &out, const Hand &hand);

#endif // ARCADE_HAND_H
