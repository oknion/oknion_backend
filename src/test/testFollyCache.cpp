/*
 * testFollyCache.cpp
 *
 *  Created on: Jun 28, 2016
 *      Author: kienpc
 */

#include "storage/FollyCache.h"
#include <folly/FBString.h>
#include <iostream>
#include <gtest/gtest.h>

using namespace std;
using namespace vng_wpl::backend;
using namespace folly;
struct KeyStruct {
  int a;
  fbstring b;
  string c;
  int32_t d;
  bool operator ==(const KeyStruct& rhs) const {
    return this->a == rhs.a && this->b == rhs.b && this->c == rhs.c
        && this->d == rhs.d;
  }
};

namespace std {
template<> struct hash<KeyStruct> {
  size_t operator()(const KeyStruct & x) const {
    std::hash<int> ih;
    std::hash<fbstring> fbsh;
    std::hash<string> sh;
    return ih(x.a) + ih(x.d) + sh(x.c) + fbsh(x.b);
  }
};
}

TEST(StorageFollyCache, SanityTest) {
  FollyCache<KeyStruct, fbstring> cache;
  KeyStruct key1;
  key1.a = 1;
  key1.b = "2";
  key1.c = "3";
  key1.d = 4;
  cache.set(key1, "asd");
  ASSERT_EQ("asd", *cache.getByKey(key1));
}

