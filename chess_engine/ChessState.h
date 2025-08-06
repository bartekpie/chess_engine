#pragma once
#include"types.h"
#include"bitboard.h"
struct ChessState {
	U64 blackPieces;
	U64 whitePieces;
	U64 emptySpaces;
	U64 pawns;
	U64 knigts;
	U64 bishops;
	U64 rooks;
	U64 queens;
	U64 kings;
	bool white_move;
	U64 MyPieces();
	
	U64 OpponentPieces();
	
	void Simulate_Move(Move move);
};

