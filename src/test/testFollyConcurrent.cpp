/*
 * testFollyConcurrent.cpp
 *
 *  Created on: Jun 21, 2016
 *      Author: kienpc
 */
#include <folly/EvictingCacheMap.h>
#include <thread>
#include <chrono>
#include <iostream>
#include <glog/logging.h>

using namespace std;
void removeHook(int k, int&& v);
void removeFromCache(folly::EvictingCacheMap<int, int>* cache, int key) {
  std::this_thread::sleep_for(chrono::seconds(1));
  cache->erase(key);
  printf("Key %d removed\n", key);
}
void makeCacheEvictAll(folly::EvictingCacheMap<int, int>* cache) {
  std::this_thread::sleep_for(chrono::seconds(2));
  printf("set to invoke evict happened \n");
  for (int i = 20; i < 1000; i++) {
    cache->set(i, i * 19);
  }
  printf("cache size: %u\n", cache->size());
  cache->set(11, 11, true, removeHook);
  for (int i = 10; i < 1000; i++) {
    int value = i * 19;
    cache->set(i, value);
  }
}
void getFromCache(folly::EvictingCacheMap<int, int>* cache, int key) {
  auto it = cache->find(key);
  if (it != cache->end()) {
    printf("Found key: %d\n", key);
    std::this_thread::sleep_for(chrono::seconds(5));
    cout << it->second << endl;
  }
  it = cache->find(key);
  if (it != cache->end()) {
    cout << it->second << endl;
  }
}

int main(int argc, char** argv) {
  google::InitGoogleLogging(argv[0]);
  google::InstallFailureSignalHandler();
  auto cache = new folly::EvictingCacheMap<int, int>(50, 2);
  cache->set(10, 10, true, removeHook);
  cache->set(11, 11, true, removeHook);
  thread remover(removeFromCache, cache, 10);
  thread getter(getFromCache, cache, 10);
  thread evicter(makeCacheEvictAll, cache);
  remover.join();
  getter.join();
  evicter.join();
  google::ShutdownGoogleLogging();
  return 0;
}

void removeHook(int k, int&& v) {
  printf("Prunce hook \n");
  int a = std::move(v);
  printf("Prunce hook key %d, value %d\n", k, a);
}
