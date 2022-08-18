#include "solver.h"
#include <emscripten/bind.h>

using sudoku::Grid;
using sudoku::Solver;

EMSCRIPTEN_BINDINGS(Grid) {
  emscripten::class_<Grid>("Grid")
    .function("ToString", &Grid::ToString)
    .class_function("FromString", &Grid::FromString);
}

EMSCRIPTEN_BINDINGS(Solver) {
  emscripten::class_<Solver>("Solver")
    .class_function("Solve", &Solver::Solve);
}

std::string getExceptionMessage(intptr_t ptr) {
  return std::string(reinterpret_cast<std::exception *>(ptr)->what());
}

EMSCRIPTEN_BINDINGS(getExceptionMessage) {
  emscripten::function("getExceptionMessage", &getExceptionMessage);
}
