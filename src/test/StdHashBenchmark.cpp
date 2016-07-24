/*
 * StdHashBenchmark.cpp
 *
 *  Created on: Jun 22, 2016
 *      Author: kienpc
 */

#include <folly/Benchmark.h>
#include <folly/Foreach.h>
#include <string>
#include <iostream>
#include <folly/FBString.h>

using namespace std;
using namespace folly;

string str, smstr;
fbstring fbstr, smfbstr;

BENCHMARK(integerHashBenchmark) {
  FOR_EACH_RANGE(i, 0, -1000)
  {
    auto a = std::hash<int>()(i);
  }
}
BENCHMARK(stringHashBenchmark) {
  FOR_EACH_RANGE(i, 0, 1000)
  {
    auto a = std::hash<string>()(str);
  }
}
BENCHMARK_RELATIVE(fbStringHashBenchmark) {
  FOR_EACH_RANGE(i, 0, 1000)
  {
    auto a = std::hash<fbstring>()(fbstr);
  }
}

BENCHMARK_RELATIVE(smallStringHashBenchmark) {
  FOR_EACH_RANGE(i, 0, 1000)
  {
    auto a = std::hash<string>()(smstr);
  }
}

BENCHMARK_RELATIVE(smallFbStringHashBenchmark) {
  FOR_EACH_RANGE(i, 0, 1000)
  {
    auto a = std::hash<fbstring>()(smfbstr);
  }
}

int main(int agrv, char** agrs) {
  if(!agrs[1]){
    cout << "Enter string to hash\n";
    return 1;
  }
  str = string(agrs[1]);
  fbstr = str;
  string str1 = "im here to win your heart and soul, that my goal";
  smstr = "im here to win your heart and soul, that my goal";
  smfbstr = "im here to win your heart and soul, that my goal";
  std::cout << str.size() << std::endl;
  std::cout << str1.size() << std::endl;
  std::cout << str.size() / str1.size() << std::endl;
  runBenchmarks();

}

