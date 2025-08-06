#include "ChessState.h"

U64 ChessState::MyPieces()
{
	if (white_move)
		return whitePieces;
	else {
		return blackPieces;
	}
}

U64 ChessState::OpponentPieces()
{
	if (white_move == 0)
		return whitePieces;
	else {
		return blackPieces;
	}
}

void ChessState::Simulate_Move(Move move)
{
	Move from = (move >> 6) & 0x3F;
	Move to = move & 0x3F;
	emptySpaces |= 1ULL<< from;
	emptySpaces &= ~(1ULL << to);
	blackPieces, whitePieces, pawns, knigts, bishops, rooks, queens, kings &= ~(1ULL<<to);
	if (getBit(whitePieces, Square(from)))
	{
		resetBit(whitePieces, Square(from));
		setBit(whitePieces, Square(to));
		white_move = 0;
	}
	else {
		resetBit(blackPieces, Square(from));
		setBit(blackPieces, Square(to));
		white_move = 1;
	}
	if (getBit(knigts, Square(from)))
	{
		resetBit(knigts, Square(from));
		setBit(knigts, Square(to));
	}
	if (getBit(pawns, Square(from)))
	{
		resetBit(pawns, Square(from));
		setBit(pawns, Square(to));
	}
	if (getBit(bishops, Square(from)))
	{
		resetBit(bishops, Square(from));
		setBit(bishops, Square(to));
	}
	if (getBit(rooks, Square(from)))
	{
		resetBit(rooks, Square(from));
		setBit(rooks, Square(to));
	}
	if (getBit(queens, Square(from)))
	{
		resetBit(queens, Square(from));
		setBit(queens, Square(to));
	}
	
}
