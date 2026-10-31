#include "hand.h"

// TODO(student): Lab 11. Every function below compiles but returns a wrong
// answer on purpose, so the tests in tests/test_hand.cpp fail until you write
// it. Name the parameters when you replace the bodies. Keep `const` wherever
// the declaration in hand.h has it.

Hand::Hand() : m_cards{}, m_count{0} {}

Hand &Hand::operator+=(const Card &) { return *this; }

const Card &Hand::operator[](int) const { return m_cards[0]; }

int Hand::count() const { return 0; }

int Hand::value() const { return 0; }

bool Hand::is_blackjack() const { return false; }

bool Hand::is_bust() const { return false; }

void Hand::clear() {}

std::ostream &operator<<(std::ostream &out, const Hand &) { return out; }
