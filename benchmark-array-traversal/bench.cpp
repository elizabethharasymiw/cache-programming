#include <benchmark/benchmark.h>

#define MAX 3000

static void bench_row_major_traversal(benchmark::State &state){
  while(state.KeepRunning()) {
    int total = 0;
    int myArray[MAX][MAX];

    for(int i = 0; i < MAX; ++i){
      for(int j = 0; j < MAX; ++j){
        total += myArray[i][j];
      }
    }

  }
}
BENCHMARK(bench_row_major_traversal);

static void bench_column_major_traversal(benchmark::State &state){
  while(state.KeepRunning()) {

    int total = 0;
    int myArray[MAX][MAX];

    for(int i = 0; i < MAX; ++i){
      for(int j = 0; j < MAX; ++j){
        total += myArray[j][i];
      }
    }

  }
}
BENCHMARK(bench_column_major_traversal);

BENCHMARK_MAIN();
