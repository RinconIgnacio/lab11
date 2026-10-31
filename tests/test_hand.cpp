// Lab 11 checks for the Card operators and Hand. They fail until you write the
// code.

#include <gtest/gtest.h>

#include <sstream>
#include <string>

#include "card.h"
#include "hand.h"

namespace {

// Build a hand from text: ranks separated by spaces, using A 2 3 4 5 6 7 8 9 T
// J Q K. Suits rotate so that no hand holds two identical cards.
Hand hand_from(const std::string &text) {
  Hand hand;
  int suit = 0;
  for (char c : text) {
    int rank = 0;
    if (c == 'A') {
      rank = 1;
    } else if (c >= '2' && c <= '9') {
      rank = c - '0';
    } else if (c == 'T') {
      rank = 10;
    } else if (c == 'J') {
      rank = 11;
    } else if (c == 'Q') {
      rank = 12;
    } else if (c == 'K') {
      rank = 13;
    }
    if (rank != 0) {
      hand += Card{rank, static_cast<Suit>(suit % 4)};
      ++suit;
    }
  }
  return hand;
}

} // namespace

// ---- Card operators
// ------------------------------------------------------------------------

TEST(CardOperatorTest, EqualityComparesRankAndSuit) {
  EXPECT_TRUE((Card{9, Suit::hearts}) == (Card{9, Suit::hearts}));
  EXPECT_FALSE((Card{9, Suit::hearts}) == (Card{9, Suit::spades}));
  EXPECT_FALSE((Card{9, Suit::hearts}) == (Card{8, Suit::hearts}));
}

TEST(CardOperatorTest, NotEqualComesFromEquality) {
  // C++20 rewrites != using ==. This fails to compile or fails the check if ==
  // is wrong.
  EXPECT_TRUE((Card{9, Suit::hearts}) != (Card{9, Suit::spades}));
  EXPECT_FALSE((Card{9, Suit::hearts}) != (Card{9, Suit::hearts}));
}

TEST(CardOperatorTest, OrderIsRankThenSuit) {
  EXPECT_TRUE((Card{3, Suit::spades}) < (Card{4, Suit::clubs}));
  EXPECT_FALSE((Card{4, Suit::clubs}) < (Card{3, Suit::spades}));
  EXPECT_TRUE((Card{7, Suit::clubs}) < (Card{7, Suit::hearts}));
  EXPECT_FALSE((Card{7, Suit::hearts}) < (Card{7, Suit::clubs}));
  EXPECT_FALSE((Card{7, Suit::hearts}) < (Card{7, Suit::hearts}));
}

TEST(CardOperatorTest, StreamWritesShortText) {
  std::ostringstream out;
  out << Card{1, Suit::spades} << '|' << Card{10, Suit::hearts};
  EXPECT_EQ(out.str(), "AS|10H");
}

// ---- Hand: adding, reading, clearing
// --------------------------------------------------------

TEST(HandTest, StartsEmpty) {
  Hand hand;
  EXPECT_EQ(hand.count(), 0);
  EXPECT_EQ(hand.value(), 0);
}

TEST(HandTest, PlusEqualsAppendsInOrder) {
  Hand hand;
  hand += Card{1, Suit::spades};
  hand += Card{9, Suit::hearts};
  ASSERT_EQ(hand.count(), 2);
  EXPECT_EQ(hand[0], (Card{1, Suit::spades}));
  EXPECT_EQ(hand[1], (Card{9, Suit::hearts}));
}

TEST(HandTest, PlusEqualsReturnsTheSameHand) {
  Hand hand;
  Hand &result = (hand += Card{5, Suit::clubs});
  EXPECT_EQ(&result, &hand);
}

TEST(HandTest, ClearEmptiesTheHand) {
  Hand hand = hand_from("K Q");
  ASSERT_EQ(hand.count(), 2);
  hand.clear();
  EXPECT_EQ(hand.count(), 0);
  EXPECT_EQ(hand.value(), 0);
}

TEST(HandTest, CopyIsIndependent) {
  Hand original = hand_from("5 6");
  Hand copy = original;
  copy += Card{2, Suit::clubs};
  EXPECT_EQ(original.count(), 2);
  EXPECT_EQ(copy.count(), 3);
}

TEST(HandTest, StreamWritesCardsSeparatedBySpaces) {
  std::ostringstream out;
  Hand hand;
  hand += Card{1, Suit::spades};
  hand += Card{9, Suit::hearts};
  out << hand;
  EXPECT_EQ(out.str(), "AS 9H");
}

TEST(HandTest, StreamWritesNothingForAnEmptyHand) {
  std::ostringstream out;
  out << Hand{};
  EXPECT_EQ(out.str(), "");
}

// ---- Hand: value, blackjack, bust
// ---------------------------------------------------------- Provided cases.
// Your OPERATORS_NOTES.md test table needs at least six hands; add yours below.

TEST(HandValueTest, AceAndKingIsTwentyOne) {
  EXPECT_EQ(hand_from("A K").value(), 21);
}

TEST(HandValueTest, FaceCardsCountTen) {
  EXPECT_EQ(hand_from("J Q").value(), 20);
}

TEST(HandValueTest, TwoAcesAreTwelve) {
  EXPECT_EQ(hand_from("A A").value(), 12);
}

TEST(HandValueTest, BustIsTheRealTotal) {
  EXPECT_EQ(hand_from("T T 5").value(), 25);
}

TEST(HandBlackjackTest, TwoCardTwentyOneIsBlackjack) {
  EXPECT_TRUE(hand_from("A K").is_blackjack());
  EXPECT_TRUE(hand_from("Q A").is_blackjack());
}

TEST(HandBlackjackTest, ThreeCardTwentyOneIsNotBlackjack) {
  EXPECT_FALSE(hand_from("7 7 7").is_blackjack());
}

TEST(HandBustTest, OverTwentyOneIsBust) {
  EXPECT_TRUE(hand_from("T T 5").is_bust());
  EXPECT_FALSE(hand_from("T T").is_bust());
  EXPECT_FALSE(hand_from("7 7 7").is_bust());
}

// TODO(student): add one TEST for each remaining row of your test table in
// OPERATORS_NOTES.md. Work out the expected value from the rules, not from what
// your code prints. The soft hands are the ones that catch mistakes: an ace
// that counts 11 and later has to count 1, and hands with more than one ace.
