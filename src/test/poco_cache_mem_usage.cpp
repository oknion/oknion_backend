/*
 * test_cache_mem_usage.cpp
 *
 *  Created on: Jun 13, 2016
 *      Author: kienpc
 */

#include <Poco/LRUCache.h>
#include <vector>
#include <thread>
#include <chrono>
#include <gflags/gflags.h>
#include <glog/logging.h>

DEFINE_int64(cacheSize, 500000, "Poco cache size");
DEFINE_int64(insertCount, 1000000, "Number of key will be inserted");

using
namespace std;
int main(int argc, char** agrs) {

  gflags::ParseCommandLineFlags(&argc, &agrs, true);

  auto pocoCache = new Poco::LRUCache<int64_t, string>(FLAGS_cacheSize);
  for (auto i = 0l; i < FLAGS_insertCount; i++) {
    pocoCache->add(i,
        "apsedifj asdf jasdfja;g afg ;ajh iahg oajsdlk jasgjalgh ask;lasdjpfaiujsef;kljapiufasjdhguxkdnfapisjvlkdhgpiaej;lkjcv");
  }
  this_thread::sleep_for(chrono::seconds(10));
  delete pocoCache;
  return 0;
}
