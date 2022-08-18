#include <string>
#include <vector>
#include "solver.h"

namespace sudoku {

Grid Solver::Solve(Grid grid) {
  // Make as many forced choices as possible.
  bool forced_choice_made;
  vector<vector<int>> choices;

  do {
    forced_choice_made = false;
    choices = grid.GenerateChoices();

    for (size_t i = 0; i < Grid::kSize; ++i) {
      if (choices[i].size() == 1) {
        forced_choice_made = true;
        grid.SetCell(i, choices[i][0]);
        break;
      }
    }
  } while (forced_choice_made);

  if (grid.IsComplete()) {
    return grid;
  }

  // Find the cell with the fewest possibilities.
  size_t min = 9,
    min_cell = 0;

  for (size_t i = 0; i < Grid::kSize; ++i) {
    if (!grid.IsCellEmpty(i)) {
      continue;
    }

    size_t size = choices[i].size();

    if (size == 0) {
      throw Unsolvable();
    }

    if (size < min) {
      min = size;
      min_cell = i;
    }
  }

  // Search the sub-tree of possibilities.
  for (const auto &digit : choices[min_cell]) {
    grid.SetCell(min_cell, digit);

    try {
      return Solve(grid);
    } catch (const Unsolvable &) {
      grid.ClearCell(min_cell);
    }
  }

  throw Unsolvable();
}

}  // namespace sudoku
