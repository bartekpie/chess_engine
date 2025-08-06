#pragma once
#include"types.h"
#include<iostream>
#include <bit>
extern enum Square;
void setBit(U64& bitboard, Square bit);

void resetBit(U64& bitboard, Square bit);

bool getBit(U64 bitboard, Square sq);

int howmanyBits(U64 bitboard);

void printBitboard(U64 bitboard);
