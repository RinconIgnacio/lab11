# Lab 11 - Design Artifacts

## 1. Updated Class Diagram

```text
+-------------------------+
|          Card           |
+-------------------------+
| - m_rank: int           |
| - m_suit: Suit          |
+-------------------------+
| + rank(): int           |
| + to_string(): string   |
| + operator==()          |
| + operator<()           |
+-------------------------+
             ^
             | contains up to 11
             | (composition)
             |
+-------------------------+
|          Hand           |
+-------------------------+
| - m_cards: Card[11]     |
| - m_count: int          |
+-------------------------+
| + operator+=()          |
| + operator[]()          |
| + count(): int          |
| + value(): int          |
| + is_blackjack(): bool  |
| + is_bust(): bool       |
| + clear(): void         |
+-------------------------+

+-------------------------+
|          Deck           |
+-------------------------+
| Stores and deals Cards  |
+-------------------------+

Blackjack game
    |
    +-- Deck
    |
    +-- Hand (player)
    |
    +-- Hand (dealer)

The Hand owns its Cards because they are stored directly
inside its array. When the Hand is destroyed, its Cards
are destroyed too.
```

## 2. Flowchart - Hand::value()

```text
       [Start]
          |
          v
 [total = 0, aces = 0]
          |
          v
 [For each card in Hand]
          |
          v
    <Is it an Ace?>
       /       \
     Yes        No
      |          |
      v          v
 [Add 11]   <Rank >= 10?>
 [aces++]     /      \
            Yes       No
             |         |
             v         v
          [Add 10]  [Add rank]
             \        /
              \      /
               v    v
          [Next card]
               |
               v
    <More cards remaining?>
         /         \
       Yes          No
        |            |
        +-- Loop     v
             <total > 21 AND aces > 0?>
                  /        \
                Yes         No
                 |           |
                 v           v
           [total -= 10]  [Return total]
           [aces--]
                 |
                 +-- Repeat check
```

## 3. Flowchart - Dealer's Turn

```text
         [Start dealer turn]
                  |
                  v
        [Calculate hand value]
                  |
                  v
           <Value < 17?>
             /        \
           Yes         No
            |           |
            v           v
       [Deal card]    [Stand]
            |           |
            v           v
       [Add to Hand]   [End]
            |
            v
      [Calculate value]
            |
            +-- Repeat check
```

The dealer keeps drawing while the hand is below 17.
Once the hand reaches 17 or more, the dealer stands,
including on soft 17.
▒▒▄▀▀▀▀▀▄▒▒▒▒▒▄▄▄▄▄▒▒▒
▒▐░▄░░░▄░▌▒▒▄█▄█▄█▄█▄▒
▒▐░▀▀░▀▀░▌▒▒▒▒▒░░░▒▒▒▒
▒▒▀▄░═░▄▀▒▒▒▒▒▒░░░▒▒▒▒
▒▒▐░▀▄▀░▌▒▒▒▒▒▒░░░▒▒▒▒

