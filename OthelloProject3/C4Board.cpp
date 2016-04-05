#include "C4Board.h"
#include <iostream>
#include <string>
#include "C4Move.h"
#include "GameBoard.h"

//<> are for system defined files
//"" is for user defined files


/*
PATCH NOTES
GETPOSSIBLE MOVES SEEMS TO WORK FOR FIRST TURN. DOESNT FIND
RELEVANT MVOES BEYOND THE BOTTOM ROW
APPLY MOVE DOES WEIRD SHIT AND APPLIES MULTIPLE MOVES SOMETIMES
*/


using namespace std;

C4Board::C4Board(){
	mPassCount = 0;
	for(int i = 0; i < 6; i++){
		for(int j = 0; j < 7; j++){
			mBoard[i][j] = C4Board::Player::EMPTY;
		}
	}
	//starts on player 1/black
}

/*
Applies move to the board
*/
void C4Board::ApplyMove(GameMove *move){
	C4Move *m = dynamic_cast<C4Move*>(move);
	int x = m->mRow;
	int y = m->mCol;
	//cout << "Mrow, mCol" << x << ',' << y << endl;
	//Turns selected valid move into player color
	if(m->IsPass() == 1){
		mPassCount++;
	}
	else{
		mPassCount = 0;
		//cout << "Adding piece to" << x << ',' << y << endl;
		mBoard[x][y] = mNextPlayer;
	}
	mHistory.push_back(move);
	mNextPlayer = -mNextPlayer;

	int inc[8][2] = {
		{-1, 1}, {0, 1}, {1, 1}, {-1, 0}, {1, 0}, {-1, -1}, {0, -1}, {1, -1}
	};

	for(int x = 0; x < 6; x++){
		for(int y = 0; y < 7; y++){
			for(int i = 0; i < 8; i++){
				if(((mBoard[x][y] == R) && 
					(mBoard[x + inc[i][0]][y + inc[i][1]] == R) &&
					(InBounds(x + 3 * inc[i][0], y + 3 * inc[i][1]) == 1) &&
					(InBounds(x + 2 * inc[i][0], y + 2 * inc[i][1]) == 1) &&
					(InBounds(x + 1 * inc[i][0], y + 1 * inc[i][1]) == 1) &&
					(mBoard[x + 2 * inc[i][0]][y + 2 * inc[i][1]] == R) &&
					(mBoard[x + 3 * inc[i][0]][y + 3 * inc[i][1]] == R))){
					mValue--;
					//cout << "R wins! Remvoe tshi" << endl;
				}
				if(((mBoard[x][y] == Y) &&
					(mBoard[x + inc[i][0]][y + inc[i][1]] == Y) &&
					(InBounds(x + 3 * inc[i][0], y + 3 * inc[i][1]) == 1) &&
					(InBounds(x + 2 * inc[i][0], y + 2 * inc[i][1]) == 1) &&
					(InBounds(x + 1 * inc[i][0], y + 1 * inc[i][1]) == 1) &&
					(mBoard[x + 2 * inc[i][0]][y + 2 * inc[i][1]] == Y) &&
					(mBoard[x + 3 * inc[i][0]][y + 3 * inc[i][1]] == Y))){
					mValue++;
					//cout << "Y wins! Remvoe this" << endl;
				}
			}
		}
	}
}

void C4Board::UndoLastMove(){
	C4Move *tmp = (C4Move*)mHistory[mHistory.size() - 1];
	mBoard[tmp->mRow][tmp->mCol] = EMPTY;
	delete tmp;
	mNextPlayer = mNextPlayer * -1;
	mHistory.pop_back();
}

void C4Board::GetPossibleMoves(vector<GameMove *> *list) const{
	for(int x = 0; x < 6; x++){
		for(int y = 0; y < 7; y++){
			//cout << "mBoard[x][y+1] = " << (int)mBoard[x][y + 1] << endl;
			if((mBoard[x][y] == EMPTY) && (((x + 1) > 5)
				|| (mBoard[x+1][y] != EMPTY))){
				//cout << "mBoard[" << x << "][" << y <<"] is: " << mBoard[x][y] << endl;
				GameMove *cand = new C4Move(x, y);
				list->push_back((C4Move*)cand);
			}
		}
	}
	(mValue != 0 || list->size() == 0) ? list->push_back(new C4Move(-1, -1)) : 0;
}
