/*
 * ZListServiceSvImpl.cpp
 *
 *  Created on: Jul 8, 2016
 *      Author: kienpc
 */
#include "ZListServiceSvImpl.h"

DEFINE_uint64(handlerMutexCount, 1000, "ZListServiceSvImpl mutex count");

ZListServiceSvImpl::ZListServiceSvImpl(IStorage<ZKey, ZListItem>* storage,
    function<size_t(const ZKey&)> keyHash = std::hash<ZKey>()) :
    storage(storage), keyHash(keyHash) {
  mutexArr = new std::mutex[FLAGS_handlerMutexCount]();
}

void ZListServiceSvImpl::getSlice(ZListResult& _return, ZKey key, int32_t pos,
    int32_t count) {
  auto ptr = storage->getByKey(key);
  if (ptr != nullptr) {
    _return.count = ptr->count;
    _return.data.reserve(std::min(count, _return.count - pos));
    pos = pos > 0 ? pos : 0;
    pos = pos > _return.count ? _return.count : pos;
    for (auto it = ptr->values.begin() + pos; it != ptr->values.end(); ++it) {
      _return.data.push_back(*it);
    }
  } else {
    _return.error = -1;
  }
  delete ptr;
}
void ZListServiceSvImpl::rgetSlice(ZListResult& _return, ZKey key, int32_t pos,
    int32_t count) {
  auto ptr = storage->getByKey(key);
  if (ptr != nullptr) {
    _return.count = ptr->count;
    _return.data.reserve(std::min(count, _return.count - pos));
    pos = pos > 0 ? pos : 0;
    pos = pos > _return.count ? _return.count : pos;
    for (auto it = ptr->values.rbegin() + pos; it != ptr->values.rend(); ++it) {
      _return.data.push_back(*it);
    }
  } else {
    _return.error = -1;
  }
  delete ptr;
}
void ZListServiceSvImpl::multiGetSlice(std::map<ZKey, ZListResult>& _return,
    std::unique_ptr<std::vector<ZKey>> keys, int32_t pos, int32_t count) {
  for (auto it = keys->begin(); it != keys->end(); ++it) {
    auto key = *it;
    ZListResult zlr;
    getSlice(zlr, key, pos, count);
    _return.insert(std::make_pair(key, zlr));
  }
}
void ZListServiceSvImpl::rmultiGetSlice(std::map<ZKey, ZListResult>& _return,
    std::unique_ptr<std::vector<ZKey>> keys, int32_t pos, int32_t count) {
  for (auto it = keys->begin(); it != keys->end(); ++it) {
    auto key = *it;
    ZListResult zlr;
    rgetSlice(zlr, key, pos, count);
    _return.insert(std::make_pair(key, zlr));
  }
}
bool ZListServiceSvImpl::checkExist(ZKey key, ZValue value) {
  bool res = false;
  auto valuePtr = storage->getByKey(key);
  if (valuePtr != nullptr) {
    auto resIt = std::find(valuePtr->values.begin(), valuePtr->values.end(),
        value);
    if (resIt != valuePtr->values.end()) {
      res = true;
    }
  }
  delete valuePtr;
  return res;
}
void ZListServiceSvImpl::checkExists(std::map<ZValue, bool>& _return, ZKey key,
    std::unique_ptr<std::vector<ZValue>> values) {
  for (auto it = values->begin(); it != values->end(); it++) {
    _return.insert(std::make_pair(*it, this->checkExist(key, *it)));
  }
}
void ZListServiceSvImpl::checkExists2(std::map<ZKey, bool>& _return,
    std::unique_ptr<std::vector<ZKey>> keys, ZValue value) {
  for (auto it = keys->begin(); it != keys->end(); it++) {
    _return.insert(std::make_pair(*it, this->checkExist(*it, value)));
  }
}
void ZListServiceSvImpl::put(ZCountResult& _return, ZKey key, ZValue value) {
  std::lock_guard<std::mutex> l(getMutex(key));
  auto valuePtr = storage->getByKey(key);
  if (valuePtr == nullptr) {
    valuePtr = new ZListItem();
  }
  valuePtr->count++;
  valuePtr->values.push_back(value);
  storage->set(key, *valuePtr);
  _return.count=valuePtr->count;
  _return.error = 0;
  delete valuePtr;
}
void ZListServiceSvImpl::multiPut(std::map<ZKey, ZCountResult>& _return,
    std::unique_ptr<std::vector<ZKey>> keys,
    std::unique_ptr<std::vector<ZValue>> values) {
  for (auto itK = keys->begin(); itK != keys->end(); ++itK) {
    ZCountResult rt;
    for (auto itV = keys->begin(); itV != keys->end(); ++itV) {
      put(rt, *itK, *itV);
    }
    _return.insert(std::make_pair(*itK, rt));
  }
}
void ZListServiceSvImpl::remove(ZCountResult& _return, ZKey key, ZValue value) {
  std::lock_guard<std::mutex> l(getMutex(key));

}
bool ZListServiceSvImpl::removeKey(ZKey key) {
  std::lock_guard<std::mutex> l(getMutex(key));
}
void ZListServiceSvImpl::multiRemove(std::map<ZKey, ZCountResult>& _return,
    std::unique_ptr<std::vector<ZKey>> keys,
    std::unique_ptr<std::vector<ZValue>> values) {
}
void ZListServiceSvImpl::getStat(std::string& _return, int32_t type) {
  std::ostringstream s;
  storage->printStat(s);
  _return = s.str();
}

std::mutex& ZListServiceSvImpl::getMutex(const ZKey& key) {
  return mutexArr[keyHash % FLAGS_handlerMutexCount];
}

ZListServiceSvImpl::~ZListServiceSvImpl() {
  delete storage;
  delete mutexArr;
}

