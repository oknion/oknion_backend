/*
 * testFollyJson.cpp
 *
 *  Created on: Jun 17, 2016
 *      Author: kienpc
 */

#include <folly/json.h>
#include <iostream>

int main(int agrv, char** agrs){
  using namespace std;
  using namespace folly;
  folly::json::serialization_opts opts;
  dynamic a = 1;
  cout << folly::json::serialize(a, opts) << endl;

  return 0;
}

