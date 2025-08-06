#include "possibleMoves.h"
U64 column(int a)
{
    U64 ret = 0ULL;
    for (int i = a; i < 64; i += 8)
    {
        setBit(ret, (Square)(i));
    }
    return ret;
}
U64 row(int a)
{
    U64 ret = 0ULL;
    for (int i = a * 8; i < a * 8 + 8; i++)
    {
        setBit(ret, (Square)(i));
    }
    return ret;
}
Move code_move(int from, int to)
{
    return ((from & 0x3f) << 6) | (to & 0x3f);  //0x3f  = 0..0111111 zachowuje tylko 6 najm³oddszych bitów 
}

void encode(U64 a, int from)
{
    while (a != 0)
    {
        int to = std::countr_zero(a);
        resetBit(a, Square(to));
        moves[count++] = code_move(from, to);
    }
}


U64 knightMoves(int square) {
    U64 bitboard = 0ULL;
    U64 knight = 1ULL << square;

    U64 moves = 0ULL;
    moves |= (knight << 17) & notAFile;
    moves |= (knight << 15) & notHFile;
    moves |= (knight << 10) & notABFile;
    moves |= (knight << 6) & notGHFile;
    moves |= (knight >> 17) & notHFile;
    moves |= (knight >> 15) & notAFile;
    moves |= (knight >> 10) & notGHFile;
    moves |= (knight >> 6) & notABFile;

    return moves;
}
void generate_knight_table(U64(&Knights)[64])
{
    for (int i = 0; i < 64; i++)
    {
        Knights[i] = knightMoves(i);
    }
}

void generate_rook_tables(U64(&N_)[64], U64(&S_)[64], U64(&E_)[64], U64(&W_)[64]) {
    for (int square = 0; square < 64; ++square) {
        int rank = square / 8;
        int file = square % 8;

        U64 N = 0ULL;
        U64 S = 0ULL;
        U64 E = 0ULL;
        U64 W = 0ULL;

        // North 
        for (int r = rank + 1; r < 8; ++r)
            N |= 1ULL << (r * 8 + file);

        // South 
        for (int r = rank - 1; r >= 0; --r)
            S |= 1ULL << (r * 8 + file);

        // East 
        for (int f = file + 1; f < 8; ++f)
            E |= 1ULL << (rank * 8 + f);

        // West 
        for (int f = file - 1; f >= 0; --f)
            W |= 1ULL << (rank * 8 + f);

        N_[square] = N;
        S_[square] = S;
        E_[square] = E;
        W_[square] = W;
    }
}

 void generate_bishop_tables(U64(&NE_)[64], U64(&NW_)[64], U64(&SE_)[64], U64(&SW_)[64]) {
    for (int square = 0; square < 64; ++square) {
        int rank = square / 8;
        int file = square % 8;
        U64 NE = 0ULL;
        U64 SE = 0ULL;
        U64 NW = 0ULL;
        U64 SW = 0ULL;

        //  NE
        for (int r = rank + 1, f = file + 1; r < 8 && f < 8; ++r, ++f)
            NE |= 1ULL << (r * 8 + f);

        //  NW
        for (int r = rank + 1, f = file - 1; r < 8 && f >= 0; ++r, --f)
            NW |= 1ULL << (r * 8 + f);

        //  SE
        for (int r = rank - 1, f = file + 1; r >= 0 && f < 8; --r, ++f)
            SE |= 1ULL << (r * 8 + f);

        // SW
        for (int r = rank - 1, f = file - 1; r >= 0 && f >= 0; --r, --f)
            SW |= 1ULL << (r * 8 + f);

        NE_[square] = NE;
        NW_[square] = NW;
        SE_[square] = SE;
        SW_[square] = SW;
    }
}

void calculate_Pawn_Moves(ChessState& state)
{
    
    U64 myPieces = state.MyPieces();
    U64 opponentPieces = state.OpponentPieces();
    
    if (state.white_move)
    {
        U64 singlePush = ((state.pawns & myPieces) << 8) & state.emptySpaces;
        U64 doublePush = (singlePush << 8) & state.emptySpaces;


        while (singlePush != 0)
        {
            int to = std::countr_zero(singlePush);
            resetBit(singlePush, Square(to));
            moves[count++] = code_move(to - 8, to);

        } 
        while (doublePush != 0)
        {
            int to = std::countr_zero(doublePush);
            resetBit(doublePush, Square(to));
            moves[count++] = code_move(to - 16, to);
        }

        U64 leftPush = ((state.pawns & myPieces) << 7) & opponentPieces;
        while (leftPush != 0)
        {
            int to = std::countr_zero(leftPush);
            resetBit(leftPush, Square(to));
            moves[count++] = code_move(to + 7, to);
        }
        U64 rightPush = ((state.pawns & myPieces) << 9) & opponentPieces;
        while (rightPush != 0)
        {
            int to = std::countr_zero(rightPush);
            resetBit(rightPush, Square(to));
            moves[count++] = code_move(to + 9, to);
        }

    }
    else
    {
        std::cout << "petla czarnych";
        U64 singlePush = ((state.pawns & myPieces) >> 8) & state.emptySpaces;
        U64 doublePush = (singlePush >> 8 ) & state.emptySpaces;
        

        while (singlePush != 0)
        {
            int to =  std::countr_zero(singlePush);
            resetBit(singlePush, Square(to));
            moves[count++] = code_move(to +8 , to);
            

        }
        while (doublePush != 0)
        {
            int to = std::countr_zero(doublePush);
            resetBit(doublePush, Square(to));
            moves[count++] = code_move(to +16 , to);
        }

        U64 leftPush = ((state.pawns & myPieces) >> 9) & opponentPieces;
        while (leftPush != 0)
        {
            int to = std::countr_zero(leftPush);
            resetBit(leftPush, Square(to));
            moves[count++] = code_move(to -9, to);
        }
        U64 rightPush = ((state.pawns & myPieces) >> 7) & opponentPieces;
        while (rightPush != 0)
        {
            int to = std::countr_zero(rightPush);
            resetBit(rightPush, Square(to));
            moves[count++] = code_move(to + (7), to);
        }
    }
   

}


U64 calculate_bishop_moves(Square square, ChessState& state)
{
    U64 myPieces = state.MyPieces();
    U64 opponentPieces = state.OpponentPieces();
    // U64 occupancy = myPieces | opponentPieces;
    U64 block;
    U64 attacks = 0ULL;
    //NE
    block = (NE[square] & myPieces);
    U64 NE_elminated = ~(block)&NE[square] & (~(NE[std::countr_zero(block)]));
    block = NE[square] & opponentPieces;
    NE_elminated &= NE[square] & (~(NE[std::countr_zero(block)]));
    //NW 
    block = (NW[square] & myPieces);
    U64 NW_elminated = ~(block)&NW[square] & (~(NW[std::countr_zero(block)]));
    block = NW[square] & opponentPieces;
    NW_elminated &= NW[square] & (~(NW[std::countr_zero(block)]));
    //SE
    block = (SE[square] & myPieces);
    U64 SE_elminated = ~(block)&SE[square] & (~(SE[63 - std::countl_zero(block)]));
    block = SE[square] & opponentPieces;
    SE_elminated &= SE[square] & (~(SE[63 - std::countl_zero(block)]));
    //SW
    block = (SW[square] & myPieces);
    U64 SW_elminated = ~(block)&SW[square] & (~(SW[63 - std::countl_zero(block)]));
    block = SW[square] & opponentPieces;
    SW_elminated &= SW[square] & (~(SW[63 - std::countl_zero(block)]));
    return SW_elminated | SE_elminated | NE_elminated | NW_elminated;
    // 
}
U64 calculate_rook_moves(Square square, ChessState& state)
{
    U64 myPieces = state.MyPieces();
    U64 opponentPieces = state.OpponentPieces();

    U64 attacks = 0ULL;
    U64 block;

    // NORTH
    block = North[square] & myPieces;
    U64 N_eliminated = ~(block)&North[square];
    if (block)
        N_eliminated &= ~(North[std::countr_zero(block)]);

    block = North[square] & opponentPieces;
    if (block)
        N_eliminated &= ~(North[std::countr_zero(block)]);

    // SOUTH
    block = South[square] & myPieces;
    U64 S_eliminated = ~(block)&South[square];
    if (block)
        S_eliminated &= ~(South[63 - std::countl_zero(block)]);

    block = South[square] & opponentPieces;
    if (block)
        S_eliminated &= ~(South[63 - std::countl_zero(block)]);

    // EAST
    block = East[square] & myPieces;
    U64 E_eliminated = ~(block)&East[square];
    if (block)
        E_eliminated &= ~(East[std::countr_zero(block)]);

    block = East[square] & opponentPieces;
    if (block)
        E_eliminated &= ~(East[std::countr_zero(block)]);

    // WEST
    block = West[square] & myPieces;
    U64 W_eliminated = ~(block)&West[square];
    if (block)
        W_eliminated &= ~(West[63 - std::countl_zero(block)]);

    block = West[square] & opponentPieces;
    if (block)
        W_eliminated &= ~(West[63 - std::countl_zero(block)]);

    return N_eliminated | S_eliminated | E_eliminated | W_eliminated;
}
U64 calculate_queen_moves(Square sq, ChessState& state)
{
    return calculate_rook_moves(sq, state) | calculate_bishop_moves(sq, state);
}
U64 calculate_Knight_moves(int a, ChessState& state)
{
    U64 myPieces = state.MyPieces();
    U64 opponentPieces = state.OpponentPieces();
    return Knights[a] & ~(myPieces);
}
void generate_all_moves(ChessState& state)
{
    count = 0;
    U64 myPieces = state.MyPieces();
    U64 opponentPieces = state.OpponentPieces();
    U64 MyKnights = myPieces & state.knigts;
    while (MyKnights != 0)
    {
        int from = std::countr_zero(MyKnights);
        resetBit(MyKnights, Square(from));
        encode(calculate_Knight_moves(Square(from), state), from);
    }
    U64 MyBishops = myPieces & state.bishops;
    while (MyBishops != 0)
    {
        int from = std::countr_zero(MyBishops);
        resetBit(MyBishops, Square(from));
        encode(calculate_bishop_moves(Square(from), state), from);
    }

    U64 MyRooks = myPieces & state.knigts;
    while (MyRooks != 0)
    {
        int from = std::countr_zero(MyRooks);
        resetBit(MyRooks, Square(from));
        encode(calculate_rook_moves(Square(from), state), from);
    }
    U64 MyQueens = myPieces & state.queens;
    while (MyQueens != 0)
    {
        int from = std::countr_zero(MyQueens);
        resetBit(MyQueens, Square(from));
        encode(calculate_queen_moves(Square(from), state), from);
    }

    calculate_Pawn_Moves(state);
     
}

void beginner_memory_calculation()
{
    generate_knight_table(Knights);
    generate_bishop_tables(NE, NW, SE, SW);
    generate_rook_tables(North, South, West, East);
    real.pawns = (row(6) | row(1));
    real.rooks = (row(7) | row(0)) & (column(0) | column(7));
    real.knigts = (row(7) | row(0)) & (column(1) | column(6));
    real.bishops = (row(7) | row(0)) & (column(2) | column(5));
    real.queens = (row(7) | row(0)) & column(3);
    real.kings = (row(7) | row(0)) & column(4);
    real.blackPieces = row(7) | row(6);
    real.whitePieces = row(1) | row(0);
    real.emptySpaces = ~(real.whitePieces & real.blackPieces);
    real.white_move = 1;
}

