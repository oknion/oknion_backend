/*
 * LevelDbPersistence.h
 *
 *  Created on: Jun 28, 2016
 *      Author: kienpc
 */

#pragma once

#include "Storage.h"
#include <leveldb/db.h>
#include <leveldb/write_batch.h>
#include <leveldb/options.h>
#include <leveldb/filter_policy.h>
#include <leveldb/cache.h>
#include <glog/logging.h>
#include <stdexcept>

DECLARE_int32(levelDbPersistenceMaxOpenFiles);
DECLARE_bool(levelDbPersistenceWriteSync);
DECLARE_int32(levelDbPersistenceFilterPolicy);

namespace vng_wpl {
namespace backend {

struct LevelDbConfig: PersistenceConfig {
  int max_open_files = FLAGS_levelDbPersistenceMaxOpenFiles;
  bool write_sync = FLAGS_levelDbPersistenceWriteSync;
  int filter_policy = FLAGS_levelDbPersistenceFilterPolicy;
};

template<class _Key, class _Value,
  class valueDeseri = ThriftDeserialize<_Value>,
  class keyDeseri = ThriftDeserialize< _Key>
>
class LevelDbIterator;

template<class _Key, class _Value,
    class valueSeri = ThriftSerialize<_Value>,
    class valueDeseri = ThriftDeserialize<_Value>,
    class keySeri = ThriftSerialize<_Key>,
    class keyDeseri = ThriftDeserialize<_Key>
>
class LevelDbPersistence: public IPersistence<_Key, _Value> {
public:
  LevelDbPersistence() :
      LevelDbPersistence(LevelDbConfig()) {
  }

  LevelDbPersistence(LevelDbConfig config) :
      _config(config) {
    openDb();
  }
  ~LevelDbPersistence() {
    delete _db;
  }

  _Value* getByKey(const _Key& key) override
  {
    _Value* resPtr = nullptr;
    std::string keyInString(keySeri_(key));
    leveldb::Slice keySlice(keyInString);

    std::string res;
    leveldb::Status status = _db->Get(leveldb::ReadOptions(), keySlice, &res);
    if (status.ok()) {
      resPtr = valueDeseri_(res);
    }
    return resPtr;
  }

  void set(const _Key& key, const _Value& value) override
  {
    string keyString = keySeri_(key);
    leveldb::Slice keySlice(keyString);
    string valueString = valueSeri_(value);
    leveldb::Slice valueSlice(valueString);
    leveldb::Status status = _db->Put(_write_options, keySlice, valueSlice);
    if (!status.ok()) {
      throw std::runtime_error("Write fail, can't set key");
    }
  }

  void removeByKey(const _Key& key) override
  {
    leveldb::Slice keySlice(keySeri_(key));
    leveldb::Status status = _db->Delete(_write_options, keySlice);
    if (!status.ok()) {
      throw std::runtime_error("Write fail, can't remove key");
    }
  }

  void printStat(std::ostream& output) override
  {
    string tmpStr;
    _db->GetProperty("leveldb.stats", &tmpStr);
    output << tmpStr << endl;
  }


  IIterator<_Key, _Value>* createIterator() override
  {
    auto res = new LevelDbIterator<_Key, _Value, valueDeseri, keyDeseri>(
        _db->NewIterator(leveldb::ReadOptions()));
    return res;
  }

  void putBatch(std::map<_Key, _Value>& batch) override
  {
    leveldb::WriteBatch holder;
    for (auto it = batch.begin(); it != batch.end(); ++it) {
      string keyString = keySeri_(it->first);
      leveldb::Slice keySlice(keyString);
      string valueString = valueSeri_(it->second);
      leveldb::Slice valueSlice(valueString);
      holder.Put(keyString, valueString);
      _db->Write(_write_options, &holder);
    }
  }
private:

  LevelDbConfig _config;
  leveldb::WriteOptions _write_options;
  leveldb::DB* _db;
  valueSeri valueSeri_ = valueSeri();
  valueDeseri valueDeseri_ = valueDeseri();
  keySeri keySeri_ = keySeri();
  keyDeseri keyDeseri_ = keyDeseri();

  void openDb() {

    leveldb::Options _options;

    // compression only useful when data size bigger than disk sector size I THINK
    _options.compression = leveldb::kNoCompression;
    _options.create_if_missing = _config.create_if_missing;
    _options.max_open_files = _config.max_open_files;
    _write_options.sync = _config.write_sync;
    // bloom filer
    _options.filter_policy = leveldb::NewBloomFilterPolicy(
        _config.filter_policy);
    leveldb::DB* db_temp;
    leveldb::Status status = leveldb::DB::Open(_options, _config.data_location,
        &db_temp);
    assert(status.ok());
    _db = db_temp;
  }
};

/**
 * This is NOT a threat-safe class, so do not share it over threads
 * Edit: may be it is. But, miss-using still can occur when you call
 * getKey() then another thread call next() and then you call getValue()
 * BOOOM!!! Shit happened
 */
template<class _Key, class _Value,
    class valueDeseri,
    class keyDeseri
>
class LevelDbIterator: public IIterator<_Key, _Value> {

  friend IIterator<_Key, _Value>* LevelDbPersistence<_Key, _Value>::createIterator();
  template<typename S1, typename S2, typename S3, typename S4>
  friend IIterator<_Key, _Value>* LevelDbPersistence<_Key, _Value, S1, S2, S3,
      S4>::createIterator();
public:

  LevelDbIterator(const LevelDbIterator<_Key, _Value>& that) = delete;

  LevelDbIterator& operator=(const LevelDbIterator& that) = delete;

  void first() override
  {
    std::lock_guard<std::mutex> guard(mut);
    _it->SeekToFirst();
  }

  void next() override
  {
    std::lock_guard<std::mutex> guard(mut);
    _it->Next();
  }

  bool isValid() override
  {
    std::lock_guard<std::mutex> guard(mut);
    return _it->Valid();
  }

  _Value* getValue() override
  {
    std::lock_guard<std::mutex> guard(mut);
    _Value* res;
    if (_it->Valid()) {
      leveldb::Slice valueSlice = _it->value();
      res = valueDeseri_(valueSlice.ToString());
    }
    return res;
  }

  _Key* getKey() override
  {
    std::lock_guard<std::mutex> guard(mut);
    _Key* res;
    if (_it->Valid()) {
      leveldb::Slice keySlice = _it->key();
      res = keyDeseri_(keySlice.ToString());
    }
    return res;
  }

  ~LevelDbIterator() {
    delete _it;
  }

protected:

  /**
   * this constructor take this pointer ownership
   */
  LevelDbIterator(leveldb::Iterator* it) :
      _it(it) {
  }
  leveldb::Iterator* _it;

private:
  std::mutex mut;
  valueDeseri valueDeseri_ = valueDeseri();
  keyDeseri keyDeseri_ = keyDeseri();
};

} // back_end
} // vng_wpl

