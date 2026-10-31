# Arcade: Week 11 starter (S11)

A text-game arcade in C++20. This is the starting point for **Lab 11: Operator Overloading (Blackjack II)**. It contains the finished Lab 10 work (`Deck` with the rule of three) and the files you need for Lab 11.

## What is already here

| Part | Files | Notes |
| --- | --- | --- |
| Menu | `app/main.cpp`, `src/input.cpp`, `include/input.h` | Already finished |
| Card and Deck | `include/card.h`, `src/card.cpp`, `include/deck.h`, `src/deck.cpp` | `Deck` is finished (Lab 10 solution). `Card` needs three operators. |
| Hand | `include/hand.h`, `src/hand.cpp` | Signatures and documentation are given. The bodies are stubs that return wrong answers. |
| Blackjack | `include/blackjack.h`, `src/blackjack.cpp` | Still the Lab 10 demonstration. You write the game. |
| Tests | `tests/test_deck.cpp`, `tests/test_hand.cpp` | `test_hand.cpp` fails until your code is right |
| Debugging practice | `gdb/hand_bug.cpp` | Not built by default |
| Notes to fill in | `OPERATORS_NOTES.md`, `GDB_LOG.md` | See below |

## Build and run

```
cmake -S . -B build                  # Debug build, -g included
cmake --build build
./build/arcade
```

With AddressSanitizer (use a separate folder):

```
cmake -S . -B build-asan -DENABLE_ASAN=ON
cmake --build build-asan
./build-asan/arcade
```

Tests:

```
cd build && ctest --output-on-failure
```

The first run downloads GoogleTest with git unless `libgtest-dev` is installed. The `Card` operator tests and the `Hand` tests fail until you write the code. The `Deck` tests pass. A new `.cpp` file in `src/` must also be added to the `arcade_lib` list in `CMakeLists.txt`.

Documentation (needs `doxygen`): `cmake --build build --target docs`, then open `docs/html/index.html`.

The GDB practice program for this lab:

```
cmake --build build --target hand_bug
gdb ./build/hand_bug
```

## Your Lab 11 tasks

1. `src/card.cpp`: write `operator==`, `operator<`, and the non-member `operator<<` for `Card`. The declarations are in `include/card.h`.
2. `src/hand.cpp`: write every function of `Hand`. Read the comments in `include/hand.h` first; they are the specification. Do not write a destructor, copy constructor, or assignment operator for `Hand`.
3. `src/blackjack.cpp`: replace the demonstration with the game, using `hand += deck.deal();` and `std::cout << hand;`.
4. `tests/test_hand.cpp`: add a test for each row of your test table.
5. `OPERATORS_NOTES.md`: test table, design artifact locations, ownership table.
6. `GDB_LOG.md`: the session on `hand_bug`. 
7. Commit with Conventional Commit messages, composed in the editor. 

## Rules for this project

- Build with no warnings under `-Wall -Wextra`.
- Allowed headers: `<iostream>`, `<iomanip>`, `<string>`, `<fstream>`, `<stdexcept>`, `<random>`. No standard containers or `<algorithm>`. No `using namespace std;`.
- Names: `underscore_separated` functions and variables, `Capitalized` types, private data members start with `m_`, enumerators are lowercase, no ALL_CAPS constants.
