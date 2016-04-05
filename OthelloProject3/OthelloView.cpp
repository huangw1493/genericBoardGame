#include "OthelloView.h"

using namespace std;

void OthelloView::PrintBoard(ostream &s) const{
	s << "~ 0 1 2 3 4 5 6 7" << endl;
	for(int x = 0; x < 8; x++) {
		s << x << " ";
		for(int y = 0; y < 8; y++) {
			OthelloBoard* tmp = mOthelloBoard;
			if(mOthelloBoard->mBoard[x][y] == OthelloBoard::Player::BLACK) {
				s << "W ";
			}
			else if(mOthelloBoard->mBoard[x][y] == OthelloBoard::Player::WHITE){
				s << "B ";
			}
			else if(mOthelloBoard->mBoard[x][y] == OthelloBoard::Player::EMPTY){
				s << ". ";
			}
			else{
				s << mOthelloBoard->mBoard[x][y];
			}
		}
		s << endl;
	}
}

/*Not Needed?
ostream& operator<< (ostream &lhs, const OthelloView &rhs){
	rhs.PrintBoard(lhs);
	return lhs;
}
*/