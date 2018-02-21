#ifndef BOARD_H
#define BOARD_H
#include <string>
#include <iostream>
#include <fstream>
#include <cassert>
#include <sstream>


class Board {
public:
	static const int SIZE = 3;
	int board[SIZE][SIZE];  // Values of board
	Board(const Board & b);  //Create board from another board
	std::string move(int m);  //m is which move.  Returns string describing move
	void makeBoard(int jumbleCt = 0);  //Starting from a perfect board, do jumbleCt moves to alter it
	std::string toString() const;  //return a string which represents the contents of the board
	bool operator==(Board &b);   //Return true if two boards are equal
	Board(){ makeBoard(); };
	void rotateEast(int row);
	void rotateWest(int row);
	void rotateNorth(int col);
	void rotateSouth(int col);
	void inputBoard(std::string fn);
	void jumble(int ct);  //Do jumble moves to alter board
};
#endif