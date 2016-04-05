#include "TTCMove.h"
#include <sstream>
#include <iostream>
#include <string>

int TTCMove::mOutstanding = 0;

using namespace std;

TTCMove::TTCMove() : mRow(-1), mCol(-1){
}

TTCMove::TTCMove(int row, int col) : mRow(row), mCol(col){
}

GameMove &TTCMove :: operator=(const std::string &other){
	if(other == "pass"){
		mRow = -1;
		mCol = -1;
		//Return this object
		return *this;
	}
	mRow = other[1] - '0';
	mCol = other[3] - '0';
	if(mRow > 2 || mCol > 2){
		throw out_of_range("Input out of Bounds");
	}
	return *this;
}

bool TTCMove::Equals(const GameMove &other)const {
	return(((mCol == ((TTCMove &)other).mCol) && (mRow ==
		((TTCMove&)other).mRow)));
}

TTCMove :: operator string() const{
	ostringstream format;
	(mRow == -1 && mCol == -1) ? format << "pass" << endl : format << "("
		<< mRow << "," << mCol << ") ";
	return format.str();
}