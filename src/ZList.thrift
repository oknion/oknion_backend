namespace cpp zingme.zlist.thrift
namespace java zingme.zlisti32i32.thrift

typedef i32 ZKey
typedef i32 ZValue

struct ZListItem{
  1: i32 count,
  2: list<ZValue> values,
}

// @count is count of entire list
struct ZListResult{
  1:i32 error,
  2:i32 count,
  3:list<ZValue> data,
}

struct ZCountResult{
  1: i32 error,
  2: i32 count,
}

service ZListService{
  // get @count items from list has key eq @key skip @pos first items
  // if list has less than @pos items, return empty list, if after skip
  // @pos items, our list just has n < count items, return list has n
  // items 
  ZListResult getSlice(1:ZKey key, 2:i32 pos, 3:i32 count);
  
  // same as "getSlice" but in reverse order
  ZListResult rgetSlice(1:ZKey key, 2:i32 pos, 4:i32 count);
  
  // another getSlice function but for multiple key 
  map<ZKey, ZListResult> multiGetSlice(1:list<ZKey> keys, 2:i32 pos, 3:i32 count);
  
  // another rgetSlice function but for multiple key
  map<ZKey, ZListResult> rmultiGetSlice(1:list<ZKey> keys, 2:i32 pos, 4:i32 count);
  
  // This is some kind of silly function design, get @count items from list has
  // key equal @key skip items which stays on front of @fromValue on the list,
  // GOD! If list is not sorted, this function's complexity is O(n) (n is number of
  // items on this list) and if we can't find @fromValue from this list what next?
  // If it's sorted, complexity is O(log(n)) if we use binary search and if we can't
  // find #fromValue we still don't know what to do next. And, how can I know that
  // this list is sorted or not? If I reorder this list every time it gets an item
  // complexity of using best (I think insert sort) algorithm is O(n) include m1
  // compare (find out position) and m2 swap (move remain items to theirs correct 
  // position) which m1 + m2 = n. If I sort list every time we got this kind of
  // request, complexity every request got is O(nlog(n). So I'll not implement those
  // functions
  ///////////////////////////////////////////////////////////////////////////////////
  //ZListResult getSliceFrom(1:ZKey key, 2:ZValue fromValue, 3:i32 pos, 4:i32 count);
  //ZListResult rgetSliceFrom(1:ZKey key, 2:ZValue fromValue, 3:i32 pos, 4:i32 count);
  
  // check if list has key eq @key has @value item or not
  bool checkExist(1:ZKey key, 2:ZValue value);
  
  // same as checkExist but for multiple values
  map<ZValue, bool> checkExists(1:ZKey key, 2:list<ZValue> values);
  
  // same as checkExist but for multiple keys, this is silly too because
  // we have @keys.size() disk access to get response 
  map<ZKey, bool> checkExists2(1:list<ZKey> keys, 2:ZValue value);

  // put @value item to list has key eq @key if list   
  ZCountResult put(1:ZKey key, 2:ZValue value);
  
  // that mean all @keys will have @values items
  map<ZKey, ZCountResult> multiPut(1:list<ZKey> keys, 2:list<ZValue> values);
  
  // remove @value from list has key eq @key
  ZCountResult remove(1:ZKey key, 2:ZValue value);
  
  // remove list has key eq @key
  i32 removeKey(1:ZKey key);
  
  map<ZKey, ZCountResult> multiRemove(1:list<ZKey> keys, 2:list<ZValue> values);

  string getStat(1:i32 type);
}