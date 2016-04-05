#ifndef __TTCBOARD_H
#define __TTCBOARD_H

#include <vector>
#include "TTCMove.h"
#include "GameBoard.h"
#include "GameMove.h"

const int TBOARD_SIZE = 3;

class TTCBoard : public GameBoard {

public:
	enum Player {EMPTY = 0, X = 1, O = -1};

	TTCBoard();

   virtual ~TTCBoard() {}

   virtual void GetPossibleMoves(std::vector<GameMove *> *list) const;

   virtual void ApplyMove(GameMove *move);
   
   virtual void UndoLastMove();
   
   virtual GameMove *CreateMove() const {return new TTCMove;}

   inline static bool InBounds(int row, int col) {return row >= 0 
      && row < TBOARD_SIZE && col >= 0 && col < TBOARD_SIZE;}

   virtual bool IsFinished() const {
		return (mValue != 0) || (mPassCount != 0);
   }

   virtual std::string GetPlayerString(char player) {
      return (player == 1 ? "X" : "O");
   }

private:
	friend class TTCView;

	char mBoard[TBOARD_SIZE][TBOARD_SIZE];
   static char mWeights[TBOARD_SIZE][TBOARD_SIZE];
   int mPassCount;
};
#endif