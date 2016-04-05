#include "TTCBoard.h"
#include <iostream>
#include <string>
#include "TTCMove.h"
#include "GameBoard.h"

//<> are for system defined files
//"" is for user defined files

using namespace std;

TTCBoard::TTCBoard(){
	mPassCount = 0;
	const int TBOARD_SIZE = 3;
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			mBoard[i][j] = TTCBoard::Player::EMPTY;
		}
	}
	//starts on player 1/black
}

/*
Applies move to the board
*/
void TTCBoard::ApplyMove(GameMove *move){
	TTCMove *m = (TTCMove*)move;
	int x = m->mRow;
	int y = m->mCol;

	//Turns selected valid move into player color
	if(((TTCMove*)move)->IsPass() == 1){
		mPassCount++;
	}
	else{
		mPassCount = 0;
		mBoard[x][y] = mNextPlayer;
	}
	mHistory.push_back(move);
	mNextPlayer = -mNextPlayer;
	
	int inc[8][2] = {
		{-1, 1}, {0, 1}, {1, 1}, {-1, 0}, {1, 0}, {-1, -1}, {0, -1}, {1, -1}
	};
	
	for(int x = 0; x < 3; x++){
		for(int y = 0; y < 3; y++){
			for(int i = 0; i < 8; i++){
				if(((mBoard[x][y] == X) && 
				 (InBounds(x + 2*inc[i][0],y + 2*inc[i][1]) == 1) &&
				 (mBoard[x + inc[i][0]][y + inc[i][1]] == X) && 
				 (mBoard[x + 2 * inc[i][0]][y + 2 * inc[i][1]] == X))){
					(mValue == 0) ? mValue++ : 0;
					//cout << "X wins! Remvoe tshi" << endl;
				}
				else if(((mBoard[x][y] == O) &&
					(InBounds(x + 2 * inc[i][0], y + 2 * inc[i][1]) == 1) &&
					(mBoard[x + inc[i][0]][y + inc[i][1]] == O) &&
					(mBoard[x + 2 * inc[i][0]][y + 2 * inc[i][1]] == O))){
					(mValue == 0) ? mValue++ : 0;
					//cout << "O wins! Remvoe tshi" << endl;
				}
			}
		}
	}
}

void TTCBoard::UndoLastMove(){
	TTCMove *tmp = (TTCMove*)mHistory[mHistory.size() - 1];
	mBoard[tmp->mRow][tmp->mCol] = EMPTY;
	if(mNextPlayer == X && mValue != 0){
		mValue += 1;
	}
	if(mNextPlayer == O && mValue != 0){
		mValue -= 1;
	}
	delete tmp;
	mNextPlayer = mNextPlayer * -1;
	mHistory.pop_back();
}

void TTCBoard::GetPossibleMoves(vector<GameMove *> *list) const{
	for(int x = 0; x < 3; x++){
		for(int y = 0; y < 3; y++){
			if(mBoard[x][y] == EMPTY){
				GameMove *cand = new TTCMove(x, y);
				list->push_back((TTCMove*)cand);
			}
		}
	}
	(mValue != 0 || list->size() == 0) ? list->push_back(new TTCMove(-1, -1)) : 0;
}
