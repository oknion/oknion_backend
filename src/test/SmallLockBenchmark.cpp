/*
 * SmallLockBenchmark.cpp
 *
 *  Created on: Jun 22, 2016
 *      Author: kienpc
 */

#include <folly/Benchmark.h>
#include <folly/SmallLocks.h>

BENCHMARK(MicroSpinLockUncontendedBenchmark, iters) {
  folly::MicroSpinLock lock;
  lock.init();
  while (iters--) {
    lock.lock();
    lock.unlock();
  }
}

BENCHMARK(PicoSpinLockUncontendedBenchmark, iters) {
  // uint8_t would be more fair, but PicoSpinLock needs at lesat two bytes
  folly::PicoSpinLock<uint16_t> lock;
  lock.init();
  while (iters--) {
    lock.lock();
    lock.unlock();
  }
}

BENCHMARK(MicroLockUncontendedBenchmark, iters) {
  folly::MicroLock lock;
  lock.init();
  while (iters--) {
    lock.lock();
    lock.unlock();
  }
}

BENCHMARK(StdMutexUncontendedBenchmark, iters) {
  std::mutex lock;
  while (iters--) {
    lock.lock();
    lock.unlock();
  }
}

struct VirtualBase {
  virtual void foo() = 0;
  virtual ~VirtualBase() {
  }
};

struct VirtualImpl: VirtualBase {
  virtual void foo() { /* noop */
  }
  virtual ~VirtualImpl() {
  }
};

#ifndef __clang__
__attribute__((noinline, noclone))  VirtualBase* makeVirtual() {
  return new VirtualImpl();
}

BENCHMARK(VirtualFunctionCall, iters) {
  VirtualBase* vb = makeVirtual();
  while (iters--) {
    vb->foo();
  }
  delete vb;
}
#endif

int main(int argc, char** argv) {
  gflags::ParseCommandLineFlags(&argc, &argv, true);
  folly::runBenchmarks();
  return 0;
}
