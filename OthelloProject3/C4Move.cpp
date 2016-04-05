#include "C4Move.h"
#include <sstream>
#include <iostream>
#include <string>

int C4Move::mOutstanding = 0;

using namespace std;

C4Move::C4Move() : mRow(-1), mCol(-1){
}

C4Move::C4Move(int row, int col) : mRow(row), mCol(col){
}

GameMove &C4Move :: operator=(const std::string &other){
	if(other == "pass"){
		mRow = -1;
		mCol = -1;
		//Return this object
		return *this;
	}
	mRow = other[1] - '0';
	mCol = other[3] - '0';
	if(mRow > 6 || mCol > 7){
		throw out_of_range("Input out of Bounds");
	}
	return *this;
}

bool C4Move::Equals(const GameMove &other)const {
	return(((mCol == ((C4Move &)other).mCol) && (mRow ==
		((C4Move&)other).mRow)));
}

C4Move :: operator string() const{
	ostringstream format;
	(mRow == -1 && mCol == -1) ? format << "pass" << endl : format << "("
		<< mRow << "," << mCol << ") ";
	return format.str();
}