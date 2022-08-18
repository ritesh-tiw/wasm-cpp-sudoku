#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <vector>

const int UNASSIGNED = 0;

using namespace std;
class Sudoku {
private:
  int grid[9][9];
  // soln grid
  int solnGrid[9][9];
  // random number generating
  int guessNum[9];
  int gridPos[81];
  int difficultyLevel;
  bool grid_status;

public:
  Sudoku();
  // constructor
  // accepting two_arguments
  Sudoku(string, bool row_major = true);
  void fillEmptyDiagonalBox(int);
  void createSeed();
  void printGrid() const;
  bool solveGrid();
  string getGrid() const;
  void countSoln(int &number);
  void genPuzzle();
  bool verifyGridStatus() const;
  void printSVG(string);
  void calculateDifficulty();
  int branchDifficultyScore();
};

// START: Get grid as string in row major order
string Sudoku::getGrid() const {
  string s = "";
  for (int row_num = 0; row_num < 9; ++row_num) {
    for (int col_num = 0; col_num < 9; ++col_num) {
      s = s + to_string(grid[row_num][col_num]);
    }
  }
  // for (const auto &row : grid)
  // {
  //   for (const auto &elem : row)
  //   {
  //     s = s + to_string(elem);
  //   }
  // }

  return s;
}
// END: Get grid as string in row major order

// START: Generate random number
int genRandNum(const int &maxLimit) {
  std::random_device
      rd; // Will be used to obtain a seed for the random number engine
  std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
  std::uniform_int_distribution<> distrib(0, maxLimit - 1);
  return distrib(gen);
}
// END: Generate random number

// START: Helper functions for solving grid
bool FindUnassignedLocation(const int grid[9][9], int &row, int &col) {
  for (row = 0; row < 9; row++) {
    for (col = 0; col < 9; col++) {
      if (grid[row][col] == UNASSIGNED)
        return true;
    }
  }

  return false;
}

bool UsedInRow(const int grid[9][9], int row, int num) {
  for (int col = 0; col < 9; col++) {
    if (grid[row][col] == num)
      return true;
  }
  // for (const auto &i : grid[row])
  // {
  //   if (i == num)
  //   {
  //     return true;
  //   }
  // }
  return false;
}

bool UsedInCol(const int grid[9][9], int col, int num) {
  for (int row = 0; row < 9; row++) {
    if (grid[row][col] == num)
      return true;
  }

  return false;
}

bool UsedInBox(const int grid[9][9], const int &boxStartRow,
               const int &boxStartCol, const int &num) {
  for (int row = 0; row < 3; row++) {
    for (int col = 0; col < 3; col++) {
      if (grid[row + boxStartRow][col + boxStartCol] == num)
        return true;
    }
  }

  return false;
}

bool isSafe(const int grid[9][9], int row, int col, int num) {
  return !UsedInRow(grid, row, num) && !UsedInCol(grid, col, num) &&
         !UsedInBox(grid, row - row % 3, col - col % 3, num);
}

// validation end here

// START: Create seed grid
void Sudoku::fillEmptyDiagonalBox(int idx) {
  int start = idx * 3;
  std::random_shuffle(this->guessNum, (this->guessNum) + 9, genRandNum);
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      this->grid[start + i][start + j] = guessNum[i * 3 + j];
    }
  }
}

void Sudoku::createSeed() {
  /* Fill diagonal boxes to form:
      x | . | .
      . | x | .
      . | . | x
  */
  this->fillEmptyDiagonalBox(0);
  this->fillEmptyDiagonalBox(1);
  this->fillEmptyDiagonalBox(2);

  /* Fill the remaining blocks:
      x | x | x
      x | x | x
      x | x | x
  */
  this->solveGrid(); // TODO: not truly random, but still good enough because we
                     // generate random diagonals.

  // Saving the solution grid
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      this->solnGrid[i][j] = this->grid[i][j];
    }
  }
}
Sudoku::Sudoku() {

  // initialize difficulty level
  this->difficultyLevel = 0;

  // Randomly shuffling the array of removing grid positions
  for (int i = 0; i < 9 * 9; i++) {
    this->gridPos[i] = i;
  }
  int k = 0;
  // for(auto& i:this->gridPos)
  // {
  //   i=k;
  //   ++k;
  // }

  random_shuffle(this->gridPos, (this->gridPos) + 81, genRandNum);

  // Randomly shuffling the guessing number array
  for (int i = 0; i < 9; i++) {
    this->guessNum[i] = i + 1;
  }

  random_shuffle(this->guessNum, (this->guessNum) + 9, genRandNum);

  // Initialising the grid
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      this->grid[i][j] = 0;
    }
  }

  grid_status = true;
}
// END: Initialising

// START: Custom Initialising with grid passed as argument
Sudoku::Sudoku(string grid_str, bool row_major) {
  if (grid_str.length() != 81) {
    grid_status = false;
    return;
  }
  // in case grid is not of 9*9 size we return
  //  First pass: Check if all cells are valid
  for (int i = 0; i < 81; ++i) {
    // convert to int
    int curr_num = grid_str[i] - '0';
    // UNASSIGNED=0, so if curr_num is 0, then it is unassigned
    // check boundRY
    if (!((curr_num == UNASSIGNED) || (curr_num > 0 && curr_num < 10))) {
      grid_status = false;
      return;
    }

    if (row_major)
      grid[i / 9][i % 9] = curr_num;
    else
      grid[i % 9][i / 9] = curr_num;
  }

  // Second pass: Check if all columns are valid
  for (int col_num = 0; col_num < 9; ++col_num) {
    bool nums[10] = {false};
    for (int row_num = 0; row_num < 9; ++row_num) {
      int curr_num = grid[row_num][col_num];
      if (curr_num != UNASSIGNED && nums[curr_num] == true) {
        grid_status = false;
        return;
      }
      nums[curr_num] = true;
    }
  }

  // Third pass: Check if all rows are valid
  for (int row_num = 0; row_num < 9; ++row_num) {
    bool nums[10] = {false};
    for (int col_num = 0; col_num < 9; ++col_num) {
      int curr_num = grid[row_num][col_num];
      if (curr_num != UNASSIGNED && nums[curr_num] == true) {
        grid_status = false;
        return;
      }
      nums[curr_num] = true;
    }
  }

  // Fourth pass: Check if all blocks are valid
  for (int block_num = 0; block_num < 9; ++block_num) {
    bool nums[10] = {false};
    for (int cell_num = 0; cell_num < 9; ++cell_num) {
      int curr_num = grid[((int)(block_num / 3)) * 3 + (cell_num / 3)]
                         [((int)(block_num % 3)) * 3 + (cell_num % 3)];
      if (curr_num != UNASSIGNED && nums[curr_num] == true) {
        grid_status = false;
        return;
      }
      nums[curr_num] = true;
    }
  }

  // Randomly shuffling the guessing number array
  for (int i = 0; i < 9; i++) {
    this->guessNum[i] = i + 1;
  }

  random_shuffle(this->guessNum, (this->guessNum) + 9, genRandNum);

  grid_status = true;
}
// END: Custom Initialising

// START: Verification status of the custom grid passed
bool Sudoku::verifyGridStatus() const { return grid_status; }
// passed grid is valid

// printing grid
void Sudoku::printGrid() const {
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      if (grid[i][j] == 0)
        cout << 'X';
      else
        cout << grid[i][j];
      cout << "|";
    }
    cout << endl;
  }

  cout << "\nDifficulty of current sudoku(0 being easiest): "
       << this->difficultyLevel;
  cout << endl;
}
// END: Printing the grid

// START: Modified Sudoku solver
bool Sudoku::solveGrid() {
  int row, col;

  // If there is no unassigned location, we are done
  if (!FindUnassignedLocation(this->grid, row, col))
    return true; // success!

  // Consider digits 1 to 9
  for (int num = 0; num < 9; num++) {
    // if looks promising
    if (isSafe(this->grid, row, col, this->guessNum[num])) {
      // make tentative assignment
      this->grid[row][col] = this->guessNum[num];

      // return, if success, yay!
      if (solveGrid())
        return true;

      // failure, unmake & try again
      this->grid[row][col] = UNASSIGNED;
    }
  }

  return false; // this triggers backtracking
}
// END: Modified Sudoku Solver

// START: Check if the grid is uniquely solvable
void Sudoku::countSoln(int &number) {
  int row, col;

  if (!FindUnassignedLocation(this->grid, row, col)) {
    number++;
    return;
  }

  for (int i = 0; i < 9 && number < 2; i++) {
    if (isSafe(this->grid, row, col, this->guessNum[i])) {
      this->grid[row][col] = this->guessNum[i];
      countSoln(number);
    }

    this->grid[row][col] = UNASSIGNED;
  }
}
// END: Check if the grid is uniquely solvable

// START: Gneerate puzzle
void Sudoku::genPuzzle() {
  for (int i = 0; i < 81; i++) {
    int x = (this->gridPos[i]) / 9;
    int y = (this->gridPos[i]) % 9;
    int temp = this->grid[x][y];
    this->grid[x][y] = UNASSIGNED;

    // If now more than 1 solution , replace the removed cell back.
    int check = 0;
    countSoln(check);
    if (check != 1) {
      this->grid[x][y] = temp;
    }
  }
}
// END: Generate puzzle

// START: Printing into SVG file
void Sudoku::printSVG(string path = "") {
  string fileName = path + "svg_gen_rit.txt";
  ifstream file1(fileName.c_str());
  stringstream svg_gen_rit;
  svg_gen_rit << file1.rdbuf();

  ofstream outFile("puzzle_sudoku_rit.svg");
  outFile << svg_gen_rit.rdbuf();

  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      if (this->grid[i][j] != 0) {
        int x = 50 * j + 16;
        int y = 50 * i + 35;

        stringstream text;
        text << "<text x=\"" << x << "\" y=\"" << y
             << "\" style=\"font-weight:bold\" font-size=\"30px\">"
             << this->grid[i][j] << "</text>\n";

        outFile << text.rdbuf();
      }
    }
  }

  outFile << "<text x=\"50\" y=\"500\" style=\"font-weight:bold\" "
             "font-size=\"15px\">Difficulty Level (0 being easiest): "
          << this->difficultyLevel << "</text>\n";
  outFile << "</svg>";
}
// END: Printing into SVG file

// START: Calculate branch difficulty score
int Sudoku::branchDifficultyScore() {
  int emptyPositions = -1;
  int tempGrid[9][9];
  int sum = 0;

  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      tempGrid[i][j] = (this->grid[i][j]);
    }
  }

  while (emptyPositions != 0) {
    vector<vector<int>> empty;

    for (int i = 0; i < 81; i++) {
      if (tempGrid[(int)(i / 9)][(int)(i % 9)] == 0) {
        vector<int> temp;
        temp.push_back(i);

        for (int num = 1; num <= 9; num++) {
          if (isSafe(tempGrid, i / 9, i % 9, num)) {
            temp.push_back(num);
          }
        }

        empty.push_back(temp);
      }
    }

    if (empty.size() == 0) {
      cout << "Hello: " << sum << endl;
      return sum;
    }

    int minIndex = 0;

    int check = empty.size();
    for (int i = 0; i < check; i++) {
      if (empty[i].size() < empty[minIndex].size())
        minIndex = i;
    }

    int branchFactor = empty[minIndex].size();
    int rowIndex = empty[minIndex][0] / 9;
    int colIndex = empty[minIndex][0] % 9;

    tempGrid[rowIndex][colIndex] = this->solnGrid[rowIndex][colIndex];
    sum = sum + ((branchFactor - 2) * (branchFactor - 2));

    emptyPositions = empty.size() - 1;
  }

  return sum;
}
// END: Finish branch difficulty score

// START: Calculate difficulty level of current grid
void Sudoku::calculateDifficulty() {
  int B = branchDifficultyScore();
  int emptyCells = 0;

  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      if (this->grid[i][j] == 0)
        emptyCells++;
    }
  }

  this->difficultyLevel = B * 100 + emptyCells;
}

int main(int argc, char const *argv[]) {

  // Creating an instance of Sudoku
  Sudoku *puzzle = new Sudoku();

  // Creating a seed for puzzle generation
  puzzle->createSeed();

  // Generating the puzzle
  puzzle->genPuzzle();

  // Calculating difficulty of puzzle
  puzzle->calculateDifficulty();

  // testing by printing the grid
  puzzle->printGrid();

  // Printing the grid into SVG file
  string rem = "svg_gen_rit";
  string path = argv[0];
  path = path.substr(0, path.size() - rem.size());
  puzzle->printSVG(path);
  cout << "The above sudoku puzzle has been stored in puzzles_sudko.svg in "
          "current folder\n";
  // freeing the memory
  delete puzzle;

  return 0;
}
// END: The main function
