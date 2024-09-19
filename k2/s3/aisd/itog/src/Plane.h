#pragma once
#include "Libs.h"

static const int TRIANGULAR = 3;
static const int RECTANGULAR = 4;
static const int HEXAGONAL = 6;

class Plane {
protected:
    std::map<std::pair<int, int>, int> board;
    int neighborsCount;

public:
    Plane(const int planeType) : neighborsCount(planeType) {
        if (planeType != TRIANGULAR && planeType != RECTANGULAR && planeType != HEXAGONAL) {
            throw std::invalid_argument("Invalid plane type");
        }
    }

    void addSand(int x, int y, int value) {
        board[std::make_pair(x, y)] += value;
    }

    void addSand(int x, int y) {
        addSand(x, y, 1);
    }

    void simulate() {
        boardUpdate();
        while (!isStable()) {
            boardUpdate();
        }
    }

private:
    void cellOwerflow(int x, int y) {
        switch (neighborsCount) {
        case TRIANGULAR:
            if ((x + y) % 2 == 0) {
                addSand(x + 1, y);
                addSand(x - 1, y);
                addSand(x, y + 1);
            } else {
                addSand(x + 1, y);
                addSand(x - 1, y);
                addSand(x, y - 1);
            }
            break;
        
        case RECTANGULAR:
            addSand(x + 1, y);
            addSand(x - 1, y);
            addSand(x, y + 1);
            addSand(x, y - 1);
            break;

        case HEXAGONAL:
            addSand(x + 1, y);
            addSand(x - 1, y);
            if (x % 2 == 0) {
                addSand(x + 1, y + 1);
                addSand(x - 1, y + 1);
                addSand(x, y + 1);
            } else {
                addSand(x + 1, y - 1);
                addSand(x - 1, y - 1);
                addSand(x, y - 1);
            }
            break;
        }
    }

    bool isStable() {
        for (auto& [position, value] : board) {
            if (value >= neighborsCount) {
                return false;
            }
        }
        return true;
    }

    void boardUpdate() {
        for (auto& [position, value] : board) {
            int x = position.first;
            int y = position.second;
            if (value >= neighborsCount) {
                board[std::make_pair(x, y)] -= neighborsCount;
                // if (board[std::make_pair(x, y)] == 0) {
                //     board.erase(std::make_pair(x, y));
                // }
                cellOwerflow(x, y);
            }
        }
    }
};
