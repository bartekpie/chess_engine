#include "consolevis.h"

int square_from_string(std::string str) {
    if (str.length() != 2) return -1;
    int file = str[0] - 'a';
    int rank = str[1] - '1';
    if (file < 0 || file > 7 || rank < 0 || rank > 7) return -1;
    return rank * 8 + file;
}



Move parse_move(std::string input) {
    if (input.length() != 4) return 0;
    int from = square_from_string(input.substr(0, 2));
    int to = square_from_string(input.substr(2, 2));
    if (from == -1 || to == -1) return 0;
    return code_move(from, to);
}

void handle_move_input(std::string input) {


    Move userMove = parse_move(input);

    bool found = false;

    for (int i = 0; i < count; ++i) {
        if (moves[i] == userMove) {
            real.Simulate_Move(moves[i]);
            found = true;
            std::cout << moves[i] << std::endl;;
            break;
        }
    }

    if (!found) {
        std::cout << "Nielegalny ruch!" << std::endl;
    }
}
void setLetter(U64 wzor, char symbol)
{
    while (wzor != 0)
    {
        int a = std::countr_zero(wzor);
        board[a] = symbol;
        resetBit(wzor, Square(a));
    }
}
void print_board(ChessState state) {
    char EMPTY = '.';
    std::fill(board, board + 64, EMPTY);

    U64 whitePawns = real.whitePieces & real.pawns;
    setLetter(whitePawns, 'p');

    U64 blackPawns = real.blackPieces & real.pawns;
    setLetter(blackPawns, 'P');
    U64 whiteKnigts = real.whitePieces & real.knigts;
    setLetter(whiteKnigts, 'n');

    U64 blackKnigts = real.blackPieces & real.knigts;
    setLetter(blackKnigts, 'N');

    U64 whiteRooks = real.whitePieces & real.rooks;
    setLetter(whiteRooks, 'r');

    U64 blackRooks = real.blackPieces & real.rooks;
    setLetter(blackRooks, 'R');

    U64 whiteBishops = real.whitePieces & real.bishops;
    setLetter(whiteBishops, 'b');

    U64 blackBishops = real.blackPieces & real.bishops;
    setLetter(blackBishops, 'B');

    U64 blackQueen = real.blackPieces & real.queens;
    setLetter(blackQueen, 'Q');

    U64 whiteQueen = real.whitePieces & real.queens;
    setLetter(whiteQueen, 'q');

    U64 blackKing = real.blackPieces & real.kings;
    setLetter(blackKing, 'K');

    U64 whiteKing = real.whitePieces & real.kings;
    setLetter(whiteKing, 'k');






    for (int rank = 7; rank >= 0; --rank) {
        std::cout << rank + 1 << " | ";
        for (int file = 0; file < 8; ++file) {
            Square sq = (Square)(rank * 8 + file);
            std::cout << board[sq] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "   -----------------" << std::endl;
    std::cout << "    A B C D E F G H" << std::endl << std::endl;
}