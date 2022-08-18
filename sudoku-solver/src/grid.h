#ifndef SRC_GRID_H_
#define SRC_GRID_H_

#include <string>
#include <vector>

using std::string;
using std::vector;

namespace sudoku {

class Grid {
 public:
  void SetCell(int idx, int digit) {
    cells_[idx] = digit;
  }

  void ClearCell(int idx) {
    SetCell(idx, kEmpty);
  }

  int GetCell(int idx) const {
    return cells_[idx];
  }

  bool IsCellEmpty(int idx) const {
    return GetCell(idx) == kEmpty;
  }

  bool IsComplete() const {
    return std::none_of(cells_.begin(), cells_.end(), [](int digit) { return digit == kEmpty; });
  }

  string ToString() const {
    string cells = "";

    for (const int &digit : cells_) {
      cells += std::to_string(digit);
    }

    return cells;
  }

  vector<vector<int>> GenerateChoices();

  bool BoxHasDigit(int, int);
  bool RowHasDigit(int, int);
  bool ColHasDigit(int, int);

  static Grid FromString(const string&);

  static const int kSize = 81;

 private:
  vector<int> cells_;

  Grid(const vector<int> &cells): cells_(cells) {
    Validate();
  }

  void Validate() noexcept(false);

  static const int kEmpty = 0;
};

struct Unsolvable : public std::runtime_error {
  Unsolvable() : std::runtime_error("Grid is not solvable") {}
};

}  // namespace sudoku

#endif  // SRC_GRID_H_
