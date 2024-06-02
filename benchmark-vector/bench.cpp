#include <benchmark/benchmark.h>
#include <vector>

static void escape(void *p){
  asm volatile("" : : "g"(p) : "memory");
}

static void clobber(){
  asm volatile("" : : : "memory");
}

static void bench_create(benchmark::State &state){
  while(state.KeepRunning()) {
    std::vector<int> v;
    (void) v;
  }
}
BENCHMARK(bench_create);

static void bench_reserve(benchmark::State &state){
  while(state.KeepRunning()) {
    std::vector<int> v;
    v.reserve(1);
  }
}
BENCHMARK(bench_reserve);

static void bench_push_back(benchmark::State &state){
  while(state.KeepRunning()) {
    std::vector<int> v;
    v.reserve(1);
    v.push_back(42);
  }
}
BENCHMARK(bench_push_back);

static void bench_create_pinned(benchmark::State &state){
  while(state.KeepRunning()) {
    std::vector<int> v;
    escape(&v);
    (void) v;
  }
}
BENCHMARK(bench_create_pinned);

static void bench_reserve_pinned(benchmark::State &state){
  while(state.KeepRunning()) {
    std::vector<int> v;
    v.reserve(1);
    escape(v.data());
  }
}
BENCHMARK(bench_reserve_pinned);

static void bench_push_back_pinned(benchmark::State &state){
  while(state.KeepRunning()) {
    std::vector<int> v;
    v.reserve(1);
    escape(v.data());
    v.push_back(42);
    clobber();
  }
}
BENCHMARK(bench_push_back_pinned);

BENCHMARK_MAIN();
