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

std::ostream& operator<<(std::ostream& os, const Coordinate &c);

class Minesweeper  {

    private:
        void populate_neighbors(const Coordinate &mine);

        void populate_board();

        bool loss(const Coordinate &click);

        bool win();

        void uncover(const Coordinate &click);

        void game_over(const bool loss);

        void uncover_safe(const Coordinate &click);

        bool finished;
        int rows;
        int cols;
        int total_spots;
        int uncovered_ct;

        std::vector<std::vector<int> > board; // -1 is a mine, 1-8 are useful
        std::vector<std::vector<bool> > state; // true - uncovered
        
        std::vector<Coordinate> mines;

    public:

        Minesweeper(int r, int c, std::vector<Coordinate> &mines_in);

        void print_board_debug();

        void print_board();

        void play(const Coordinate &click);
};
#endif
