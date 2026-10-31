# GDB log

One dated section per week. Paste the commands you used and the output you saw, then explain what it means in your own words. Pasted output with no explanation earns partial credit at most. Each partner writes their own section.

## Week 11 (Lab 11)

Partner name: Ignacio Rincon :0 

### Predict before you run

Before running `hand_bug`, which hands from the Aces Table do you expect it to get wrong, and why?

I expected some of the hands with aces to give incorrect values. The code was checking the total before adding the next card, so I thought it might fail when the last card made the total go over 21.

### Build and run

```
cmake -S . -B build
cmake --build build --target hand_bug
./build/hand_bug
```

Hands whose total differs from your Aces Table (hand number, printed total, correct total):

- Hand 2: 22, correct value 12
- Hand 4: 22, correct value 12
- Hand 5: 23, correct value 13
- Hand 7: 26, correct value 16
- Hand 8: 31, correct value 21

### The GDB session on `Hand::value`

Record the commands in the order you typed them. For each, one line on what it did.

- Conditional breakpoint command (stop only when the hand has three cards):

  `break Hand::value if m_count == 3`

  I used `run 4` after setting the breakpoint. It stopped at line 33 because hand 4 had three cards.

- `display` commands you set:

  `display total`

  `display aces_as_eleven`

  These commands helped me see the values of both variables while going through the function.

- Values shown at the failing step (the running total and the number of aces counted as 11 after each `next`):

  At first, `total = 0` and `aces_as_eleven = 0`. After the first ace was added, `total = 11` and `aces_as_eleven = 1`.

  I used `next` to follow the execution, and then `finish` to check the returned value.

- What `print *this` showed:

  It showed `m_count = 3`, with the first three cards having ranks 1, 6, and 5. This confirmed I was looking at the correct hand.

- What `finish` returned for the failing hand, and the correct value:

  `Value returned is $2 = 22`

  The correct value was 12 because the ace should count as 1 instead of 11.

### Cause and fix

- The line that is wrong, and what it does instead of what it should:

  The problem was around lines 36–39. The code adjusted the aces before adding the next card. If the last card made the total go over 21, the program wouldn't check again.

- The change you made:

  I moved the ace adjustment outside the `for` loop so the program could check the total after adding every card.

  ```cpp
  while (total > 21 && aces_as_eleven > 0) {
    total -= 10;
    --aces_as_eleven;
  }
  ```

- How you checked it (which hands, which result):

  I rebuilt the program and ran all ten hands again. All of them returned the correct values. Hand 4 returned 12 instead of 22, and hands 2, 5, 7, and 8 were also fixed.
  ( ͡❛ ͜ʖ ͡❛)
