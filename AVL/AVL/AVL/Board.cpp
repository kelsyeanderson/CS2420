#include "Board.h"

void Board::inputBoard(std::string fn)
{
	std::ifstream inf;
	inf.open(fn.c_str());
	assert(inf.good());
	for (int i= 0; i < SIZE; i++)
		for (int j=0; j<SIZE;j++)
		   inf >> board[i][j];
}

// Create a printable representation of the Board class
// The stringstream allows you to use the power of output commands in creating a string
std::string Board::toString() const {
	std::stringstream ss;
	for (int i=0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
			ss << board[i][j] << " ";
		ss << std::endl;
	}
	return ss.str();
};

// return true if board is identical to b
bool Board::operator==(Board &b) {
	
	for (int i=0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
			if (board[i][j] != b.board[i][j]) return false;
	return true;
}

//Create a board by performing legal moves on a board
//jumbleCt indicates the number of moves that may be required
//if jumbleCt ==0, return the winning board
void Board::makeBoard(int jumbleCt) {
	int val=1;
	for (int i=0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
			board[i][j] = val++;
	jumble(jumbleCt);
}

//Copy constructor
Board::Board(const Board & b) {
	//cout << "Just Copied Board\n" << b.toString() << endl;
	assert(SIZE > 0);
	for (int i=0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
			board[i][j] = b.board[i][j];
}


//Rotate East using row specified
void Board::rotateEast(int row){
	if (row <0|| row >=SIZE) return;
	int wrap = board[row][SIZE-1];
	for (int i = SIZE-2; i >=0; i--)
		board[row][i+1] = board[row][i];
	board[row][0] = wrap;
}
//Rotate West using row specified
void Board::rotateWest(int row){
	if (row <0 || row >=SIZE) return;
	int wrap = board[row][0];
	for (int i = 0; i <SIZE-1; i++)
		board[row][i] = board[row][i+1];
	board[row][SIZE-1] = wrap;
}

//Rotate South using column specified
void Board::rotateSouth(int col){
	if (col <0||col >=SIZE) return;
	int wrap = board[SIZE-1][col];
	for (int i = SIZE-2; i >=0; i--)
		board[i+1][col] = board[i][col];
	board[0][col] = wrap;
}
//Rotate North using column specified
void Board::rotateNorth(int col){
	if (col <0||col >=SIZE) return;
	int wrap = board[0][col];
	for (int i = 0; i <SIZE-1; i++)
		board[i][col] = board[i+1][col];
	board[SIZE-1][col] = wrap;
}

// Randomly apply ct moves to the board
void Board::jumble(int ct) {
	for (int i=0; i < ct; i++)
		move(rand()%(SIZE*4));
}


// Make one move.  m indicates which move is wanted. Return string describing the move
std::string Board::move(int m){
	std::stringstream ss;
	ss << ":";
	int sub = m/ 4;
	switch (m%4)
	{
	case 0:  rotateNorth(sub); ss << "^" << sub; break;
	case 1:  rotateSouth(sub); ss << "v" << sub; break;
	case 2:  rotateEast(sub); ss << ">" << sub; break;
	case 3:  rotateWest(sub); ss << "<" << sub; break;
	}
	return ss.str();
}


