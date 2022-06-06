#ifndef PLAYER_H_
#define PLAYER_H_

#include "chess.h"

class _player {};

template <Chess *TChess, _game *TGame>
class Player: public _player {
private:
public:
	Player() {}
	~Player() {}
	
	TChess::Move Move() {}
};

#endif