#ifndef GOBANG_CHESS_H_
#define GOBANG_CHESS_H_

#include <cstring>
#include <vector>
#include <algorithm>

#include "chess.h"

class GoBangChess: public Chess {
public:
    const int PLAYER_COUNT = 2;

    struct Move {
        int x, y;
        Move() {}
		Move(int x_, int y_): x(x_), y(y_) {}
        Move(char pos[2]) { // as the standard notation
            x = y = -1;
            if (pos[0] >= 49 && pos[0] <= 57) x = pos[0] - 49;
            if (pos[0] >= 65 && pos[0] <= 70) x = pos[0] - 56;
            if (pos[1] >= 49 && pos[1] <= 57) y = pos[1] - 49;
            if (pos[1] >= 65 && pos[1] <= 70) y = pos[1] - 56;
        }
        bool operator == (const Move &r) const {
            return x == r.x && y == r.y;
        }
    };

    struct Hist {
        int x, y, player;
        Hist() {}
        Hist(int x_, int y_, int player_): x(x_), y(y_), player(player_) {}
    };

    struct Board {
        static const int H = 15;
        static const int W = 15; // standard size
        int content[H][W];
        const int NONE = -1;
        const int MEMSIZE = H * W * sizeof(int);

        int* operator [] (int rhs) const {
            return (int *) content[rhs];
        }
        void clear() {
            std::memset(content, NONE, MEMSIZE);
        }
    };

private:
    History<Hist> history;

protected:
    Board board;

public:
    GoBangChess() {}
    ~GoBangChess() {}

    void clear() {
        this->current_player = 0;
        this->history.clear();
        this->board.clear();
    }

    void copyHistory(History<Hist> *h) {
        h->clear();
        this->history.copyTo(h);
    }

    void copyBoard(Board *b) {
        memcpy(b->content, this->board.content, this->board.MEMSIZE);
    }

    void copyFrom(GoBangChess *c) {
        this->current_player = c->currentPlayer();
        c->copyHistory(&this->history);
        c->copyBoard(&this->board);
    }

    int winner() {
        #define CHECK_DIRE(board, dx, dy) ((board)[(i) + (dx)][(j) + (dy)])
        #define LINE(board, dx, dy, target) (CHECK_DIRE((board), (dx), (dy)) == (target) && \
                                             CHECK_DIRE((board), 2 * (dx), 2 * (dy)) == (target) && \
                                             CHECK_DIRE((board), 3 * (dx), 3 * (dy)) == (target) && \
                                             CHECK_DIRE((board), 4 * (dx), 4 * (dy)) == (target))
        
        const int xlim[4][2] = {{0, Board::H}, {0, Board::H - 4}, {0, Board::H - 4}, {0, Board::H - 4}};
        const int ylim[4][2] = {{0, Board::W - 4}, {0, Board::W}, {0, Board::W - 4}, {4, Board::W}};
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
        this->board[move.x][move.y] = this->currentPlayer();
        this->history.append(Hist(move.x, move.y, this->currentPlayer()));
        this->current_player = (this->currentPlayer() + 1) % this->PLAYER_COUNT;
        return true;
    }

};

#endif