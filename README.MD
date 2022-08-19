# PROJECT_SUDKO_WASM

```mermaid
graph TB
  Sudko-app --> Sudko-genrator
  Sudko-app --> Sudko-Solver
	Sudko-genrator --> what-it-can-do
  what-it-can-do --> genrate-random-sudko
  what-it-can-do --> generate-an-svg-file-in-cwd-9*9
  Sudko-Solver --> uses-wasm-tell-solve-the-sudko-if-it-is-solveable

 

```

> TO RUN SUDKO-GENERATOR RUN
> 

```markdown
from cwd as sudko-generator
bash setup.sh
now u can run sudkoGen from anywhere after restarting the terminal
```

> TO RUN SUDKO_SOLVER from sudko-solver as cwd
> 

```markdown
./build.sh

```

In case its not working just run 

```markdown
emcc --bind -o public/sudoku-solver.js src/wasm-bindings.cc src/solver.cc src/grid.cc -s NO_DISABLE_EXCEPTION_CATCHING -O3
```

from the terminal

> u need to have wasm , g++ ,cmake ,installed
> 

now to run the sudko_solver_int_web

uses

```markdown
python3 -m http.server
```

[Screencast from 19-08-22 05:15:31 AM IST.webm](PROJECT_SUDKO_WASM%20205d0738a0fe4d589acbdacb397b0d9c/Screencast_from_19-08-22_051531_AM_IST.webm)

[Screencast from 19-08-22 05:17:26 AM IST.webm](PROJECT_SUDKO_WASM%20205d0738a0fe4d589acbdacb397b0d9c/Screencast_from_19-08-22_051726_AM_IST.webm)
