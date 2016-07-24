/*
 * ExceptionBenchmark.cpp
 *
 *  Created on: Jun 16, 2016
 *      Author: kienpc
 */

#include <iostream>
#include <stdexcept>

struct SpaceWaster {
    SpaceWaster(int l, SpaceWaster *p) : level(l), prev(p) {}
    // we want the destructor to do something
    ~SpaceWaster() { prev = 0; }
    bool checkLevel() { return level == 0; }
    int level;
    SpaceWaster *prev;
};

void thrower(SpaceWaster *current) {
    if (current->checkLevel()) throw std::logic_error("some error message goes here\n");
    SpaceWaster next(current->level - 1, current);
    // typical exception-using code doesn't need error return values
    thrower(&next);
    return;
}

int returner(SpaceWaster *current) {
    if (current->checkLevel()) return -1;
    SpaceWaster next(current->level - 1, current);
    // typical exception-free code requires that return values be handled
    if (returner(&next) == -1) return -1;
    return 0;
}

int main() {
    const int repeats = 10001;
    int returns = 0;
    SpaceWaster first(10000, 0);

    for (int i = 0; i < repeats; ++i) {
        #ifdef THROW
            try {
                thrower(&first);
            } catch (std::exception &e) {
                ++returns;
            }
        #else
            returner(&first);
            ++returns;
        #endif
    }
    #ifdef THROW
        std::cout << returns << " exceptions\n";
    #else
        std::cout << returns << " returns\n";
    #endif
}
