/*
 * LevelDbPersistence.cpp
 *
 *  Created on: Jul 5, 2016
 *      Author: kienpc
 */

#include "LevelDbPersistence.h"


inline DEFINE_int32(levelDbPersistenceMaxOpenFiles, 1000,
    "Max files will be opened by LevelDb");
inline DEFINE_bool(levelDbPersistenceWriteSync, false,
    "Max files will be opened by LevelDb");
inline DEFINE_int32(levelDbPersistenceFilterPolicy, 10,
    " Bloom filter based filtering relies on keeping some number of bits of data in memory per key");
