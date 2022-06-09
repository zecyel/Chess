#ifndef GAME_H_
#define GAME_H_

#include "chess.h"
#include "player.h"
#include "interactor.h"

class _game {};

template <Chess *TChess, _player *TPlayer, _interactor *TInteractor>
class Game {
private:
public:
	Game() {}
	~Game() {}
};

#endif