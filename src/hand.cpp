#include "hand.h"

// TODO(student): Lab 11. Every function below compiles but returns a wrong
// answer on purpose, so the tests in tests/test_hand.cpp fail until you write
// it. Name the parameters when you replace the bodies. Keep `const` wherever
// the declaration in hand.h has it.

    Hand::Hand() : m_cards{}, m_count{0} {}

    Hand &Hand::operator+=(const Card &card) {
     m_cards[m_count] = card;
     ++m_count;
     return *this;
}

    const Card &Hand::operator[](int index) const {
      return m_cards[index];
    }

    int Hand::count() const {
     return m_count;
}

    int Hand::value() const {
     int total = 0;
     int aces = 0;

    for (int i = 0; i < m_count; ++i) {
     int rank = m_cards[i].rank();

    if (rank == 1) {
      total += 11;
      ++aces;
    }

   else if (rank >= 10) {
      total += 10;
    }

    else {
      total += rank;
    }
  }

    while (total > 21 && aces > 0) {
    total -= 10;
    --aces;
  }

    return total;
}

    bool Hand::is_blackjack() const {
    return m_count == 2 && value() == 21;
}

    bool Hand::is_bust() const {
    return value() > 21;
}

    void Hand::clear() {
    m_count = 0;
}

    std::ostream &operator<<(std::ostream &out, const Hand &hand) {
        for (int i = 0; i < hand.count(); ++i) {
        if (i > 0) {
        out << ' ';
    }
        out << hand[i];
  }

      return out;
}
