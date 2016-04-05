#ifndef __TTCMOVE_H
#define __TTCMOVE_H
#include "GameMove.h"
#include <string>
#include <vector>
#include <iostream>

class TTCMove : public GameMove {
private:

	friend class TTCBoard;
   int mRow, mCol;

   TTCMove();

   TTCMove(int row, int col);
   
   static int mOutstanding;


public:

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
   }
   virtual ~TTCMove() { }

   TTCMove(const TTCMove &);
   TTCMove& operator=(const TTCMove &rhs);

	virtual GameMove& operator=(const std::string &);

   virtual bool Equals(const GameMove &other) const;
  
	operator std::string() const;

	inline bool IsPass() const { return mRow == -1 && mCol == -1;}

};

//int OthelloMove::mOutstanding = 0;
#endif