#include <benchmark/benchmark.h>
#include <atomic>
#include <thread>
#include <new>

#define MAX 10000

constexpr std::size_t CACHE_LINE_SIZE = 64;

struct alignas(CACHE_LINE_SIZE) AlignedAtomicInt {
    std::atomic<int> value{0};
};

/*
struct keep_apart
{
  alignas(std::hardware_destructive_interference_size) std::atomic<int> cat;
  alignas(std::hardware_destructive_interference_size) std::atomic<int> dog;
};
*/

void work(std::atomic<int>& num){
  for(int i = 0; i < MAX; ++i){
    num++;
   }
 }

static void bench_false_sharing(benchmark::State &state){
  while(state.KeepRunning()) {
    std::atomic<int> a;
    a = 0;
    std::atomic<int> b;
    b = 0;
    std::atomic<int> c;
    c = 0;
    std::atomic<int> d;
    d = 0;

    std::thread t1([&]() { work(a); });
    std::thread t2([&]() { work(b); });
    std::thread t3([&]() { work(c); });
    std::thread t4([&]() { work(d); });

    t1.join();
    t2.join();
    t3.join();
    t4.join();
  }
}
BENCHMARK(bench_false_sharing);

static void bench_no_false_sharing(benchmark::State &state){
  while(state.KeepRunning()) {
    AlignedAtomicInt a;
    AlignedAtomicInt b;
    AlignedAtomicInt c;
    AlignedAtomicInt d;

    std::thread t1([&]() { work(a.value); });
    std::thread t2([&]() { work(b.value); });
    std::thread t3([&]() { work(c.value); });
    std::thread t4([&]() { work(d.value); });

    t1.join();
    t2.join();
    t3.join();
    t4.join();
  }
}
BENCHMARK(bench_no_false_sharing);

BENCHMARK_MAIN();
