#include <iostream>
#include <unordered_set>

#include "engine.h"

int main() {
  // 4x4 board
  // - - - -
  // x - - -
  // - - x -
  // - - - -

  /* std::unordered_set<Coordinate, CoordinateHash> mines = {Coordinate(3, 8), Coordinate(4, 8), Coordinate(0, 2), Coordinate(7, 9)}; */
  /* Minesweeper game = Minesweeper(10, 10, mines); */
  std::unordered_set<Coordinate, CoordinateHash> mines = {Coordinate(1, 2), Coordinate(2, 2)};
  Minesweeper game = Minesweeper(4, 4, mines);
  std::cout << "Before Play\n";
  game.print_board_debug(std::cout);
  /* game.play_move(Coordinate(0,0)); */
  /* game.print_user_board(std::cout); */
  /* game.play_move(Coordinate(0,3)); */
  /* game.print_user_board(std::cout); */
  /* game.play_move(Coordinate(2,1)); */
  /* game.print_user_board(std::cout); */
  /* game.play_move(Coordinate(3,0)); */
  /* game.print_user_board(std::cout); */
  /* game.play_move(Coordinate(2,3)); */
  /* game.print_user_board(std::cout); */
  /* game.play_move(Coordinate(3,3)); */
  /* game.print_user_board(std::cout); */
  /* game.play_move(Coordinate(3,2)); */
}
