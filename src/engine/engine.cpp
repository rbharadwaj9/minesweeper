#include <sstream>
#include <random>

#include "engine.h"

Minesweeper::Minesweeper(int r, int c, int num_mines) : Minesweeper(r, c, num_mines, 0)
{}

Minesweeper::Minesweeper(int r, int c, int num_mines, int seed) :
  finished(false), rows(r), cols(c), total_spots(r*c), uncovered_ct(0),
  board(r, std::vector<int>(c, 0)), state(r, std::vector<bool>(c, false)),
  mines({}) {
    generate_mines(num_mines, seed);
    populate_board();
  }


Minesweeper::Minesweeper(int r, int c, std::unordered_set<Coordinate, CoordinateHash> &mines_in) :
  finished(false), rows(r), cols(c), total_spots(r*c), uncovered_ct(0),
  board(r, std::vector<int>(c, 0)), state(r, std::vector<bool>(c, false)),
  mines(mines_in) {
    populate_board();
}

void Minesweeper::generate_mines(int num_mines, int seed) {
  std::random_device r_dev;
  std::mt19937 rng_r(r_dev());
  std::mt19937 rng_c(r_dev());
  if (seed) {
    std::cout << "Setting Seed" << std::endl;
    rng_r.seed(seed);
    rng_c.seed(seed);
  }
  std::uniform_int_distribution<int> int_dist_r(0, rows-1);
  std::uniform_int_distribution<int> int_dist_c(0, cols-1);
  while (static_cast<int>(mines.size()) != num_mines) {
    int row = int_dist_r(rng_r);
    int col = int_dist_c(rng_c);
    Coordinate c(row, col);
    mines.insert(c);
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

      board[next_row][next_col] += board[next_row][next_col] != -1 ? 1 : 0;
    }
  }
}

void Minesweeper::uncover(const Coordinate &click) {
  state[click.r][click.c] = true;
  ++uncovered_ct;
}

void Minesweeper::uncover_safe(const Coordinate &click) {
  if (state[click.r][click.c])
    return;
  uncover(click);

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

bool Minesweeper::loss(const Coordinate &click) const {
  if (board[click.r][click.c] == -1)
    return true;
  return false;
}

bool Minesweeper::win() const {
  return uncovered_ct + static_cast<int>(mines.size()) == total_spots;
}

void Minesweeper::execute_game_over(const bool loss) {
  if (loss)
    std::cout << "You lost\n";
  else
    std::cout << "You won!\n";
  finished = true;
}

bool Minesweeper::valid_move(const Coordinate &click) const {
  if (finished) {
    std::cout << "Game Finished. Please Restart\n";
    return false;
  }

  return !state[click.r][click.c];
}

void Minesweeper::execute_valid_move(const Coordinate &click) {
  // uncover current coordinate - loss or not
  // uncover rest of the coordinate
  int occupied_by = board[click.r][click.c];
  if (occupied_by != 0) {
    uncover(click);
    return;
  }
  uncover_safe(click);
}

bool Minesweeper::play_move(const Coordinate &click) {
  std::cout << "Playing: " << click << std::endl;

  if (!valid_move(click))
    return false;

  // Check Loss
  if (loss(click)) {
    uncover(click);
    execute_game_over(true);
    return true;
  }

  execute_valid_move(click);

  // Check Win
  if (win()) {
    execute_game_over(false);
  }
  return true;
}

bool Minesweeper::is_game_over() {
  return finished;
}

std::string Minesweeper::get_mines() const {
  std::ostringstream out;
  auto st = mines.begin();
  while (st != mines.end()) {
    out << *st << ", ";
    ++st;
  }
  return out.str();
}

std::string Minesweeper::get_board_debug() const {
  std::ostringstream out;
  print_board_debug(out);
  return out.str();
}

std::string Minesweeper::get_user_board() const {
  std::ostringstream out;
  print_user_board(out);
  return out.str();
}

std::ostream& Minesweeper::print_board_debug(std::ostream &os) const {
  for (const auto &b_r : board) {
    for (const auto b_c : b_r) {
      os << b_c << " ";
    }
    os << "\n";
  }
  return os;
}

std::ostream& Minesweeper::print_user_board(std::ostream &os) const {
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      if (state[i][j]) {
        os << board[i][j] << " ";
      } else {
        os << "-" << " ";
      }
    }
    os << "\n";
  }
  return os;
}

std::ostream& operator<<(std::ostream& os, const Minesweeper &m) {
  m.print_user_board(os);
  return os;
}
