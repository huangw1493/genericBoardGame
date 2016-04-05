#include "TTCBoard.h"
#include <iostream>
#include <string>
#include "TTCMove.h"
#include "TTCView.h"

//<> are for system defined files
//"" is for user defined files

using namespace std;

void TTCView::PrintBoard(ostream &s) const{
	s << "- 0 1 2 " << endl;
	for(int x = 0; x < 3; x++) {
		s << x << " ";
		for(int y = 0; y < 3; y++) {
			TTCBoard* tmp = mTTCBoard;
			if(mTTCBoard->mBoard[x][y] == TTCBoard::Player::O) {
				s << "O ";
			}
			else if(mTTCBoard->mBoard[x][y] == TTCBoard::Player::X){
				s << "X ";
			}
			else if(mTTCBoard->mBoard[x][y] == TTCBoard::Player::EMPTY){
				s << ". ";
			}
			else{
				s << mTTCBoard->mBoard[x][y];
			}
		}
		s << endl;
	}
}
