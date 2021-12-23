#include "engine.h"

Coordinate::Coordinate(int r_in, int c_in) : r(r_in), c(c_in) {}

std::ostream& operator<<(std::ostream& os, const Coordinate &c) {
    os << "(" << c.r << "," << c.c << ")";
    return os;
}

Minesweeper::Minesweeper(int r, int c, std::vector<Coordinate> &mines_in) : rows(r), cols(c), board(r, std::vector<int>(c, 0)), state(r, std::vector<bool>(c, false)), mines(mines_in) {
    populate_board(); 
    print_board();
}

void Minesweeper::populate_neighbors(const Coordinate &mine) {
    for (int i = -1; i < 2; ++i) {
        for (int j = -1; j < 2; ++j) {
            // Bomb
            if (i == 0 && j == 0)
                continue;
            int next_row = mine.r - i;
            int next_col = mine.c - j;
            if (next_row < 0 || next_row >= rows || next_col < 0 || next_col >= cols) {
                continue;
            }

            board[next_row][next_col] += 1;
        }
    }
}

void Minesweeper::populate_board() {
    for (const auto &mine : mines) {

        assert(mine.r >= 0 && mine.r < rows);
        assert(mine.c >= 0 && mine.c < cols);
        board[mine.r][mine.c] = -1;

        populate_neighbors(mine);
    }
}

void Minesweeper::print_board_debug() {
    for (const auto &b_r : board) {
        for (const auto b_c : b_r) {
            std::cout << b_c << ", ";
        }
        std::cout << "\n";
    }
}

void Minesweeper::print_board() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (state[i][j]) {
                std::cout << board[i][j] << " ";
            } else {
                std::cout << "-" << " ";
            }
        }
        std::cout << "\n";
    }
}

bool Minesweeper::loss(const Coordinate &click) {
    if (board[click.r][click.c] == -1)
        return true;
    return false;
}

void Minesweeper::uncover(const Coordinate &click) {
    state[click.r][click.c] = true;
}

void Minesweeper::game_over(const bool loss) {
    if (loss)
        std::cout << "You lost\n";
    else
        std::cout << "You won\n";
    finished = true;
    print_board();
}

void Minesweeper::uncover_safe(const Coordinate &click) {
    if (state[click.r][click.c])
        return;
    state[click.r][click.c] = true;

    if (board[click.r][click.c] != 0)
        return;

    for (int i = -1; i < 2; ++i) {
        for (int j = -1; j < 2; ++j) {
            // Bomb
            if (i == 0 && j == 0)
                continue;
            int next_row = click.r - i;
            int next_col = click.c - j;
            if (next_row < 0 || next_row >= rows || next_col < 0 || next_col >= cols) {
                continue;
            }
            uncover_safe(Coordinate(next_row, next_col));
        }
    }
}

void Minesweeper::play(const Coordinate &click) {
    if (finished) {
        std::cout << "Game Finished. Please Restart\n";
        return;
    }

    std::cout << "Playing: " << click << std::endl;
    // Check if we're uncovering a mine.
    if (loss(click)) {
        uncover(click);
        game_over(true);
        return;
    }
    
    // uncover current coordinate - loss or not
    // uncover rest of the coordinate
    int occupied_by = board[click.r][click.c];  
    if (occupied_by != 0) {
        uncover(click);
        return;
    } 
    uncover_safe(click);
    if (win()) {
        game_over(false);
    }
}
