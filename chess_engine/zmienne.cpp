#include"zmienne.h"

ChessState real,simulation;

char board[64];

std::string input;

const U64 notAFile = 0xfefefefefefefefeULL;
const U64 notABFile = 0xfcfcfcfcfcfcfcfcULL;
const U64 notHFile = 0x7f7f7f7f7f7f7f7fULL;
const U64 notGHFile = 0x3f3f3f3f3f3f3f3fULL;



U64 NE[64];
U64 SE[64];
U64 NW[64];
U64 SW[64];

U64 North[64];
U64 West[64];
U64 South[64];
U64 East[64];

U64 Knights[64];

Move moves[256];
int count = 0;
 