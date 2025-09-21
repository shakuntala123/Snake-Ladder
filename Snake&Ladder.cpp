#include <bits/stdc++.h>
using namespace std;

// ---------------- Player Class ----------------
class GamePlayer {
public:
    int id;
    int position;
    int rank;

    GamePlayer(int _id) {
        id = _id;
        position = 1;
        rank = -1; // -1 indicates player hasn't finished yet
    }
};

// ---------------- Moving Entity Class ----------------
class MovingEntity {
protected:
    int endPos;
    string desc;

public:
    MovingEntity(int endPos, string desc) {
        this->endPos = endPos;
        this->desc = desc;
    }

    int getEndPos() { return endPos; }
    string getDesc() { return desc; }
};

// ---------------- Snake Class ----------------
class Snake : public MovingEntity {
public:
    Snake(int endPos) : MovingEntity(endPos, "Bit by Snake") {}
};

// ---------------- Ladder Class ----------------
class Ladder : public MovingEntity {
public:
    Ladder(int endPos) : MovingEntity(endPos, "Climbed Ladder") {}
};

// ---------------- Board Class ----------------
class Board {
private:
    int size;
    unordered_map<int, MovingEntity*> entities;

public:
    Board(int size) { this->size = size; }

    void setEntity(int pos, MovingEntity* entity) {
        entities[pos] = entity;
    }

    int getNextPos(int pos) {
        if (pos > size) return pos;
        if (entities.count(pos)) {
            cout << entities[pos]->getDesc() << " at position " << pos << endl;
            return entities[pos]->getEndPos();
        }
        return pos;
    }

    bool atLastPos(int pos) { return pos == size; }

    int getSize() { return size; }
};

// ---------------- Dice Class ----------------
class Dice {
private:
    int sides;

public:
    Dice(int sides) { this->sides = sides; }

    int roll() {
        return rand() % sides + 1;
    }
};

// ---------------- Game Class ----------------
class Game {
private:
    Board* board;
    Dice* dice;
    vector<GamePlayer*> players;
    int turn = 0;
    int lastRank = 0;
    int consecutiveSix = 0;

public:
    void initialize(Board* board, int diceSides, int playerCount) {
        this->board = board;
        dice = new Dice(diceSides);
        for (int i = 0; i < playerCount; i++)
            players.push_back(new GamePlayer(i));
    }

    bool canPlay() { return lastRank != players.size(); }

    GamePlayer* getNextPlayer() {
        while (true) {
            if (players[turn]->rank == -1)
                return players[turn];
            turn = (turn + 1) % players.size();
        }
    }

    void movePlayer(GamePlayer* player, int nextPos) {
        player->position = nextPos;
        if (board->atLastPos(player->position)) {
            player->rank = ++lastRank;
            cout << "Player " << (player->id + 1) << " finished with rank " << player->rank << "!\n";
        }
    }

    bool canMove(GamePlayer* player, int nextPos) {
        return nextPos <= board->getSize() && player->rank == -1;
    }

    void changeTurn(int diceRes) {
        consecutiveSix = (diceRes == 6) ? consecutiveSix + 1 : 0;
        if (diceRes != 6 || consecutiveSix == 3) {
            if (consecutiveSix == 3)
                cout << "Turn skipped due to 3 consecutive sixes!\n";
            turn = (turn + 1) % players.size();
            consecutiveSix = 0;
        } else {
            cout << "Player " << (turn + 1) << " rolls again!\n";
        }
    }

    void play() {
        while (canPlay()) {
            GamePlayer* player = getNextPlayer();
            cout << "\nPlayer " << (turn + 1) << " press Enter to roll dice...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            int diceRes = dice->roll();
            cout << "Player " << (turn + 1) << " rolled: " << diceRes << endl;

            int nextPos = board->getNextPos(player->position + diceRes);
            if (canMove(player, nextPos))
                movePlayer(player, nextPos);

            changeTurn(diceRes);
            printState();
        }
        printResult();
    }

    void printState() {
        cout << "---------- Game State ----------\n";
        for (auto p : players) {
            cout << "Player " << (p->id + 1) << " at position " << p->position
                 << " (Rank: " << p->rank << ")\n";
        }
        cout << "--------------------------------\n";
    }

    void printResult() {
        cout << "\n---------- Final Result ----------\n";
        sort(players.begin(), players.end(), [](GamePlayer* a, GamePlayer* b) {
            return a->rank < b->rank;
        });
        for (auto p : players) {
            cout << "Player " << (p->id + 1) << " - Rank: " << p->rank << endl;
        }
        cout << "----------------------------------\n";
    }
};

// ---------------- Main Function ----------------
int main() {
    srand(time(0));

    // Board setup
    Board* board = new Board(30);
    board->setEntity(14, new Snake(7));
    board->setEntity(25, new Snake(5));
    board->setEntity(3, new Ladder(22));
    board->setEntity(11, new Ladder(28));

    // Initialize game
    Game game;
    game.initialize(board, 6, 2);

    // Start game
    game.play();

    return 0;
}
