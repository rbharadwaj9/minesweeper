#include <iostream>

#include "engine.h"

int main() {
    // 4x4 board
    // - - - -
    // x - - -
    // - - x -
    // - - - -
    
    std::vector<Coordinate> mines = {Coordinate(1, 0), Coordinate(2, 2)};
    Minesweeper game = Minesweeper(4, 4, mines);
    std::cout << "Before Play\n";
    game.print_board_debug(std::cout);
    game.play_move(Coordinate(0,0));
    game.print_board(std::cout);
    game.play_move(Coordinate(0,3));
    game.print_board(std::cout);
    game.play_move(Coordinate(2,1));
    game.print_board(std::cout);
    game.play_move(Coordinate(3,0));
    game.print_board(std::cout);
    game.play_move(Coordinate(2,3));
    game.print_board(std::cout);
    game.play_move(Coordinate(3,3));
    game.print_board(std::cout);
    game.play_move(Coordinate(3,2));
}
