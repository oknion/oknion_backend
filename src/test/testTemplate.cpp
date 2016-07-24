/*
 * testTemplate.cpp
 *
 *  Created on: Jun 16, 2016
 *      Author: kienpc
 */
#include <iostream>
#include <string>
#include <functional>

using namespace std;

template<typename inType>
struct print {
  void operator()(const inType &a) {
    cout << a << endl;
  }
};
template<> struct print<string> {
  void operator()(const string &a) const {
    cout << "String: " << a << endl;
  }
};
template<typename key, typename value, class keyPrinter = print<key>,
    class valuePrinter = print<value>>
class MyTPL {
public:
  MyTPL(key k, value v) :
      key_(k), value_(v) {
  }
  key key_;
  value value_;
  void print() {
    keyPrinter()(key_);
    valuePrinter()(value_);
  }
};
int main(int agrv, char** agrs) {
  MyTPL<int, string> m(1, "Mouse love rice");
  m.print();
}
