#include "blackjack.h"
#include <iostream>
#include <random>
#include <string>

#include "deck.h"
#include "hand.h"
#include "input.h"

namespace {

constexpr int starting_bankroll = 100;
constexpr int fixed_bet = 10;
constexpr int reshuffle_limit = 15;

/// Play the dealer's turn, standing on every 17, including soft 17.
void dealer_turn(Deck &deck, Hand &dealer) {
  while (dealer.value() < 17) {
    dealer += deck.deal();
    std::cout << "Dealer hits: " << dealer
              << " (" << dealer.value() << ")\n";
  }

  std::cout << "Dealer stands: " << dealer
            << " (" << dealer.value() << ")\n";
}

/// Ask the player whether to hit or stand.
/// @return true to hit, false to stand or end input.
bool wants_hit() {
  std::string choice;

  while (true) {
    if (!prompt_line("Hit or stand? (h/s): ", choice)) {
      return false;
    }

    if (choice == "h" || choice == "H") {
      return true;
    }

    if (choice == "s" || choice == "S") {
      return false;
    }

    std::cout << "Please enter h or s.\n";
  }
}

/// Ask whether to play another round.
/// @return true to play, false to quit or end input.
bool wants_round() {
  std::string choice;

  while (true) {
    if (!prompt_line("Play a round? (y/n): ", choice)) {
      return false;
    }

    if (choice == "y" || choice == "Y") {
      return true;
    }

    if (choice == "n" || choice == "N") {
      return false;
    }

    std::cout << "Please enter y or n.\n";
  }
}

} // namespace

void play_blackjack() {
  std::random_device device{};
  std::mt19937 gen{device()};

  Deck deck;
  deck.shuffle(gen);

  int bankroll = starting_bankroll;

  std::cout << "\n--- Blackjack ---\n"
            << "Starting bankroll: $" << bankroll << "\n"
            << "Fixed bet: $" << fixed_bet << "\n";

  while (bankroll >= fixed_bet) {
    std::cout << "\nBankroll: $" << bankroll << "\n";

    if (!wants_round()) {
      break;
    }

    if (deck.remaining() < reshuffle_limit) {
      deck = Deck{};
      deck.shuffle(gen);
      std::cout << "Deck reshuffled.\n";
    }

    Hand player;
    Hand dealer;

    player += deck.deal();
    dealer += deck.deal();
    player += deck.deal();
    dealer += deck.deal();

    bankroll -= fixed_bet;

    std::cout << "\nYour hand: " << player
              << " (" << player.value() << ")\n"
              << "Dealer shows: " << dealer[0] << "\n";

    const bool player_blackjack = player.is_blackjack();
    const bool dealer_blackjack = dealer.is_blackjack();

    if (player_blackjack || dealer_blackjack) {
      std::cout << "Dealer hand: " << dealer
                << " (" << dealer.value() << ")\n";

      if (player_blackjack && dealer_blackjack) {
        std::cout << "Both have blackjack. Push!\n";
        bankroll += fixed_bet;
      } else if (player_blackjack) {
        std::cout << "Natural blackjack! Pays 3:2.\n";
        bankroll += fixed_bet * 5 / 2;
      } else {
        std::cout << "Dealer has blackjack. You lose.\n";
      }

      continue;
    }

    while (!player.is_bust() && wants_hit()) {
      player += deck.deal();

      std::cout << "Your hand: " << player
                << " (" << player.value() << ")\n";
    }

    if (player.is_bust()) {
      std::cout << "Bust! You lose $" << fixed_bet << ".\n";
      continue;
    }

    std::cout << "\nDealer reveals: " << dealer
              << " (" << dealer.value() << ")\n";

    dealer_turn(deck, dealer);

    if (dealer.is_bust()) {
      std::cout << "Dealer busts! You win.\n";
      bankroll += fixed_bet * 2;
    } else if (player.value() > dealer.value()) {
      std::cout << "You win!\n";
      bankroll += fixed_bet * 2;
    } else if (player.value() < dealer.value()) {
      std::cout << "Dealer wins.\n";
    } else {
      std::cout << "Push! Your bet is returned.\n";
      bankroll += fixed_bet;
    }
  }

  if (bankroll < fixed_bet) {
    std::cout << "\nYou are out of money!\n";
  }

  std::cout << "Final bankroll: $" << bankroll << "\n";
}
