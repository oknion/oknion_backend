/*
 * FollyCache.cpp
 *
 *  Created on: Jul 5, 2016
 *      Author: kienpc
 */
/**
 * So, now you wondering why the hell I created this file right?
 * Because if I define gflags variable in header file and get rid
 * of this file, we will get multiple definition of `***` error.
 * I could not find out other better solution so I used this trick.
 * FIXME: get rid of this kind of file
 */

#include "FollyCache.h"

DEFINE_int64(storageCacheClearSize, 10,
    "Number item folly LRU cache will evict to create space when reach limit size");

