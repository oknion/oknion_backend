/*
 * SimpleExceptionBenchmark.cpp
 *
 *  Created on: Jun 16, 2016
 *      Author: kienpc
 */

#include <iostream>
#include <stdexcept>
int main() {
  for (int i = 0; i < 1000000; i++) {
    try {

      throw std::logic_error("some error message goes here\n");
    } catch (std::exception &e) {

    }
  }
}
