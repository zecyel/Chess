#ifndef INTERACTOR_H_
#define INTERACTOR_H_

#include "chess.h"
#include "game.h"

class _interactor {};

template <Chess *TChess, _game *TGame>
class Interactor: public _interactor {
private:
public:
	Interactor() {}
	~Interactor() {}
};

#endif