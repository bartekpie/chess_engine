#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include <chrono>
#include <bit>
#include"types.h"
#include"ChessState.h" 
extern ChessState real, simulation;

extern std::string input;

extern const U64 notAFile ;
extern const U64 notABFile ;
extern const U64 notHFile ;
extern const U64 notGHFile;
 
extern char board[64];//visualtization
 
extern U64 NE[64];
extern U64 SE[64];
extern U64 NW[64];
extern U64 SW[64];

extern U64 North[64];
extern U64 West[64];
extern U64 South[64];
extern U64 East[64];
 
extern U64 Knights[64];

extern Move moves[256];
extern int count ;


