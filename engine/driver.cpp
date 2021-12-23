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
    game.print_board_debug();
    game.play(Coordinate(0,0));
    game.print_board();
    game.play(Coordinate(0,3));
    game.print_board();
    game.play(Coordinate(1,0));
    game.print_board();
}
