#ifndef __C4View_H
#define __C4View_H
#include "C4Board.h"
#include "GameView.h"
#include <iostream>
class C4View : public GameView {
private:
	C4Board *mC4Board;
	virtual void PrintBoard(std::ostream &s) const;

public:
	C4View(GameBoard *b) : mC4Board((C4Board*)b) {}
};
#endif