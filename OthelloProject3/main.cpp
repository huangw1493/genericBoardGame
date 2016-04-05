#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "GameMove.h"
#include "GameBoard.h"
#include "GameView.h"
#include "OthelloMove.h"
#include "OthelloBoard.h"
#include "OthelloView.h"
#include "TTCMove.h"
#include "TTCBoard.h"
#include "TTCView.h"
#include "C4Board.h"
#include "C4Move.h"
#include "C4View.h"

using namespace std;

/*This program was created to test generic types and demonstrate some of their capabilities 
by implementing board games. We've implemented Tic Tac Toe and Othello here, however any board game is doable.
This particualr file was created using an older version of VS and doesn't compile in VS 2015
*/
int main(int argc, char* argv[]) {
	// Initialization
	using namespace std;
	while(true){
		string userInput;
		GameBoard *board;
		GameView *v;
		vector<GameMove *> possMoves;

		cout << "What game would you like to play?" << endl;
		cout << "1. Othello. 2. Tic Tac Toe. 3. Connect 4." << endl;
		getline(cin, userInput);

		if(userInput.find("1") == 0) {
			board = new OthelloBoard();
			v = new OthelloView(board);

		}
		else if(userInput.find("2") == 0){
			board = new TTCBoard();
			v = new TTCView(board);
		}
		else{
			board = new C4Board();
			v = new C4View(board);
		}

		do{
			//Prints out board
			cout << *v << endl;
			cout << "move (r,c)" << endl << "undo n" << endl << "showValue" << endl
				<< "showHistory" << endl << "quit" << endl << "Player: ";
			//Gets player color and displays it
			cout << board->GetPlayerString(board->GetNextPlayer()) << endl;
			//Asks for player input
			board->GetPossibleMoves(&possMoves);
			//cout << "Poss moves is this long: "<< possMoves.size() << endl;

			//Prints out possible moves
			for(vector<GameMove *> ::iterator itr = possMoves.begin();
				itr != possMoves.end(); itr++){
				cout << (string)**itr << " ";
			}
			cout << endl;

			//Takes player input
			getline(cin, userInput);


			if(userInput.find("move") == 0) {
				bool mValid = 0;
				GameMove *ptr = (GameMove*)board->CreateMove();
				ptr -> operator=(userInput.substr(5));

				//Checks for valid move
				for(vector<GameMove*> ::iterator itr = possMoves.begin(); itr != possMoves.end(); itr++){
					(**itr == *ptr) ? mValid = 1 : 0;
				}
				if(mValid == 1)
					board->ApplyMove(ptr);
				else{
					cout << "Invalid Move" << endl;
					delete ptr;
				}
			}

			if(userInput.find("showValue") == 0){
				cout << "Board Value is : " << board->GetValue() << endl;
			}

			if(userInput.find("showHistory") == 0){

				int mFlip = board->GetNextPlayer()*-1;
				for(vector<GameMove *> ::const_iterator itr =
					board->GetMoveHistory()->begin();
					itr != board->GetMoveHistory()->end(); itr++){
					cout << board->GetPlayerString(mFlip)
						<< (string)**itr << endl;
					mFlip = -mFlip;
				}
			}

			if(userInput.find("undo") == 0){
				int tx = userInput.at(5) - '0';
				(tx > board->GetMoveCount() || tx < 0) ? tx = board->GetMoveCount()
					: 0;
				for(int i = 0; i < tx; i++){
					board->UndoLastMove();
				}
			}
			if(userInput.find("quit") == 0){
				break;
			}
			for(vector<GameMove*> ::iterator itr = possMoves.begin(); itr != possMoves.end(); itr++){
				delete *itr;
			}
			possMoves.clear();
			if(board->IsFinished()){
				if((board->GetValue()) > 0){
					cout << board->GetPlayerString(board->GetNextPlayer()*-1) 
						<< " is the winner!" << endl;
				}
				else if((board->GetValue()) < 0){
					cout << board->GetPlayerString(board->GetNextPlayer()) 
						<< " is the winner!" << endl;
				}
				else{
					cout << "Tie!" << endl;
				}
			}
		} while(!board->IsFinished());
		cout << *v << endl;
		//delete history
		//cout << "We are deleting all the moves" << endl;
		for(vector<GameMove *> ::iterator itr = possMoves.begin();
			itr != possMoves.end(); itr++){
			delete *itr;
		}
		for(vector<GameMove *> ::const_iterator itr =
	    board->GetMoveHistory()->begin();
		 itr != board->GetMoveHistory()->end(); itr++){
			delete *itr;
		}
	}
}