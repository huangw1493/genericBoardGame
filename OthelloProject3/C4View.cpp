#include "C4Board.h"
#include <iostream>
#include <string>
#include "C4Move.h"
#include "C4View.h"

//<> are for system defined files
//"" is for user defined files

using namespace std;

void C4View::PrintBoard(ostream &s) const{
	s << "- 0 1 2 3 4 5 6 " << endl;
	for(int x = 0; x < 6; x++) {
		s << x << " ";
		for(int y = 0; y < 7	; y++) {
			C4Board* tmp = mC4Board;
			if(mC4Board->mBoard[x][y] == C4Board::Player::R) {
				s << "R ";
			}
			else if(mC4Board->mBoard[x][y] == C4Board::Player::Y){
				s << "Y ";
			}
			else if(mC4Board->mBoard[x][y] == C4Board::Player::EMPTY){
				s << ". ";
			}
			else{
				s << mC4Board->mBoard[x][y];
			}
		}
		s << endl;
	}
}
