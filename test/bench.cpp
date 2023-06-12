
#include <benchmark/benchmark.h>
#include <cstring>
#include <iostream>
#include <memory>
#include "smalloc.h"

constexpr std::size_t kDefaultHeapSize{512UL * 1024 * 1024};
constexpr std::size_t kAllocateNum{100};

double static GetMaxValue(std::vector<double> const& v)
{
    return *(std::max_element(std::begin(v), std::end(v)));
}

double static GetMinValue(std::vector<double> const& v)
{
    return *(std::min_element(std::begin(v), std::end(v)));
}

static void TlsfBenchmark(benchmark::State& state)
{
    for (auto _ : state) {
        auto bytes = state.range(0);
        std::vector<void*> allocatedPtr(kAllocateNum);
        // 申请N次内存，触发最坏情况
        for (auto i = 0; i < 100; i++) {
            auto* ptr = smalloc::smalloc(bytes);
            benchmark::DoNotOptimize(ptr);
            if (ptr != nullptr) {
                allocatedPtr[i] = ptr;
            } else {
                exit(-1);
            }
        }

        // 释放所有申请的内存
        for (auto* ptr : allocatedPtr) {
            smalloc::sfree(ptr);
        }
    }
}

BENCHMARK(TlsfBenchmark)
    ->RangeMultiplier(2)
    ->Arg(4)
    ->Arg(16)
    ->Arg(32)
    ->Arg(64)
    ->Arg(256)
    ->Arg(512)
    ->Arg(1024)
    ->Arg(2048)
    ->Arg(4096)
    ->Arg(8192)
    ->Arg(1048576)
    ->Repetitions(2)
    ->Threads(4)
    ->ComputeStatistics("max", GetMaxValue)
    ->ComputeStatistics("min", GetMinValue);


static void Tlsf_S_Benchmark(benchmark::State& state)
{
    for (auto _ : state) {
        auto bytes = state.range(0);
        std::vector<void*> allocatedPtr(kAllocateNum);
        // 申请N次内存，触发最坏情况
        for (auto i = 0; i < 100; i++) {
            auto* ptr = smalloc::smalloc_s(bytes);
            benchmark::DoNotOptimize(ptr);
            if (ptr != nullptr) {
                allocatedPtr[i] = ptr;
            } else {
                exit(-1);
            }
        }

        // 释放所有申请的内存
        for (auto* ptr : allocatedPtr) {
            smalloc::sfree_s(ptr);
        }
    }
}

BENCHMARK(Tlsf_S_Benchmark)
    ->RangeMultiplier(2)
    ->Arg(4)
    ->Arg(16)
    ->Arg(32)
    ->Arg(64)
    ->Arg(256)
    ->Arg(512)
    ->Arg(1024)
    ->Arg(2048)
    ->Arg(4096)
    ->Arg(8192)
    ->Arg(1048576)
    ->Repetitions(2)
    ->Threads(4)
    ->ComputeStatistics("max", GetMaxValue)
    ->ComputeStatistics("min", GetMinValue);

static void MallocBenchmark(benchmark::State& state)
{
    for (auto _ : state) {
        auto bytes = state.range(0);
        std::vector<void*> allocatedPtr(kAllocateNum);
        // 申请N次内存，触发最坏情况
        for (auto i = 0; i < 100; i++) {
            auto* ptr = malloc(bytes);
            benchmark::DoNotOptimize(ptr);
            if (ptr != nullptr) {
                allocatedPtr[i] = ptr;
            } else {
                exit(-1);
            }
        }

        // 释放所有申请的内存
        for (auto* ptr : allocatedPtr) {
            free(ptr);
        }
    }
}

BENCHMARK(MallocBenchmark)
    ->RangeMultiplier(2)
    ->Arg(4)
    ->Arg(16)
    ->Arg(32)
    ->Arg(64)
    ->Arg(256)
    ->Arg(512)
    ->Arg(1024)
    ->Arg(2048)
    ->Arg(4096)
    ->Arg(8192)
    ->Arg(1048576)
    ->Repetitions(2)
    ->Threads(4)
    ->ComputeStatistics("max", GetMaxValue)
    ->ComputeStatistics("min", GetMinValue);
int main(int argc, char** argv)
{
    ::benchmark::Initialize(&argc, argv);
    if (::benchmark::ReportUnrecognizedArguments(argc, argv)) {
        return 1;
    }

    ::benchmark::RunSpecifiedBenchmarks();

    return 0;
}