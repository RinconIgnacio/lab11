#ifndef ARCADE_DECK_H
#define ARCADE_DECK_H

#include <random>

#include "card.h"

/// @file deck.h
/// @brief A deck of 52 cards that owns its memory.

/// The number of cards in a full deck.
inline constexpr int deck_size = 52;

// Class invariant (true before and after every public function):
//   m_cards points to a valid array of m_size Card objects allocated with
//   new[] (or is nullptr when m_size is 0), and 0 <= m_next <= m_size.
//   Every object owns its own array; no two Decks share one.
//
// Self-assignment: if operator= freed m_cards before copying and the argument
// is the same object, it would read from memory it had just released (a use
// after free), and the deck would end up holding garbage.

/// A deck of playing cards stored in a heap array.
class Deck {
public:
  /// Make a full, ordered deck: one of each rank in each suit.
  Deck();

  /// Free the cards.
  ~Deck();

  /// Make an independent copy of another deck.
  Deck(const Deck &other);

  /// Replace this deck's contents with a copy of another deck.
  Deck &operator=(const Deck &other);

  /// Put all the cards in random order and start dealing from the top again.
  /// @param gen the random number generator to draw from
  void shuffle(std::mt19937 &gen);

  /// Take the top card.
  /// @pre the deck is not empty
  /// @return the card that was on top
  Card deal();

  /// @return true if every card has been dealt
  bool empty() const;

  /// @return how many cards are left to deal
  int remaining() const;

private:
  Card *m_cards;
  int m_size;
  int m_next;
};

#endif // ARCADE_DECK_H
