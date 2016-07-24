/*
 * Storage.cpp
 *
 *  Created on: Jul 5, 2016
 *      Author: kienpc
 */

#include "Storage.h"

inline DEFINE_uint64(storageCacheSize, 300000, "Size of LRU cache");
inline DEFINE_bool(storagePersistenceCreateIfMissing, true,
    "Storage Persistence create database file(s) if not found specified location");
inline DEFINE_string(storagePersistenceLocation, "db",
    "Storage Persistence database file(s) location");
inline DEFINE_uint64(storageStorageMutexCount, 2000,
    "Number of mutexs on storage instance");

