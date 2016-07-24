/*
 * follyCacheUsage.cpp
 *
 *  Created on: Jun 14, 2016
 *      Author: kienpc
 */

#include <folly/EvictingCacheMap.h>
#include <string>
#include <gflags/gflags.h>
#include <glog/logging.h>
#include <folly/Random.h>

DEFINE_int64(cacheSize, 500000, "Poco cache size");
DEFINE_int64(insertCount, 1000000, "Number of key will be inserted");
DEFINE_int32(clearSize, 10,
    "Number of item will be evicted when cache reach limit size");

using
namespace folly;
using namespace std;

int main(int agrv, char** agrs) {
  auto cache = new folly::EvictingCacheMap<int64_t, string>(FLAGS_cacheSize,
      FLAGS_clearSize);
  for (int64_t i = 0; i < FLAGS_insertCount; i++) {
    auto key = Random::rand32(UINT_MAX);
    key=Random::rand32(1,2);
    cache->set(i,
        "Full length M16A4 with an ACOG 4x scope....painted tan and black..... I really don't like the G36 mags..... to fat to fit with most pouches......and those shitty knobs to click them together..... For the rest the G36 is pretty damn cool; especially love the holes to capture your pins while stripping it.... ");
  }
  delete cache;
  return 0;
}
