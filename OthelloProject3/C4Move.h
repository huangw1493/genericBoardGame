#ifndef __C4MOVE_H
#define __C4MOVE_H
#include "GameMove.h"
#include <string>
#include <vector>
#include <iostream>
/*
An C4Move encapsulates a single potential move on an C4Board. It
is represented internally by a row and column, both 0-based.
*/
class C4Move : public GameMove {
private:
	// OthelloBoard is a friend so it can access mRow and mCol.
	friend class C4Board;
	int mRow, mCol;

	// KEEP THESE CONSTRUCTORS PRIVATE.
	// Default constructor: initializes this move as a PASS.
	C4Move();
	/*
	2-parameter constructor: initializes this move with the given
	row and column.
	*/
	C4Move(int row, int col);

	//void AddFlipSet(FlipSet set) {mFlips.push_back(set);}

	static int mOutstanding;


public:
	/*
	static void* operator new(std::size_t sz) {
	mOutstanding++;
	std::cout << "operator new: " << mOutstanding <<
	" moves outstanding" << std::endl;
	return ::operator new(sz);
	}

	static void operator delete(void* ptr, std::size_t sz) {
	mOutstanding--;
	std::cout << "operator delete: " << mOutstanding <<
	" moves oustanding" << std::endl;
	::operator delete(ptr);
	}*/
	virtual ~C4Move() { }

	C4Move(const C4Move &);
	C4Move& operator=(const C4Move &rhs);

	/*
	This assignment operator takes a string representation of an Othellomove
	and uses it to initialize the move. The string is in the format
	(r, c); OR is the string "pass". [The user will not enter (-1,-1) to pass
	anymore.]
	*/
	virtual GameMove& operator=(const std::string &);

	/*
	Compares two C4 objects for equality.
	*/
	virtual bool Equals(const GameMove &other) const;

	// Converts the C4 into a string representation, one that could be
	// used correctly with operator=(string). Returns "pass" if move is a pass.
	operator std::string() const;

	// Returns true if the move represents a Pass.
	// TO DO: fill in this method.
	inline bool IsPass() const { return mRow == -1 && mCol == -1; }
	/*
	virtual GameMove *Clone() const {
	return new OthelloMove(*this);
	}
	*/
};

//int OthelloMove::mOutstanding = 0;
#endif