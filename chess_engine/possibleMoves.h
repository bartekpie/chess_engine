#pragma once
#include"types.h"
#include"zmienne.h"
#include"bitboard.h"

U64 column(int a);

U64 row(int a);

Move code_move(int from, int to);

void encode(U64 a, int from);



U64 knightMoves(int square);

void generate_knight_table(U64(&Knights)[64]);

void generate_rook_tables(U64(&N_)[64], U64(&S_)[64], U64(&E_)[64], U64(&W_)[64]);

void generate_bishop_tables(U64(&NE_)[64], U64(&NW_)[64], U64(&SE_)[64], U64(&SW_)[64]);

void calculate_Pawn_Moves(ChessState& state);

U64 calculate_bishop_moves(Square square, ChessState& state);

U64 calculate_rook_moves(Square square, ChessState& state);

U64 calculate_queen_moves(Square sq, ChessState& state);

U64 calculate_Knight_moves(int a, ChessState& state);

void generate_all_moves(ChessState& state);

void beginner_memory_calculation();
