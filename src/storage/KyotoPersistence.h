/*
 * KyotoPersistence.h
 *
 *  Created on: Jul 1, 2016
 *      Author: kienpc
 */

#pragma once

#include "kccompare.h"
#include "kcdb.h"
#include "kcpolydb.h"
#include "kchashdb.h"
#include "Storage.h"

//TODO: make it done
namespace vng_wpl {
namespace backend {
struct HashKyotoConfig: PersistenceConfig {

  int8_t tune_alignment = 3; //: sets the power of the alignment of record size.
  int8_t tune_fbp = 10; //: sets the power of the capacity of the free block pool.
  int8_t tune_options = 0; //: sets the optional features.
  int64_t tune_buckets = 20LL * 1000 * 1000; //: sets the number of buckets of the hash table.
  int64_t tune_map = 64LL << 20; //: sets the size of the internal memory - mapped region.
  int64_t tune_defrag = 512; //: sets the unit step number of auto defragmentation.
  kyotocabinet::Compressor* tune_compressor; //: set the data compressor.
};

} //vng_wpl
} //backend
