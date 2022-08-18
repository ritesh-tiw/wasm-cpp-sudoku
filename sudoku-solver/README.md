# Sudoku Solver

A brute force approach to solving Sudoku. Written in C++, compiled to WebAssembly and [presented with React](https://tomcant.dev/sudoku-solver).

## Compile and Run

Run `make run` at the root of the project to compile and run the solver on http://localhost (this uses the [emscripten/emsdk](https://hub.docker.com/r/emscripten/emsdk) and [nginx](https://hub.docker.com/_/nginx) Docker images).

## The Algorithm

We use [depth-first search](https://en.wikipedia.org/wiki/Depth-first_search) to apply every combination of possible choices per cell either until the grid is full or until there are no more choices to explore, in which case the puzzle is unsolvable.

Roughly speaking, the following steps are taken:

1. Make as many forced choices as possible (i.e. where the number of choices for a given cell is one). This will be enough to solve most _easy_ puzzles.
2. Check for completeness or unsolvability:
   - If the grid now contains no empty cells then we are done and the grid is returned.
   - If the grid now contains an empty cell with no choices then mark this combination as unsolvable.
3. Find the cell with the fewest choices and apply each of them in turn, attempting to solve each new puzzle this produces (recurse back to step 1).
