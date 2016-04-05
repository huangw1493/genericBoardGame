#ifndef __C4Board_H
#define __C4Board_H

#include <vector>
#include "C4Move.h"
#include "GameBoard.h"
#include "GameMove.h"

const int TBOARD_SIZEX = 6;
const int TBOARD_SIZEY = 7;


class C4Board : public GameBoard {

public:
	enum Player { EMPTY = 0, Y = 1, R = -1 };

	C4Board();

	virtual ~C4Board() {}

	virtual void GetPossibleMoves(std::vector<GameMove *> *list) const;

	virtual void ApplyMove(GameMove *move);

	virtual void UndoLastMove();

	virtual GameMove *CreateMove() const { return new C4Move; }

	inline static bool InBounds(int row, int col) {
		return row >= 0
			&& row < TBOARD_SIZEX && col >= 0 && col < TBOARD_SIZEY;
	}

	virtual bool IsFinished() const {
		return mPassCount == 1 || mValue != 0;
	}

	virtual std::string GetPlayerString(char player) {
		return (player == 1 ? "Y" : "R");
	}

private:
	friend class C4View;

	char mBoard[TBOARD_SIZEX][TBOARD_SIZEY];
	static char mWeights[TBOARD_SIZEX][TBOARD_SIZEY];
	int mPassCount;
};
#endif