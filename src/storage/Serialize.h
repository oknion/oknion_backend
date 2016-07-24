/*
 * Serialize.h
 *
 *  Created on: Jun 22, 2016
 *      Author: kienpc
 */

#pragma once

#include <iomanip>
#include <string>
#include <thrift/lib/cpp2/protocol/CompactProtocol.h>
#include <thrift/lib/cpp2/protocol/BinaryProtocol.h>

namespace vng_wpl {
namespace backend {

using namespace ::std;
using namespace ::apache::thrift;

template<typename inType>
struct ThriftCompactSerialize {

  string operator()(const inType &input) {
    auto comProt = CompactProtocolWriter();
    auto queue = IOBufQueue();
    comProt.setOutput(&queue);
    input.write(&comProt);
    string out;
    queue.appendToString(out);
    return out;
  }
};

template<typename Item>
struct ThriftCompactDeserialize {

  Item* operator()(const string &input) {
    Item* item = new Item();
    auto reader = CompactProtocolReader();
    auto buff = IOBuf::wrapBufferAsValue(input.c_str(), input.size());
    reader.setInput(&buff);
    item->read(&reader);
    return item;
  }
};

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

template<typename Item>
struct ThriftBinaryDeserialize {

  Item* operator()(const string &input) {
    Item* item = new Item();
    auto reader = BinaryProtocolReader();
    auto buff = IOBuf::wrapBufferAsValue(input.c_str(), input.size());
    reader.setInput(&buff);
    item->read(&reader);
    return item;
  }
};


template<typename inType>
struct ThriftBinarySerialize {

  string operator()(const inType &input) {
    auto comProt = BinaryProtocolWriter();
    auto queue = IOBufQueue();
    comProt.setOutput(&queue);
    input.write(&comProt);
    string out;
    queue.appendToString(out);
    return out;
  }
};

template<typename inType>
using ThriftSerialize = ThriftCompactSerialize<inType>;

template<typename inType>
using ThriftDeserialize = ThriftCompactDeserialize<inType>;

template<>
struct ThriftBinarySerialize<int32_t> {
  string operator()(const int32_t& input) {
    stringstream ss;
    ss << std::setfill('0') << std::setw(sizeof(input) * 2) << std::hex
        << input;
    return ss.str();
  }
};

template<>
struct ThriftBinaryDeserialize<int32_t> {
  int32_t* operator()(const string &input) {
    uint32_t x;
    std::stringstream ss;
    ss << std::hex << input;
    ss >> x;
    return new int32_t(static_cast<uint32_t>(x));
  }
};

template<>
struct ThriftBinarySerialize<int64_t> {
  string operator()(const int64_t& input) {
    stringstream ss;
    ss << std::setfill('0') << std::setw(sizeof(input) * 2) << std::hex
        << input;
    return ss.str();
  }
};

template<>
struct ThriftBinaryDeserialize<int64_t> {
  int64_t* operator()(const string& input) {
    uint64_t x;
    std::stringstream ss;
    ss << std::hex << input;
    ss >> x;
    return new int64_t(static_cast<int64_t>(x));
  }
};

template<>
struct ThriftBinarySerialize<int16_t> {
  string operator()(const int16_t& input) {
    stringstream ss;
    ss << std::setfill('0') << std::setw(sizeof(input) * 2) << std::hex
        << input;
    return ss.str();
  }
};

template<>
struct ThriftBinaryDeserialize<int16_t> {
  int16_t* operator()(const string &input) {
    uint16_t x;
    std::stringstream ss;
    ss << std::hex << input;
    ss >> x;
    return new int16_t(static_cast<int16_t>(x));
  }
};

/// compact

template<>
struct ThriftCompactSerialize<int32_t> {
  string operator()(const int32_t& input) {
    stringstream ss;
    ss << std::setfill('0') << std::setw(sizeof(input) * 2) << std::hex
        << input;
    return ss.str();
  }
};

template<>
struct ThriftCompactDeserialize<int32_t> {
  int32_t* operator()(const string &input) {
    uint32_t x;
    std::stringstream ss;
    ss << std::hex << input;
    ss >> x;
    return new int32_t(static_cast<uint32_t>(x));
  }
};

template<>
struct ThriftCompactSerialize<int64_t> {
  string operator()(const int64_t& input) {
    stringstream ss;
    ss << std::setfill('0') << std::setw(sizeof(input) * 2) << std::hex
        << input;
    return ss.str();
  }
};

template<>
struct ThriftCompactDeserialize<int64_t> {
  int64_t* operator()(const string& input) {
    uint64_t x;
    std::stringstream ss;
    ss << std::hex << input;
    ss >> x;
    return new int64_t(static_cast<int64_t>(x));
  }
};

template<>
struct ThriftCompactSerialize<int16_t> {
  string operator()(const int16_t& input) {
    stringstream ss;
    ss << std::setfill('0') << std::setw(sizeof(input) * 2) << std::hex
        << input;
    return ss.str();
  }
};

template<>
struct ThriftCompactDeserialize<int16_t> {
  int16_t* operator()(const string &input) {
    uint16_t x;
    std::stringstream ss;
    ss << std::hex << input;
    ss >> x;
    return new int16_t(static_cast<int16_t>(x));
  }
};

} // back_end
} // vng_wpl
