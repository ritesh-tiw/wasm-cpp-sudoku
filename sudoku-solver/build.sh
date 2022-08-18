#!/bin/bash

emcc --bind -o public/sudoku-solver.js src/wasm-bindings.cc src/solver.cc src/grid.cc -s NO_DISABLE_EXCEPTION_CATCHING -O3
