#include <benchmark/benchmark.h>
#include <vector>

#pragma pack(1);

static void bench_lots_of_memory_padding(benchmark::State &state){
  while(state.KeepRunning()) {
    class manyPads{
    public:
      manyPads(){       // Alignment
        char c1;        // 1
        long long n1;   // 8
        char c2;        // 1
        long long n2;   // 8
        char c3;        // 1
        long long n3;   // 8
        char c4;        // 1
        long long n4;   // 8
        char c5;        // 1
        long long n5;   // 8
        char c6;        // 1
        long long n6;   // 8
        char c7;        // 1
        long long n7;   // 8
        char c8;        // 1
        long long n8;   // 8
      }
    };

    manyPads myObject = manyPads();
  }
}
BENCHMARK(bench_lots_of_memory_padding);


static void bench_no_memory_padding(benchmark::State &state){
  while(state.KeepRunning()) {
    class manyPads{
    public:
      manyPads(){       // Alignment
        long long n1;   // 8
        long long n2;   // 8
        long long n3;   // 8
        long long n4;   // 8
        long long n5;   // 8
        long long n6;   // 8
        long long n7;   // 8
        long long n8;   // 8
        char c1;        // 1
        char c2;        // 1
        char c3;        // 1
        char c4;        // 1
        char c5;        // 1
        char c6;        // 1
        char c7;        // 1
        char c8;        // 1
      }
    };

    manyPads myObject = manyPads();
  }
}
BENCHMARK(bench_no_memory_padding);

BENCHMARK_MAIN();
