var Module = {
  onRuntimeInitialized: () => {
    onmessage = e => {
      try {
        const grid = Module.Grid.FromString(e.data);

        self.postMessage({
          cells: Module.Solver.Solve(grid).ToString(),
        });
      } catch (error) {
        self.postMessage({
          error: Module.getExceptionMessage(error),
        });
      }
    };
  },
};

self.importScripts('sudoku-solver.js');
