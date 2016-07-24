/*
 * ZListServiceSvImpl.h
 *
 *  Created on: Jul 4, 2016
 *      Author: kienpc
 */

#pragma once

#include "zlist/ZListService.h"
#include <thrift/lib/cpp2/async/AsyncProcessor.h>
#include "storage/Storage.h"
#include <gflags/gflags.h>
#include <functional>
#include <cstdlib>
#include <mutex>
#include <sstream>
#include <algorithm>

using namespace apache::thrift;
using namespace zingme::zlist::thrift::cpp2;
using namespace vng_wpl::backend;

DECLARE_uint64(handlerMutexCount);

//template<class T>
//using CallBack = std::unique_ptr<apache::thrift::HandlerCallback<std::unique_ptr<T>>>;

/**
 * I'm just too stupid to implement like this, implement [func_name] instead of
 * [func_name] like normal thrift server, we usually implement [func_name] method when
 * we use same thread call inside it (ie: call other thread). But this is a good example
 * to next level of back-end which use fb-thrift and call other service
 * EDIT: I already changed it to normal style
 */
class ZListServiceSvImpl: public ZListServiceSvIf {
public:
  ZListServiceSvImpl() = delete;
  ZListServiceSvImpl(const ZListServiceSvImpl&) = delete;

  ZListServiceSvImpl(IStorage<ZKey, ZListItem>* storage,
      function<size_t(const ZKey&)> keyHash = std::hash<ZKey>());
  void getSlice(ZListResult& _return, ZKey key, int32_t pos, int32_t count)
      override;
  void rgetSlice(ZListResult& _return, ZKey key, int32_t pos, int32_t count)
      override;
  void multiGetSlice(std::map<ZKey, ZListResult>& _return,
      std::unique_ptr<std::vector<ZKey>> keys, int32_t pos, int32_t count)
          override;
  void rmultiGetSlice(std::map<ZKey, ZListResult>& _return,
      std::unique_ptr<std::vector<ZKey>> keys, int32_t pos, int32_t count)
          override;
  bool checkExist(ZKey key, ZValue value) override;
  void checkExists(std::map<ZValue, bool>& _return, ZKey key,
      std::unique_ptr<std::vector<ZValue>> values) override;
  void checkExists2(std::map<ZKey, bool>& _return,
      std::unique_ptr<std::vector<ZKey>> keys, ZValue value) override;
  void put(ZCountResult& _return, ZKey key, ZValue value) override;
  void multiPut(std::map<ZKey, ZCountResult>& _return,
      std::unique_ptr<std::vector<ZKey>> keys,
      std::unique_ptr<std::vector<ZValue>> values) override;
  void remove(ZCountResult& _return, ZKey key, ZValue value) override;
  bool removeKey(ZKey key) override;
  void multiRemove(std::map<ZKey, ZCountResult>& _return,
      std::unique_ptr<std::vector<ZKey>> keys,
      std::unique_ptr<std::vector<ZValue>> values) override;
  void getStat(std::string& _return, int32_t type) override;

  ~ZListServiceSvImpl();

private:

  IStorage<ZKey, ZListItem>* storage;
  std::mutex* mutexArr;
  function<size_t(const ZKey&)> keyHash;
  std::mutex& getMutex(const ZKey& key);
};

