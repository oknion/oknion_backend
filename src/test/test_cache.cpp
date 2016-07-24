/*
 * test_cache.cpp
 *
 *  Created on: Jun 13, 2016
 *      Author: kienpc
 */
#include <folly/EvictingCacheMap.h>
#include <Poco/LRUCache.h>
#include <folly/Random.h>
#include <vector>
#include <climits>
#include <ctime>
#include <folly/Benchmark.h>
#include <iostream>

using namespace std;
using namespace folly;
#define TEST_COUNT 10000

BENCHMARK(testPocoCache) {
  vector<string> vecValue;
  vecValue.push_back("And what is love? It is a doll dressed up");
  vecValue.push_back("For idleness to cosset, nurse, and dandle;");
  vecValue.push_back("A thing of soft misnomers, so divine");
  vecValue.push_back("That silly youth doth think to make itself");
  vecValue.push_back("Divine by loving, and so goes on");
  vecValue.push_back("Yawning and doting a whole summer long,");
  vecValue.push_back("Till Miss's comb is made a perfect tiara,");
  vecValue.push_back("And common Wellingtons turn Romeo boots;");
  vecValue.push_back("Till Cleopatra lives at Number Seven,");
  vecValue.push_back("And Antony resides in Brunswick Square.");
  vecValue.push_back("Fools! if some passions high have warmed the world,");
  vecValue.push_back(
      "If queens and soldiers have played deep for hearts,It is no reason why such agonies");
  vecValue.push_back("Should be more common than the growth of weeds.");
  vecValue.push_back(
      "Fools! make me whole again that weighty pearl The queen of Egypt melted, and I'll say");
  vecValue.push_back("That ye may love in spite of beaver hats.");
  auto pocoCache = new Poco::LRUCache<int64_t, string>(100000);
  for (int64_t i = 0; i < TEST_COUNT; i++) {
    auto key = Random::rand32(UINT_MAX);
    auto valueIndex = Random::rand32(vecValue.size());
    pocoCache->add(key, vecValue[valueIndex]);
  }
  delete pocoCache;
}
BENCHMARK_RELATIVE(testFollyRLUCache) {
  vector<string> vecValue;
  vecValue.push_back("And what is love? It is a doll dressed up");
  vecValue.push_back("For idleness to cosset, nurse, and dandle;");
  vecValue.push_back("A thing of soft misnomers, so divine");
  vecValue.push_back("That silly youth doth think to make itself");
  vecValue.push_back("Divine by loving, and so goes on");
  vecValue.push_back("Yawning and doting a whole summer long,");
  vecValue.push_back("Till Miss's comb is made a perfect tiara,");
  vecValue.push_back("And common Wellingtons turn Romeo boots;");
  vecValue.push_back("Till Cleopatra lives at Number Seven,");
  vecValue.push_back("And Antony resides in Brunswick Square.");
  vecValue.push_back("Fools! if some passions high have warmed the world,");
  vecValue.push_back(
      "If queens and soldiers have played deep for hearts,It is no reason why such agonies");
  vecValue.push_back("Should be more common than the growth of weeds.");
  vecValue.push_back(
      "Fools! make me whole again that weighty pearl The queen of Egypt melted, and I'll say");
  vecValue.push_back("That ye may love in spite of beaver hats.");
  auto cache = new folly::EvictingCacheMap<int64_t, string>(100000, 10);
  for (int64_t i = 0; i < TEST_COUNT; i++) {
    auto key = Random::rand32(UINT_MAX);
    auto valueIndex = Random::rand32(vecValue.size());
    cache->set(key, vecValue[valueIndex]);
  }
  delete cache;
}

folly::EvictingCacheMap<int64_t, string>* buildFollyCache(){
  vector<string> vecValue;
    vecValue.push_back("And what is love? It is a doll dressed up");
    vecValue.push_back("For idleness to cosset, nurse, and dandle;");
    vecValue.push_back("A thing of soft misnomers, so divine");
    vecValue.push_back("That silly youth doth think to make itself");
    vecValue.push_back("Divine by loving, and so goes on");
    vecValue.push_back("Yawning and doting a whole summer long,");
    vecValue.push_back("Till Miss's comb is made a perfect tiara,");
    vecValue.push_back("And common Wellingtons turn Romeo boots;");
    vecValue.push_back("Till Cleopatra lives at Number Seven,");
    vecValue.push_back("And Antony resides in Brunswick Square.");
    vecValue.push_back("Fools! if some passions high have warmed the world,");
    vecValue.push_back(
        "If queens and soldiers have played deep for hearts,It is no reason why such agonies");
    vecValue.push_back("Should be more common than the growth of weeds.");
    vecValue.push_back(
        "Fools! make me whole again that weighty pearl The queen of Egypt melted, and I'll say");
    vecValue.push_back("That ye may love in spite of beaver hats.");
    auto cache = new folly::EvictingCacheMap<int64_t, string>(100000, 10);
    for (int64_t i = 0; i < TEST_COUNT; i++) {
      auto key = Random::rand32(UINT_MAX);
      auto valueIndex = Random::rand32(vecValue.size());
      cache->set(key, vecValue[valueIndex]);
    }
    return cache;
}

int main(int agrv, char** agrs) {
  runBenchmarks();
  folly::EvictingCacheMap<int64_t, string>* cache = buildFollyCache();
  for (auto it = cache->begin(); it != cache->end(); ++it) {
    cout << "Key: " << it->first << ", value: " << it->second << std::endl;
  }
  std::cout << "delete cache" << std::endl;
  delete cache;
  return 0;
}

