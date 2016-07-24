/*
 * File:   Storage.h
 * Author: kienpc
 *
 * Created on June 16, 2016, 10:54 AM
 */
#pragma once

#include "Serialize.h"
#include <mutex>
#include <tuple>
#include <memory>
#include <string>
#include <functional>
#include <gflags/gflags.h>
#include <boost/core/noncopyable.hpp>
#include <cstdlib>
#include <cmath>

DECLARE_uint64(storageCacheSize);
DECLARE_bool(storagePersistenceCreateIfMissing);
DECLARE_string(storagePersistenceLocation);
DECLARE_uint64(storageStorageMutexCount);

namespace vng_wpl {
namespace backend {
using namespace ::std;
using namespace ::apache::thrift;

template<typename _Key, typename _Value>
class ICache {
public:
  virtual _Value* getByKey(const _Key& key) = 0;
  virtual void set(const _Key& key, const _Value& value) = 0;
  virtual void removeByKey(const _Key& key) = 0;
  virtual void printStat(std::ostream& output) = 0;

  virtual ~ICache() {
  }

private:

};

struct CacheConfig {
  size_t maxItems = FLAGS_storageCacheSize;
};

template<class _Key, class _Value>
class IIterator {
public:
  virtual void first() = 0;
  virtual void next() = 0;
  virtual bool isValid() = 0;
  virtual _Value* getValue() = 0;
  virtual _Key* getKey() = 0;

  virtual ~IIterator() {
  }

protected:
};

template<class _Key, class _Value>
class IPersistence {
public:

  virtual _Value* getByKey(const _Key& key) = 0;
  virtual void set(const _Key& key, const _Value& value) = 0;
  virtual void removeByKey(const _Key& key) = 0;
  virtual void printStat(std::ostream& output) = 0;
  virtual IIterator<_Key, _Value>* createIterator() = 0;
  virtual void putBatch(std::map<_Key, _Value>& batch) = 0;

  virtual ~IPersistence() {
  }

private:
};

struct PersistenceConfig {
  bool create_if_missing = FLAGS_storagePersistenceCreateIfMissing;
  string data_location = FLAGS_storagePersistenceLocation;
};

template<typename _Key, typename _Value>
class IStorage {
public:

  virtual _Value* getByKey(const _Key& key) = 0;
  virtual void set(const _Key& key, const _Value& value) = 0;
  virtual void removeByKey(const _Key& key) = 0;
  virtual void printStat(std::ostream& output) = 0;
  virtual IIterator<_Key, _Value>* createIterator() = 0;
  virtual void putBatch(std::map<_Key, _Value>& batch) = 0;

  virtual ~IStorage() {
  }

private:

};

struct StorageConfig {
  size_t mutexSize = FLAGS_storageStorageMutexCount;
};

template<typename _Key, typename _Value, class keyHasher = std::hash<_Key>>
class BasicStorage: public IStorage<_Key, _Value> {
public:

  //TODO: profiler here

  BasicStorage(StorageConfig config, ICache<_Key, _Value>* cache,
      IPersistence<_Key, _Value>* persis) :
      _cache(cache), _persis(persis), _config(config) {
    mutexArraySize = config.mutexSize;
    mutexs = new std::mutex[mutexArraySize]();
    warmUp();
    cacheMiss = 1;
    totalGet = 1;
  }

  ~BasicStorage() {
    delete[] mutexs;
    delete _cache;
    delete _persis;
  }

  _Value* getByKey(const _Key& key) override
  {
    totalGet++;
    std::lock_guard<std::mutex> lock(getMutexForKey(key));
    auto res = _cache->getByKey(key);
    if (res == nullptr) {
      cacheMiss++;
      res = _persis->getByKey(key);
      if (res != nullptr) {
        _cache->set(key, *res);
      }
    }
    return res;
  }

  void set(const _Key& key, const _Value& value) override
  {
    totalRequest++;
    std::lock_guard<std::mutex> lock(getMutexForKey(key));
    _cache->set(key, value);
    _persis->set(key, value);
  }

  void removeByKey(const _Key& key) override
  {
    totalRequest++;
    std::lock_guard<std::mutex> lock(getMutexForKey(key));
    _cache->removeByKey(key);
    _persis->removeByKey(key);
  }

  IIterator<_Key, _Value>* createIterator() override
  {
    totalRequest++;
    return _persis->createIterator();
  }

  void putBatch(std::map<_Key, _Value>& batch) override
  {
    totalRequest++;
    _persis->putBatch(batch);
  }

  void printStat(std::ostream& output) override
  {
    output << "Cache miss rate: " << 1.0 * cacheMiss / totalGet << endl;
    output << "Total request: " << totalRequest << endl;
    _cache->printStat(output);
    _persis->printStat(output);
  }
private:
  ICache<_Key, _Value>*  _cache;
  IPersistence<_Key, _Value>* _persis;
  StorageConfig _config;
  std::mutex* mutexs;

  std::atomic<unsigned long> cacheMiss;
  std::atomic<unsigned long> totalGet;
  std::atomic<unsigned long> totalRequest;
  uint32_t mutexArraySize;

  void warmUp() {
  }

  std::mutex& getMutexForKey(const _Key& key) {

    int hashIndex = keyHasher()(key);
    int mi = (hashIndex > 0 ? hashIndex : -hashIndex) % mutexArraySize;
    return mutexs[mi];
  }
};

} // back_end
} // vng_wpl
