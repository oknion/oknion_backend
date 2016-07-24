/*
 * benchSerialize.cpp
 *
 *  Created on: Jul 6, 2016
 *      Author: kienpc
 */

#include "storage/Serialize.h"
#include "zlist/ZList_types.h"
#include <folly/Benchmark.h>
#include <iostream>
#include <cassert>
#include "storage/LevelDbPersistence.h"
#include <boost/filesystem.hpp>
#include <folly/Random.h>

using namespace vng_wpl::backend;
using namespace zingme::zlist::thrift::cpp2;
using namespace folly;
ZListItem item;
ZListItem item2;
string ss, ss2, ss3, ss4;
LevelDbPersistence<int, ZListItem>* persisBi;
LevelDbPersistence<int, ZListItem, ThriftCompactSerialize<ZListItem>,
    ThriftCompactDeserialize<ZListItem>>* persisCom;

BENCHMARK(Serialize) {
  ThriftCompactSerialize<ZListItem> seri;
  for (auto i = 0; i < 10000; i++) {
    ss = seri(item);
  }
}

BENCHMARK_RELATIVE(Deserialize) {
  ThriftCompactDeserialize<ZListItem> deseri;
  for (auto i = 0; i < 10000; i++) {
    ZListItem *iptr = deseri(ss);
    delete iptr;
  }
}

//////////////////////

BENCHMARK_RELATIVE(SerializeBinary) {
  ThriftBinarySerialize<ZListItem> seri;
  for (auto i = 0; i < 10000; i++) {
    ss2 = seri(item);
  }
}

BENCHMARK_RELATIVE(DeserializeBinary) {
  ThriftBinaryDeserialize<ZListItem> deseri;
  for (auto i = 0; i < 10000; i++) {
    ZListItem *iptr = deseri(ss2);
    delete iptr;
  }
}

//////////////////////

BENCHMARK_RELATIVE(SerializeBinarySmallObj) {
  ThriftBinarySerialize<ZListItem> seri;
  for (auto i = 0; i < 1000; i++) {
    ss3 = seri(item2);
  }
}

BENCHMARK_RELATIVE(DeserializeBinarySmallObj) {
  ThriftBinaryDeserialize<ZListItem> deseri;
  for (auto i = 0; i < 1000; i++) {
    ZListItem *iptr = deseri(ss3);
    delete iptr;
  }
}

BENCHMARK_RELATIVE(SerializeSmallObj) {
  ThriftCompactSerialize<ZListItem> seri;
  for (auto i = 0; i < 1000; i++) {
    ss4 = seri(item2);
  }
}

BENCHMARK_RELATIVE(DeserializeSmallObj) {
  ThriftCompactDeserialize<ZListItem> deseri;
  for (auto i = 0; i < 1000; i++) {
    ZListItem *iptr = deseri(ss4);
    delete iptr;
  }
}

BENCHMARK(LevelDbPersistenceBinary) {
  for (auto iter = 0; iter < 10000; ++iter)
    persisBi->set(iter, item);
}
BENCHMARK(LevelDbPersistenceCompact) {
  for (auto iter = 0; iter < 10000; ++iter)
    persisCom->set(iter, item);
}



BENCHMARK(LevelDbPersistenceBinary100) {
  for (auto iter = 0; iter < 100; ++iter)
    persisBi->set(iter, item);
}
BENCHMARK(LevelDbPersistenceCompact100) {
  for (auto iter = 0; iter < 100; ++iter)
    persisCom->set(iter, item);
}



BENCHMARK(LevelDbPersistenceBinaryRand) {
  int iter = folly::Random::rand32();
  persisBi->set(iter, item);
}
BENCHMARK(LevelDbPersistenceCompactRand) {
  int iter = folly::Random::rand32();
  persisCom->set(iter, item);
}
int main(int argc, char** argv) {
  item.count = 10000;
  for (size_t i = 0; i < 10000; i++) {
    item.values.push_back(i);
  }
  item2.count = 100;
  for (size_t i = 0; i < 100; i++) {
    item2.values.push_back(i);
  }

  auto conf = LevelDbConfig();
  conf.data_location = "db1";
  persisBi = new LevelDbPersistence<int, ZListItem>();
  persisCom = new LevelDbPersistence<int, ZListItem,
      ThriftCompactSerialize<ZListItem>, ThriftCompactDeserialize<ZListItem>>(
      conf);

  folly::runBenchmarks();
  std::cout << ss.size() << std::endl;
  std::cout << ss2.size() << std::endl;
  std::cout << ss3.size() << std::endl;

// clean up
  delete persisBi;
  delete persisCom;
  boost::filesystem::remove_all("db");
  boost::filesystem::remove_all("db1");

  return 0;
}

