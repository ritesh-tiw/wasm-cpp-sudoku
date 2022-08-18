#include "grid.h"
#include<stdexcept>

namespace sudoku {

Grid Grid::FromString(const string &cells) {
  if (cells.size() != kSize) {
    throw std::invalid_argument(
      "Expected " + std::to_string(kSize) + " cells, got " + std::to_string(cells.size())
    );
  }

  vector<int> cells_v;

  for (const char &digit : cells) {
    cells_v.push_back(digit - '0');
  }

  return Grid(cells_v);
}

bool Grid::BoxHasDigit(int digit, int cell_idx) {
  static const int cell_idx_to_box_start[] = {
    0,  0,  0,  3,  3,  3,  6,  6,  6,
    0,  0,  0,  3,  3,  3,  6,  6,  6,
    0,  0,  0,  3,  3,  3,  6,  6,  6,

    27, 27, 27, 30, 30, 30, 33, 33, 33,
    27, 27, 27, 30, 30, 30, 33, 33, 33,
    27, 27, 27, 30, 30, 30, 33, 33, 33,

    54, 54, 54, 57, 57, 57, 60, 60, 60,
    54, 54, 54, 57, 57, 57, 60, 60, 60,
    54, 54, 54, 57, 57, 57, 60, 60, 60
  };

  int start = cell_idx_to_box_start[cell_idx],
    end = start + 21;

  for (int i = start; i < end; i += 9) {
    for (int j = 0; j < 3; ++j) {
      if (i + j != cell_idx && cells_[i + j] == digit) {
        return true;
      }
    }
  }

  return false;
}

bool Grid::RowHasDigit(int digit, int cell_idx) {
  int start = cell_idx - cell_idx % 9,
    end = start + 9;

  for (int i = start; i < end; ++i) {
    if (i != cell_idx && GetCell(i) == digit) {
      return true;
    }
  }

  return false;
}

bool Grid::ColHasDigit(int digit, int cell_idx) {
  int start = cell_idx % 9,
    end = start + 73;

  for (int i = start; i < end; i += 9) {
    if (i != cell_idx && GetCell(i) == digit) {
      return true;
    }
  }

  return false;
}

vector<vector<int>> Grid::GenerateChoices() {
  vector<vector<int>> choices;

  for (int cell_idx = 0; cell_idx < kSize; ++cell_idx) {
    vector<int> choices_at_idx;

    if (IsCellEmpty(cell_idx)) {
      for (int digit = 1; digit <= 9; ++digit) {
        if (
          !BoxHasDigit(digit, cell_idx) &&
          !RowHasDigit(digit, cell_idx) &&
          !ColHasDigit(digit, cell_idx)
        ) {
          choices_at_idx.push_back(digit);
        }
      }
    }

    choices.push_back(choices_at_idx);
  }

  return choices;
}

void Grid::Validate() {
  for (int cell_idx = 0; cell_idx < kSize; ++cell_idx) {
    if (IsCellEmpty(cell_idx)) {
      continue;
    }

    int digit = GetCell(cell_idx);

    if (
      BoxHasDigit(digit, cell_idx) ||
      RowHasDigit(digit, cell_idx) ||
      ColHasDigit(digit, cell_idx)
    ) {
      throw Unsolvable();
    }
  }
}

}  // namespace sudoku
