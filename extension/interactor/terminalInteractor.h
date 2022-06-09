#ifndef TERMINAL_INTERACTOR_H_
#define TERMINAL_INTERACTOR_H_

#include <iostream>
#include <cstring>

#include "include/chess.h"
#include "include/interactor.h"

template <Chess *TChess>
class TerminalInteractor: public Interactor {
private:
    std::istream *fin;
    std::ostream *fout;
    DisplayScheme *ds;
    TChess *chess;
public:
    TerminalInteractor(std::istream *fin_, std::ostream *fout_, DisplayScheme *ds_, TChess *chess_): fin(fin_), fout(fout_), ds(ds_), chess(chess_) {}
    ~TerminalInteractor() {}

    void update() {
        string rowIndex = this->ds->fetch("rowIndex", "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ".splice(0, TChess::Board::H));
        string columnIndex = this->ds->fetch("columnIndex", "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ".splice(0, TChess::Board::W));
        this->fout << ' ' << columnIndex;
        TChess::Board b;
        this->chess->copyBoard(&b);
        for (int i = 0; i < TChess::Board::H; ++ i) {
            this->fout << rowIndex[i];
            for (int j = 0; j < TChess::Board::W; ++ j)
                this->fout << this->ds->image[b[i][j]];
        }
    }

    TChess::Move getMove() {
        this->fout << this->ds->fetch("hint", "Please input your move: ");
        std::string answer;
        this->fin << answer;
        return TChess::Move(answer);
    }
};

#endif