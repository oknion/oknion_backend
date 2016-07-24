/*
 * testSerializer.cpp
 *
 *  Created on: Jun 28, 2016
 *      Author: kienpc
 */
#include <iostream>
#include <folly/FBString.h>
#include <storage/Storage.h>
#include <storage/Serialize.h>
#include <folly/Random.h>
#include <climits>
#include <folly/Benchmark.h>

using namespace ::std;
using namespace ::folly;
using namespace ::vng_wpl::backend;

BENCHMARK(int32) {

  int32_t i32 = static_cast<int32_t>(folly::Random::rand32());
  printf("Serialize i32 %d\n", i32);
  auto i32s = ThriftSerialize<int32_t>()(i32);
  printf("Serialized string %s\n", i32s.c_str());
  auto i32ptr = ThriftDeserialize<int32_t>()(i32s);
  assert(i32 == *i32ptr);
  printf("Serialized string %d\n", *i32ptr);
}
BENCHMARK(int64) {

  int64_t i64 = static_cast<int64_t>(folly::Random::rand64());
  printf("Serialize i64 %ld\n", i64);
  auto i64s = ThriftSerialize<int64_t>()(i64);
  printf("Serialized string %s\n", i64s.c_str());
  auto i64ptr = ThriftDeserialize<int64_t>()(i64s);
  printf("Serialized string %ld\n", *i64ptr);
  assert(i64 == *i64ptr);

}
BENCHMARK(int16) {

  int16_t i16 = static_cast<int16_t>(folly::Random::rand32(0, USHRT_MAX));
  printf("Serialize i16 %d\n", i16);
  auto i16s = ThriftSerialize<int16_t>()(i16);
  printf("Serialized string %s\n", i16s.c_str());
  auto i16ptr = ThriftDeserialize<int16_t>()(i16s);
  printf("Serialized string %d\n", *i16ptr);
  assert(i16 == *i16ptr);
}

int main(int argc, char** argv) {

  folly::runBenchmarks();
  return 0;
}
