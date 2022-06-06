#ifndef GOBANG_CHESS_H_
#define GOBANG_CHESS_H_

#include <cstring>
#include <vector>
#include <algorithm>

#include "chess.h"

class GoBangChess: public Chess {
public:
    static const int H = 15;
    static const int W = 15; // standard size
    static const int PLAYER_COUNT = 2;

    struct Move {
        int x, y;
		Move(int x_, int y_): x(x_), y(y_) {}
        bool operator == (const Move &r) const {
            return x == r.x && y == r.y;
        }
    };

    struct Hist {
        int x, y, player;
        Hist(int x_, int y_, int player_): x(x_), y(y_), player(player_) {}
    };

    struct Board {
        int content[H][W];
        const int NONE = -1;
        const int MEMSIZE = sizeof(Board);

        int* operator [] (int rhs) const {
            return (int *) content[rhs];
        }
    };

private:
    History<Hist> history;

private:
    Board board;

public:
    GoBangChess() {}
    ~GoBangChess() {}

    void clear() {
        this->current_player = 0;
        this->history.clear();
        std::memset(this->board.content, this->board.NONE, this->board.MEMSIZE);
    }

    void copyHistory(History<Hist> *h) {
        h->clear();
        this->history.copyTo(h);
    }

    void copyFrom(GoBangChess *c) {
        this->current_player = c->currentPlayer();
        c->copyHistory(&this->history);
        memcpy(this->board.content, c->board.content, this->board.MEMSIZE);
    }

    int winner() {
        #define CHECK_DIRE(board, dx, dy) ((board)[(i) + (dx)][(j) + (dy)])
        #define LINE(board, dx, dy, target) (CHECK_DIRE((board), (dx), (dy)) == (target) && \
                                             CHECK_DIRE((board), 2 * (dx), 2 * (dy)) == (target) && \
                                             CHECK_DIRE((board), 3 * (dx), 3 * (dy)) == (target) && \
                                             CHECK_DIRE((board), 4 * (dx), 4 * (dy)) == (target))
        
        const int xlim[4][2] = {{0, H}, {0, H - 4}, {0, H - 4}, {0, H - 4}};
        const int ylim[4][2] = {{0, W - 4}, {0, W}, {0, W - 4}, {4, W}};
        const int dire[4][2] = {{0, 1}, {1, 0}, {1, 1}, {1, -1}};
        for (int k = 0; k < 4; ++ k)
            for (int i = xlim[k][0]; i < xlim[k][1]; ++ i)
                for (int j = ylim[k][0]; j < ylim[k][1]; ++ j) {
                    int now = this->board[i][j];
                    if (now == this->board.NONE) continue;
                    if (LINE(this->board, dire[k][0], dire[k][1], now)) return now;
                }
        return -1;

        #undef CHECK_DIRE
        #undef LINE
    }

    bool checkMove(const Move move) {
        return this->board[move.x][move.y] == this->board.NONE;
    }

    bool move(const Move move) {
        if (!this->checkMove(move))
            return false;
        this->board[move.x][move.y] = this->current_player;
        this->current_player = (this->current_player + 1) % this->PLAYER_COUNT;
        return true;
    }

    void copyBoardTo(Board *b) {
        memcpy(b->content, this->board.content, this->board.MEMSIZE);
    }
};

#endif