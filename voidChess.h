#ifndef VOID_CHESS_H_
#define VOID_CHESS_H_

#include "chess.h"

// to make code clear or simple is a dilemma
#ifdef WANT_TO_HAVE_VOID_HISTORY
template <typename Hist>
class VoidHistory: public History<Hist> {};
#endif

class VoidChess: public Chess {
public:
    struct Move {
        // define something.
        Move(/* paramters */) {}
    };

    struct Hist {
        // define something.
        Hist(/* paramters */) {}
    };
    static const int PLAYER_COUNT = 2; // maybe not?

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
        // clear the board
    }

#ifdef WANT_TO_HAVE_VOID_HISTORY
    void copyHistory(VoidHistory<Hist> *h) {
        h->clear();
        this->history.copyTo(h);
    }
#else
    void copyHistory(History<Hist> *h) {
        h->clear();
        this->history.copyTo(h);
    }
#endif

    void copyFrom(VoidChess *c) {
        this->current_player = c->currentPlayer();
        c->copyHistory(&this->history);
        // and copy the board
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