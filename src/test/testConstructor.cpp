/*
 * testConstructor.cpp
 *
 *  Created on: Jun 17, 2016
 *      Author: kienpc
 */
#include <bits/stdc++.h>

using namespace std;
class A {
public:
  A() {
    cout << "A has been created!" << endl;
  }
};

A returnA() {
  return A();
}

int main(int agrv, char** agrs) {
  A a = returnA();
  return 0;
}

