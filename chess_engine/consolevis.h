#pragma once
#include<iostream>
#include"types.h"
#include"ChessState.h"
#include "possibleMoves.h"
#include"zmienne.h"

int square_from_string(std::string str);

Move parse_move(std::string input);

void handle_move_input(std::string input);

void setLetter(U64 wzor, char symbol);

void print_board(ChessState state);
