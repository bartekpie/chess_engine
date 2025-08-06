////This is not typical chess game. This project is basis for chess engine.
////From this prject you can develop your own algorithms using structeres 
//// and functions that generate moves using bitboard and bitoperations. 



#include"possibleMoves.h"
#include "consolevis.h"



int main() {
    beginner_memory_calculation(); 
    
    

    while (true) {
        print_board(real);
        std::cout << (real.white_move ? "Bialy" : "Czarny") << " ruch :  ";
        std::cin >> input;

        if (input == "end")
            break;

        generate_all_moves(real);
        handle_move_input(input);
    }

    std::cout << "Koniec gry." << std::endl;
    return 0;
}