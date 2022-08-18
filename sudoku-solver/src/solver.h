#ifndef SRC_SOLVER_H_
#define SRC_SOLVER_H_

#include "grid.h"

namespace sudoku {

class Solver {
 public:
  static Grid Solve(Grid) noexcept(false);
};

}  // namespace sudoku

#endif  // SRC_SOLVER_H_
