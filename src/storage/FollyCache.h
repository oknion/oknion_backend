/*
 * FollyCache.h
 *
 *  Created on: Jun 21, 2016
 *      Author: kienpc
 *
 */
#pragma once

#include "Storage.h"
#include <mutex>
#include <gflags/gflags.h>
#include <folly/EvictingCacheMap.h>
#include <folly/MicroSpinLock.h>
#include <boost/noncopyable.hpp>

DECLARE_int64(storageCacheClearSize);

namespace vng_wpl {
namespace backend {

using namespace ::folly;
struct FollyCacheConfig: CacheConfig {
  size_t clearSize = FLAGS_storageCacheClearSize;
};

/**
 * Note: Use MicroSpinLock will use more CPU but
 * it makes thread don't need to sleep and wake up so its probably
 * faster than std::mutex. You still can use std::mutex or other
 * mutex by using this template class
 */

template<typename _Key, typename _Value,
    class keyHasher = std::hash<_Key>,
    class MUTEX = folly::MicroSpinLock
>
class FollyCache: public ICache<_Key, _Value> {
public:
  FollyCache(FollyCacheConfig conf) {
    _instance = new EvictingCacheMap<_Key, _Value>(conf.maxItems,
        conf.clearSize);
    mutexSize = conf.maxItems / 2;

    // this mutex initiation must have "()" so it's a zero initiation
    // so we don't have to call mutexes[i].init()
    mutexes = new MUTEX[mutexSize]();
  }
  FollyCache() :
      FollyCache(FollyCacheConfig()) {
  }

  _Value* getByKey(const _Key& key) {

    std::lock_guard<MUTEX> guard(mutexForKey(key));

    _Value* res = nullptr;
    auto iter = _instance->find(key);
    if (iter != _instance->end()) {
      res = new _Value(iter->second);
    }

    return res;
  }

  void set(const _Key& key, const _Value& value) {

    std::lock_guard<MUTEX> guard(mutexForKey(key));

    _instance->set(key, value);
  }

  void removeByKey(const _Key& key) {

    std::lock_guard<MUTEX> guard(mutexForKey(key));

    _instance->erase(key);
  }

  void printStat(std::ostream& output) {
    output << "Folly EvictingCacheMap size: " << _instance->size() << endl;
  }

  virtual ~FollyCache() {
    delete _instance;
    delete[] mutexes;
  }

private:
  EvictingCacheMap<_Key, _Value>* _instance;
  MUTEX * mutexes;
  size_t mutexSize;

  MUTEX& mutexForKey(const _Key& key) {
    auto mi = keyHasher()(key) % this->mutexSize;
    mi = mi > 0 ? mi : -mi;
    return mutexes[mi];
  }

};

} // back_end
} // vng_wpl

