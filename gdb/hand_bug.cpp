// hand_bug.cpp - a Hand::value that gives the wrong total for some hands.
//
// This file does not use your Hand. It has its own Hand so the bug is the same
// for everyone. The program prints the total it computes for ten hands. It does
// not say which are right: work out the correct totals from the rules first
// (your Aces Table), then compare.
//
// Build (Debug, includes -g):
//   cmake -S . -B build
//   cmake --build build --target hand_bug
// Run:
//   ./build/hand_bug        all ten hands
//   ./build/hand_bug 4      only hand number 4

#include <iostream>
#include <string>

#include "card.h"

inline constexpr int max_hand = 11;

class Hand {
public:
  Hand() : m_cards{}, m_count{0} {}

  Hand &operator+=(const Card &card) {
    m_cards[m_count] = card;
    ++m_count;
    return *this;
  }

  int value() const {
    int total = 0;
    int aces_as_eleven = 0;
    for (int i = 0; i < m_count; ++i) {
      if (total > 21 && aces_as_eleven > 0) {
        total -= 10;
        --aces_as_eleven;
      }
      const int rank = m_cards[i].rank();
      if (rank == 1) {
        total += 11;
        ++aces_as_eleven;
      } else if (rank >= 10) {
        total += 10;
      } else {
        total += rank;
      }
    }
    return total;
  }

private:
  Card m_cards[max_hand];
  int m_count;
};

namespace {

// A hand written as ranks: 1 = ace, 11 = jack, 12 = queen, 13 = king. A rank of
// 0 ends the list.
struct Row {
  int ranks[5];
};

const Row rows[] = {
    {{1, 13, 0}},      // 1
    {{1, 1, 0}},       // 2
    {{1, 1, 9, 0}},    // 3
    {{1, 6, 5, 0}},    // 4
    {{1, 1, 1, 0}},    // 5
    {{1, 1, 1, 8, 0}}, // 6
    {{1, 5, 13, 0}},   // 7
    {{1, 13, 12, 0}},  // 8
    {{10, 10, 5, 0}},  // 9
    {{9, 7, 5, 0}},    // 10
};
const int row_count = 10;

void show(int number) {
  Hand hand;
  std::string text;
  for (int i = 0; rows[number - 1].ranks[i] != 0; ++i) {
    const Card card{rows[number - 1].ranks[i], static_cast<Suit>(i % 4)};
    hand += card;
    if (i > 0) {
      text += ", ";
    }
    text += card.to_string();
  }
  std::cout << "Hand " << number << ": " << text << "  ->  value "
            << hand.value() << "\n";
}

} // namespace

int main(int argc, char *argv[]) {
  if (argc > 1) {
    const int number = std::stoi(argv[1]);
    if (number < 1 || number > row_count) {
      std::cout << "Usage: ./hand_bug [1-" << row_count << "]\n";
      return 1;
    }
    show(number);
    return 0;
  }
  for (int number = 1; number <= row_count; ++number) {
    show(number);
  }
  return 0;
}
