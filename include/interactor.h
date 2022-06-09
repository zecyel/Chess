#ifndef INTERACTOR_H_
#define INTERACTOR_H_

#include <map>

#include "chess.h"

class _interactor {};

template <class TChess>
class Interactor: public _interactor {
public:
	Interactor() {}
	~Interactor() {}
	void update();

	template <Chess TChess> // I give up.
	TChess::Move getMove(); // I just cannot fix it
};

struct DisplayScheme {
	std::map<std::string, std::string> config;
	std::map<int, std::string> image;

	std::string fetch(std::string key, std::string value) {
		// `value` is for backup option, in case the `key` hasn't registered.
		if (this->config.find(key) != this->config.end())
			return this->config[key];
		return value;
	};
};

#endif