#ifndef __TTCVIEW_H
#define __TTCVIEW_H
#include "TTCBoard.h"
#include "GameView.h"
#include <iostream>
class TTCView : public GameView {
private:
	TTCBoard *mTTCBoard;
	virtual void PrintBoard(std::ostream &s) const;

public:
   TTCView(GameBoard *b) : mTTCBoard((TTCBoard*)b) {}
};
#endif