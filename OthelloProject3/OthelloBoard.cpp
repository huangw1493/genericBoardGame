#include "OthelloBoard.h"
#include <iostream>
#include <string>
#include "OthelloMove.h"
#include "GameBoard.h"

//<> are for system defined files
//"" is for user defined files

using namespace std;

OthelloBoard::OthelloBoard(){
	const int BOARDSIZE = 8;
	for(int x = 0; x < 8; x++){
		for(int y = 0; y < 8; y++){
			mBoard[x][y] = OthelloBoard::Player::EMPTY;
		}
	}
	mBoard[3][4] = OthelloBoard::Player::WHITE;
	mBoard[4][3] = OthelloBoard::Player::WHITE;
	mBoard[4][4] = OthelloBoard::Player::BLACK;
	mBoard[3][3] = OthelloBoard::Player::BLACK;
}

/*
Applies move to the board
*/
void OthelloBoard::ApplyMove(GameMove *move){
	OthelloMove *m = dynamic_cast<OthelloMove*>(move);
	if(m == nullptr){
//		throw OthelloException("Tried to apply a non OthelloMove");
	}
	int inc[8][2] = {
		{-1, 1}, {0, 1}, {1, 1}, {-1, 0}, {1, 0}, {-1, -1}, {0, -1}, {1, -1}
	};
	
	if(m->IsPass())
		mPassCount++;
	else{
		//Reset passes
		mPassCount = 0;
		//set board piece to player
		mBoard[m->mRow][m->mCol] = mNextPlayer;
		//mBoard[((OthelloMove*)move)->mRow][((OthelloMove*)move)->mCol] = mNextPlayer;
		mNextPlayer == WHITE ? mValue -= 1 : mValue += 1;

		//Loop for each direction in the inc matrix
		for(int i = 0; i < 8; i++){
			//pcs is number of pieces. fin is a flag for flip elligiility
			int pcs = 0, fin = 0, x = ((OthelloMove*)move)->mRow,
				y = ((OthelloMove*)move)->mCol, a = x, b = y;
			//As long as the next piece is in bounds. This will check until 8 limit
			while(InBounds(a + inc[i][0], b + inc[i][1]) == true){
				//if the matrix inthe following direction is the opposite player
				//increase piece count by 1
				if(mBoard[a + inc[i][0]][b + inc[i][1]] == mNextPlayer*-1){
					pcs++;
					a = a + inc[i][0];
					b = b + inc[i][1];
					//if the next piece after that is yours. Set fin count to 1
					//This signals its safe to flip pieces
					fin = 0;
				}
				else if(mBoard[a + inc[i][0]][b + inc[i][1]] == mNextPlayer){
					(pcs > 0) ? fin = 1 : 0;
					break;
				}
				else if(mBoard[a + inc[i][0]][b + inc[i][1]] == 0)
					break;
			}
			//Now that we have checked for flip elligebility, we can flip
			//Add flip sets
			if(fin == 1){
				(mNextPlayer == 1) ? mValue -= (2 * pcs) : mValue += (2 * pcs);
				((OthelloMove*)move)->AddFlipSet(OthelloMove::FlipSet(pcs, inc[i][0], inc[i][1]));
			}
			//Actually flip pieces
			while((pcs != 0) && (fin == 1)){
				//Starting at the 2nd from furthest piece, change it to the opposite piece
				mBoard[a][b] = mBoard[a][b] * -1;
				//Decrement position
				a = a - inc[i][0];
				b = b - inc[i][1];
				//Decrement pieces
				pcs--;
			}
		}
	}
	//push move into flipset
	mHistory.push_back(move);
	//Switch players
	mNextPlayer = -mNextPlayer;
}

void OthelloBoard::UndoLastMove(){
	OthelloMove *tmp = (OthelloMove*)mHistory[mHistory.size() - 1];
	vector<OthelloMove::FlipSet> ::iterator itr = (tmp->mFlips.begin());
	int x = tmp->mRow;
	int y = tmp->mCol;
	mBoard[x][y] = EMPTY;
	if(mNextPlayer == WHITE)
		mValue += 1;
	else if(mNextPlayer == BLACK)
		mValue -= 1;
	itr = tmp->mFlips.begin();

	for(itr = tmp->mFlips.begin(); itr < tmp->mFlips.end(); itr++){
		int x = tmp->mRow;
		int y = tmp->mCol;

		for(int i = 0; i < itr->switched; i++){
			x += itr->rowDelta;
			y += itr->colDelta;
			mBoard[x][y] = mNextPlayer;
			(mNextPlayer == WHITE) ? mValue += 2 : mValue -= 2;
		}
	}
	delete tmp;
	mNextPlayer = mNextPlayer*-1;
	mHistory.pop_back();
}
/*
void OthelloBoard::GetPossibleMoves(vector<GameMove *> *list) const{
int inc[8][2] = {{-1, 1}, {0, 1}, {1, 1}, {-1, 0}, {1, 0}, {-1, -1},
{0, -1}, {1, -1}};
for(int x = 0; x < 8; x++){
for(int y = 0; y < 8; y++){
//8 loops in 8 directions
for(int i = 0; i < 8; i++){
int pieces = 0, a = x, b = y, fin = 0;
while(InBounds(a + inc[i][0], y + inc[i][1]) == true){
//	cout << "eat a dick" << endl;
//if the matrix in the following direction is the opposite player
//increase pieces count by 1
if(mBoard[x][y] == EMPTY){
if(mBoard[a + inc[i][0]][b + inc[i][1]] == mNextPlayer*-1){
pieces++;
a = a + inc[i][0];
b = b + inc[i][1];
fin = 0;
//if the next piece after that is yours. Set fin count to 1
//This signals its safe to flip pieces
fin = mBoard[x + inc[i][0]][y + inc[i][1]]
== mNextPlayer ? 1 : 0;
}
else//Otherwise break out of the while
break;
}
else
break;
}
//While there are pieces to flip and its safe to flip. mark each piece
if((fin == 1)){
int NRFlag = 1;
x = a;
y = b;
vector<GameMove*> ::iterator itr = (list->begin());
GameMove *cand = new OthelloMove(x, y);
for(vector<GameMove*> ::iterator itr = (list->begin());
itr < list->end(); itr++){
(*cand == **itr) ? NRFlag = 0 : NRFlag = 1;
}
(NRFlag == 1) ? list->push_back((OthelloMove*)cand) : 0;
}
}
}
}

//If there is no possible moves. push back a pass
(list->size() == 0) ? list->push_back(new OthelloMove(-1, -1)) : 0;
}*/

void OthelloBoard::GetPossibleMoves(vector<GameMove *> *list) const{
	int inc[8][2] = {{-1, 1}, {0, 1}, {1, 1}, {-1, 0}, {1, 0}, {-1, -1},
	{0, -1}, {1, -1}};

	for(int x = 0; x < 8; x++){
		for(int y = 0; y < 8; y++){
			//8 loops in 8 directions
			for(int i = 0; i < 8; i++){
				int pieces = 0, a = x, b = y, fin = 0;
				while(InBounds(a + inc[i][0], y + inc[i][1]) == true){
					//if the matrix in the following direction is the opposite player
					//increase pieces count by 1
					if(mBoard[x][y] == EMPTY){
						if(mBoard[a + inc[i][0]][b + inc[i][1]] == mNextPlayer*-1){
							pieces++;
							a = a + inc[i][0];
							b = b + inc[i][1];
							fin = 0;
							//if the next piece after that is yours. Set fin count to 1
							//This signals its safe to flip pieces
						}
						else if(mBoard[a + inc[i][0]][b + inc[i][1]] == mNextPlayer){
							(pieces > 0) ? fin = 1 : 0;
							break;
						}
						else//Otherwise break out of the while
							break;
					}
					else
						break;
				}
				//While there are pieces to flip and its safe to flip. mark each piece
				if((fin == 1)){
					//int NRFlag = 1;
					//for(int i = 0; i < (list->size()); i++){
					//	int tempRow = (list->at(i)))->mRow;
					//	int tempCol = (list->at(i)))->mCol;
					//	(x == tempRow && y == tempCol) ? NRFlag = 0 : NRFlag = 1;
					list->push_back(new OthelloMove(x, y));
				}
				//(NRFlag == 1) ? list->push_back(new OthelloMove(x, y)) : 0;
			}
		}
	}
	//If there is no possible moves. push back a pass
	list->size() == 0 ? list->push_back(new OthelloMove(-1, -1)) : 0;
}


/*
void OthelloBoard::GetPossibleMoves(vector<GameMove *> *list) const{
for(int x = 0; x < 8; x++){
for(int y = 0; y < 8; y++){
int inc[8][2] = {{0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}, {-1, 0}
, {-1, 1}
};
//8 loops into the 8 directions
for(int i = 0; i < 8; i++){
int piece = 0, a = x, b = y, fin = 0;
while(InBounds(x + inc[i][0], y + inc[i][1]) == true){
//if the- matrix inthe following direction is the opposite
//increase piece count by 1
if(mBoard[a][b] == EMPTY){
if(mBoard[x + inc[i][0]][y + inc[i][1]] == -mNextPlayer){
piece++;
x = x + inc[i][0];
y = y + inc[i][1];
//if the next piece after that is yours. Set fin to 1
//This signals its safe to flip pieces
fin = mBoard[x + inc[i][0]][y + inc[i][1]]
== mNextPlayer ? 1 : 0;
}
else
break;
}
else
break;

}
//While there are enemies and its safe to flip. Flip each pirece
if((fin == 1)){
int NRFlag = 1;
x = a;
y = b;
//Checks for repeats
//vector<GameMove*> ::iterator itr = (list->begin());
GameMove *cand = new OthelloMove(x, y);
for(vector<GameMove*> ::iterator itr = (list->begin());
itr < list->end(); itr++){
if(*cand == **itr){
NRFlag = 0;
}
else{
NRFlag = 1;
}
}
if(NRFlag == 1){
list->push_back((OthelloMove*)cand);
}
//Memory Leak without deleting?
//delete cand;
}
//Resets x and y values
x = a;
y = b;
}
}
}
cout << "List size: " << list->size() << endl;
list->size() == 0 ? list->push_back(new OthelloMove(-1, -1)) : 0;
}*/