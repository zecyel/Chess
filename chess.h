#ifndef CHESS_H_
#define CHESS_H_

#include <vector>


template <typename Hist>
class History {
private:
    std::vector<Hist> v;
public:
    History() {}
    ~History() {}
    void clear() {
        this->v.clear();
    }
    void append(Hist hist) {
        this->v.push_back(hist);
    }
    void copyTo(std::vector<Hist> *a) {
        a->clear();
        for (Hist i: this->v)
            a->push_back(i);
    }
    void copyTo(History *a) {
        this->copyTo(a->v);
    }
    void copyFrom(const std::vector<Hist> *a) {
        this->clear();
        for (Hist i: a)
            this->v.push_back(i);
    }
    void copyFrom(const History *a) {
        this->copyFrom(a->v);
    }
};

class Chess {
protected:
    int current_player;
public:
    struct Move;
    struct Hist;
    struct Board;

    Chess() {}
    ~Chess() {}
    bool checkMove(const Move move); // check if the move is valid
    bool move(const Move move); // do move
    int winner(); // check if there's winner
    int currentPlayer() { // who's now playing
        return this->current_player;
    }
    void clear();
    void copyHistory(History<Hist> *h);
    void copyFrom(Chess *c); // the make itself a clone of `c'
    void copyBoardTo(Board *b);
};

#endif