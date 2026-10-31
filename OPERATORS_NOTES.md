# Operators notes (Lab 11)

Fill this in as you work. Commit it with the code.

## 1. Test table for `Hand`

At least six hands. Work out each expected value from the rules **before** you run any code. At least one soft hand, one bust, and one blackjack must be in the table. Every row must also appear as a test in `tests/test_hand.cpp`.

| Hand | Expected `value()` | `is_bust()` | `is_blackjack()` |
| --- | --- | --- | --- |
| | | | |
| | | | |
| | | | |
| | | | |
| | | | |
| | | | |

## 2. Design artifacts

List the files you added and where they are in the repository.

- Updated class diagram (with `Hand` and its relationship to `Card`):
- Flowchart for `Hand::value`:
- Flowchart for the dealer's turn:

## 3. Ownership classification

For each relationship, write **composition**, **aggregation**, or **association**, then one sentence that says why. Use the test questions from class: if the whole is destroyed, does the part go too? Could the same part belong to two wholes? Does the class only store a reference to something it does not own? A complete answer states what happens to the part when the whole is destroyed, and whether anything else can still hold the part.

| Relationship | Composition, aggregation, or association | One-sentence justification |
| --- | --- | --- |
| `Hand` and its `Card`s | | |
| The Blackjack game and its `Deck` and `Hand`s | | |
| `Player` and the current `Room*` in the Dungeon | | |

## 4. Checklist before you push

- [ ] `cmake --build build` has no warnings
- [ ] `ctest` passes, including your own `Hand` tests
- [ ] A run under AddressSanitizer is clean (`-DENABLE_ASAN=ON`, separate build folder)
- [ ] `GDB_LOG.md`: each partner has written their own Week 11 section
- [ ] Commits use Conventional Commit messages, and both partners have commits
