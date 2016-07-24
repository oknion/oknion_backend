/*
 * TestStdHash.cpp
 *
 *  Created on: Jun 14, 2016
 *      Author: kienpc
 */
#include <iostream>
#include <functional>
#include <string>

using namespace std;

class Obj {
public:
  Obj(int a, string b) :
      a(a), b(b) {
  }
  int a;
  string b;
};
namespace std {
template<> struct hash<Obj> {
  size_t operator()(const Obj & x) const {
    return 0;
  }
};
}
int main() {
  std::cout << std::hash<string>()("asldfkjas;dfk") << std::endl;
  std::cout << std::hash<int>()(1) << std::endl;
  std::cout << std::hash<int>()(-1) << std::endl;
  Obj t(1, "");
  std::cout << std::hash<Obj>()(t) << std::endl;
  return 0;
}
