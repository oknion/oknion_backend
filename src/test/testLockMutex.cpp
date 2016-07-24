/*
 * testLockMutex.cpp
 *
 *  Created on: Jun 17, 2016
 *      Author: kienpc
 */
#include <folly/Benchmark.h>
#include <Poco/Mutex.h>
#include <folly/Foreach.h>
#include <mutex>
#include <memory>
#include <Poco/SharedPtr.h>

using namespace folly;

class A {
  char* data;
public:
  A() {
    data = new char[1000000];
  }
  ~A() {
    delete[] data;
  }
};

BENCHMARK(stdSharedPtr) {

  FOR_EACH_RANGE (i, 0, 100000)
  {
    std::shared_ptr<A> aPtr(new A());
    for (int i = 0; i < 1000; i++) {
      auto nptr = aPtr;
    }

  }

}

BENCHMARK(stdRawPtr) {

  FOR_EACH_RANGE (i, 0, 100000)
  {
    auto aPtr = new A();
    for (int i = 0; i < 1000; i++) {
      auto nptr = aPtr;
    }
    delete aPtr;
  }

}

BENCHMARK(PocoPtr) {

  FOR_EACH_RANGE (i, 0, 100000)
  {
    Poco::SharedPtr<A> aPtr(new A());
    for (int i = 0; i < 1000; i++) {
      auto nptr = aPtr;
    }

  }

}

BENCHMARK(stdMutex) {
  std::mutex* ma = new std::mutex[1000];
  FOR_EACH_RANGE (i, 0, 1000)
  {
    std::lock_guard<std::mutex> g(ma[i]);
  }
}

BENCHMARK(pocoMutex) {
  Poco::Mutex* ma = new Poco::Mutex[1000];
  FOR_EACH_RANGE (i, 0, 1000)
  {
    Poco::Mutex::ScopedLock lock(ma[i]);
  }
}

int main(int agrv, char** agrs) {
  folly::runBenchmarks();
}

