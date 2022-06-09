#ifndef VOID_CHESS_H_
#define VOID_CHESS_H_

#include <cstring>
#include "include/chess.h"

// to make code clear or simple is a dilemma
#ifdef WANT_TO_HAVE_VOID_HISTORY
template <typename Hist>
class VoidHistory: public History<Hist> {};
#endif

class VoidChess: public Chess {
public:
    static const int PLAYER_COUNT = 2; // maybe not?
    struct Move {
        // define something.
        Move(/* paramters */) {}
        bool operator == (const Move &r) const {
            // you may need it
        }
    };

    struct Hist {
        // define something.
        Hist(/* paramters */) {}
    };

    struct Board {
        static const int H = 19; // assume the board is a rect
        static const int W = 19; // size as you like
        int content[H][W];
        const int NONE = -1; // what to place in if there's nothing on the board
        const int MEMSIZE = H * W * sizeof(int);

        void clear() {
            std::memset(content, NONE, MEMSIZE);
        }
        void copyTo(Board *b) {
            std::memcpy(b->content, content, MEMSIZE);
        }
    };

protected:
    Board board;

private:
#ifdef WANT_TO_HAVE_VOID_HISTORY
    VoidHistory<Hist> history;
#else
    History<Hist> history;
#endif

protected:
    // some definitions about the board.

public:
    VoidChess() {}
    ~VoidChess() {}

    void clear() {
        this->current_player = 0;
        this->history.clear();
        this->board.clear();
    }

#ifdef WANT_TO_HAVE_VOID_HISTORY
    void copyHistory(VoidHistory<Hist> *h) {
        this->history.copyTo(h);
    }
#else
    void copyHistory(History<Hist> *h) {
        this->history.copyTo(h);
    }
#endif

    void copyBoard(Board *b) {
        this->board.copyTo(b);
    }

    void copyFrom(VoidChess *c) {
        this->current_player = c->current_player;
        c->copyHistory(&this->history);
        c->copyBoard(&this->board);
    }

    int winner() {
        // do check
    }

    bool checkMove(const Move move) {
        // check if the move is vaild according to the board.
    }

    bool move(const Move move) {
        if (!this->checkMove(move))
            return false;

        // generate a Hist struct and append it to this->history.
        // and make changes to the board.

        this->current_player = (this->current_player + 1) % this->PLAYER_COUNT;
        return true;
    }

};

#endif