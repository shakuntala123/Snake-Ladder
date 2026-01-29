
#Snake and Ladder Game

A simple console-based Snake and Ladder game implemented in C++ with object-oriented programming principles. Players roll dice, climb ladders, and avoid snakes to reach the final position.

---

## Features

- Multiple players support
- Dice rolls with configurable sides
- Snakes and ladders with custom positions
- Automatic ranking when players finish
- Consecutive six rules (player rolls again if they get a 6, but turn is skipped on 3 consecutive sixes)
- Real-time game state display
- Fully object-oriented design

---

## Classes

### GamePlayer
Represents a player in the game.

**Attributes:**
- `id` – Player ID
- `position` – Current position on the board
- `rank` – Finishing rank (-1 if not finished)

### MovingEntity
Base class for snakes and ladders.

**Attributes:**
- `endPos` – Position to move the player to
- `desc` – Description of the entity

**Derived Classes:**
- `Snake` – Player moves backward
- `Ladder` – Player moves forward

### Board
Represents the game board.

**Attributes:**
- `size` – Number of cells on the board
- `entities` – Map of snakes and ladders

**Methods:**
- `setEntity(pos, entity)` – Add a snake or ladder
- `getNextPos(pos)` – Returns the next position of the player after entity interaction
- `atLastPos(pos)` – Checks if the player has reached the end

### Dice
Represents a dice.

**Attributes:**
- `sides` – Number of sides on the dice

**Methods:**
- `roll()` – Returns a random number between 1 and sides

### Game
Controls the flow of the game.

**Attributes:**
- `board` – Game board
- `dice` – Dice object
- `players` – List of players
- `turn` – Current player's turn
- `lastRank` – Last assigned rank
- `consecutiveSix` – Counter for consecutive sixes

**Methods:**
- `initialize(board, diceSides, playerCount)` – Sets up the game
- `play()` – Main game loop
- `getNextPlayer()` – Returns the next player to play
- `movePlayer(player, nextPos)` – Moves the player and updates rank if finished
- `canMove(player, nextPos)` – Checks if the move is valid
- `changeTurn(diceRes)` – Handles turn switching and consecutive six logic
- `printState()` – Prints the current state of all players
- `printResult()` – Prints the final ranking

---

## How to Play

**Compile the game:**

```bash
g++ -o SnakeLadder main.cpp
