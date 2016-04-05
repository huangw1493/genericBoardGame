#include "OthelloMove.h"
#include <iostream>
#include <string>
#include <sstream>

//Constructors
//Default constructor

int OthelloMove::mOnHeap = 0;
OthelloMove::OthelloMove() : mRow(-1), mCol(-1){}

//2 parameter constructor
OthelloMove::OthelloMove(int row, int col) : mRow(row), mCol(col){}

//Add void AddFlipSet? I think it's already coded in the h

//Operator=. Move gets inputted in format "(x,y)"
GameMove &OthelloMove::operator=(const std::string &other){
	if(other == "pass"){
		mRow = -1;
		mCol = -1;
		return *this;
	}
	mRow = other[1] - '0';
	//std::cout << mRow << std::endl;
	mCol = other[3] - '0';
	//std::cout << mCol<< std::endl;
	if(mRow > 7 || mCol > 7){
		std::cout << "Out of Bounds input" << std::endl;
	}
	return *this;
}

OthelloMove :: operator std::string() const{
	std::ostringstream format;
	(mRow == -1 && mCol == -1) ? format << "pass" << std::endl : format << "("
		<< mRow << "," << mCol << ") ";
	return format.str();
}

bool OthelloMove::Equals(const GameMove &other)const {
	return(((mCol == ((OthelloMove &)other).mCol) && (mRow ==
		((OthelloMove&)other).mRow)));
}
/*Not needed?
bool operator==(const OthelloMove &lhs, const OthelloMove &rhs){
	return ((lhs.mCol == rhs.mCol) && (lhs.mRow == rhs.mRow));
}
*/