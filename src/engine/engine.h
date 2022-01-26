#ifndef ENGINE_H
#define ENGINE_H

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

struct Coordinate {
  int r;
  int c;

  Coordinate(int r_in, int c_in);

  friend std::ostream& operator<<(std::ostream& os, const Coordinate &c);
};

class Minesweeper  {

  public:

    // Initialize num mines randomly in given board size
    Minesweeper(int r, int c, int num_mines);

    /* // Initialize mines at given coordinates */
    Minesweeper(int r, int c, std::vector<Coordinate> &mines_in);

    bool play_move(const Coordinate &click);

    bool is_game_over();

    std::string get_board_debug() const;

    std::string get_user_board() const;

    std::ostream& print_board_debug(std::ostream &os) const;

    std::ostream& print_user_board(std::ostream &os) const;

  private:
    bool finished;
    int rows;
    int cols;
    int total_spots;
    int uncovered_ct;

    std::vector<std::vector<int> > board; // -1 is a mine, 1-8 are useful
    std::vector<std::vector<bool> > state; // true - uncovered

    std::vector<Coordinate> mines;

  private:
    void populate_neighbors(const Coordinate &mine);

    void populate_board();

    void uncover(const Coordinate &click);

    void uncover_safe(const Coordinate &click);

    bool loss(const Coordinate &click) const;

    bool win() const;

    void execute_game_over(const bool loss);

    bool valid_move(const Coordinate &click) const;

    void execute_valid_move(const Coordinate &click);

};

std::ostream& operator<<(std::ostream& os, const Coordinate &c);

std::ostream& operator<<(std::ostream& os, const Minesweeper &m);

#endif
