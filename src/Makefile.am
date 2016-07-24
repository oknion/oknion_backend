noinst_PROGRAMS=wpl-back-end.out \
						test-cache.out \
						test-folly-future.out \
						poco-cache-mem-usage.out \
						follyCacheUsage.out \
						ExceptionBenchmark.out \
						ExceptionBenchmarkThrow.out \
						ExceptionBenchmarkThrowOptimize.out \
						testTemplate.out \
						TestSdtHash.out \
						SimpleExceptionBenchmark.out \
						testFollyJson.out \
						testConstructor.out \
						testLockMutex.out \
						testFollyConcurrent.out \
						SmallLockBenchmark.out \
						StdHashBenchmark.out \
						testSerializer.out \
						benchSerialize.out

lib_LIBRARIES = libwpl_storage.a


wplincludedir = $(includedir)/wpl

nobase_wplinclude_HEADERS = storage/FollyCache.h storage/LevelDbPersistence.h storage/Serialize.h storage/Storage.h

libwpl_storage_a_SOURCES = storage/FollyCache.cpp \
						storage/KyotoPersistence.cpp \
						storage/LevelDbPersistence.cpp \
						storage/Storage.cpp

AM_LDFLAGS = -static

wpl_back_end_out_SOURCES = ZListServiceSvImpl.cpp \
						zlist/ZList_constants.cpp \
						zlist/ZListService.cpp \
						zlist/ZList_types.cpp \
						zlist/ZListService.tcc \
						zlist/ZList_types.tcc \
						back-end-v3.cpp
						
wpl_back_end_out_LDADD = libwpl_storage.a

test_cache_out_SOURCES=test/test_cache.cpp test/Benchmark.cpp
test_cache_out_LDADD = 	-lPocoFoundation -lPocoUtil

test_folly_future_out_SOURCES = test/test_folly_future.cpp

poco_cache_mem_usage_out_SOURCES = test/poco_cache_mem_usage.cpp
poco_cache_mem_usage_out_LDADD = -lPocoFoundation -lPocoUtil

follyCacheUsage_out_SOURCES = test/follyCacheUsage.cpp

ExceptionBenchmark_out_SOURCES = test/ExceptionBenchmark.cpp

ExceptionBenchmarkThrow_out_SOURCES = test/ExceptionBenchmark.cpp
ExceptionBenchmarkThrow_out_CPPFLAGS = -D THROW

ExceptionBenchmarkThrowOptimize_out_SOURCES = test/ExceptionBenchmark.cpp
ExceptionBenchmarkThrowOptimize_out_CPPFLAGS = -D THROW -O2 -finline-functions

testTemplate_out_SOURCES = test/testTemplate.cpp

TestSdtHash_out_SOURCES = test/TestStdHash.cpp

SimpleExceptionBenchmark_out_SOURCES = test/SimpleExceptionBenchmark.cpp

testFollyJson_out_SOURCES = test/testFollyJson.cpp

testConstructor_out_SOURCES = test/testConstructor.cpp

testLockMutex_out_SOURCES = test/testLockMutex.cpp test/Benchmark.cpp
testLockMutex_out_LDADD = -lPocoFoundation -lPocoUtil

testFollyConcurrent_out_SOURCES = test/testFollyConcurrent.cpp

SmallLockBenchmark_out_SOURCES = test/SmallLockBenchmark.cpp test/Benchmark.cpp

StdHashBenchmark_out_SOURCES = test/StdHashBenchmark.cpp test/Benchmark.cpp

testSerializer_out_SOURCES = test/testSerializer.cpp test/Benchmark.cpp
benchSerialize_out_SOURCES = test/benchSerialize.cpp zlist/ZList_types.cpp
benchSerialize_out_LDADD = -lfollybenchmark libwpl_storage.a


