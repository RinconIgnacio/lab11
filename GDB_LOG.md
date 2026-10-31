# GDB log

One dated section per week. Paste the commands you used and the output you saw, then explain what it means in your own words. Pasted output with no explanation earns partial credit at most. Each partner writes their own section.

## Week 11 (Lab 11)

Partner name:

### Predict before you run

Before running `hand_bug`, which hands from the Aces Table do you expect it to get wrong, and why?

### Build and run

```
cmake -S . -B build
cmake --build build --target hand_bug
./build/hand_bug
```

Hands whose total differs from your Aces Table (hand number, printed total, correct total):

### The GDB session on `Hand::value`

Record the commands in the order you typed them. For each, one line on what it did.

- Conditional breakpoint command (stop only when the hand has three cards):
- `display` commands you set:
- Values shown at the failing step (the running total and the number of aces counted as 11 after each `next`):
- What `print *this` showed:
- What `finish` returned for the failing hand, and the correct value:

### Cause and fix

- The line that is wrong, and what it does instead of what it should:
- The change you made:
- How you checked it (which hands, which result):
