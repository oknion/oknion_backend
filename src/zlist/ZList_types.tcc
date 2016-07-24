/**
 * Autogenerated by Thrift
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#pragma once

#include "ZList_types.h"
#include <thrift/lib/cpp/TApplicationException.h>
#include <folly/io/IOBuf.h>
#include <folly/io/IOBufQueue.h>
#include <thrift/lib/cpp/transport/THeader.h>
#include <thrift/lib/cpp2/server/Cpp2ConnContext.h>
#include <thrift/lib/cpp2/GeneratedCodeHelper.h>

#include <thrift/lib/cpp2/protocol/BinaryProtocol.h>
#include <thrift/lib/cpp2/protocol/CompactProtocol.h>
namespace zingme { namespace zlist { namespace thrift { namespace cpp2 {

template <typename T_ZListItem_values_struct_setter>
std::vector< ::zingme::zlist::thrift::cpp2::ZValue>& ZListItem::set_values(T_ZListItem_values_struct_setter&& values_) {
  values = std::forward<T_ZListItem_values_struct_setter>(values_);
  __isset.values = true;
  return values;
}

template <class Protocol_>
uint32_t ZListItem::read(Protocol_* iprot) {
  uint32_t xfer = 0;
  std::string fname;
  apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using apache::thrift::TProtocolException;


  while (true) {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == apache::thrift::protocol::T_STOP) {
      break;
    }
    if (fid == std::numeric_limits<int16_t>::min()) {
      if (fname == "count") {
        fid = 1;
        ftype = apache::thrift::protocol::T_I32;
      }
      else if (fname == "values") {
        fid = 2;
        ftype = apache::thrift::protocol::T_LIST;
      }
    }
    switch (fid) {
      case 1:
      {
        if (ftype == apache::thrift::protocol::T_I32) {
          xfer += iprot->readI32(this->count);
          this->__isset.count = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      }
      case 2:
      {
        if (ftype == apache::thrift::protocol::T_LIST) {
          this->values = std::vector< ::zingme::zlist::thrift::cpp2::ZValue>();
          uint32_t _size0;
          apache::thrift::protocol::TType _etype3;
          xfer += iprot->readListBegin(_etype3, _size0);
          uint32_t _i4;
          if (_size0 == std::numeric_limits<uint32_t>::max()) {
            for (_i4 = 0; iprot->peekList(); _i4++) {
              this->values.resize(_i4 + 1);
              xfer += iprot->readI32(this->values[_i4]);
            }
          }
          else {
            this->values.resize(_size0);
            for (_i4 = 0; _i4 < _size0; ++_i4) {
              xfer += iprot->readI32(this->values[_i4]);
            }
          }
          xfer += iprot->readListEnd();
          this->__isset.values = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      }
      default:
      {
        xfer += iprot->skip(ftype);
        break;
      }
    }
    xfer += iprot->readFieldEnd();
  }
  xfer += iprot->readStructEnd();

  return xfer;
}

template <class Protocol_>
uint32_t ZListItem::serializedSize(Protocol_* prot_) const {
  uint32_t xfer = 0;
  xfer += prot_->serializedStructSize("ZListItem");
  xfer += prot_->serializedFieldSize("count", apache::thrift::protocol::T_I32, 1);
  xfer += prot_->serializedSizeI32(this->count);
  xfer += prot_->serializedFieldSize("values", apache::thrift::protocol::T_LIST, 2);
  xfer += prot_->serializedSizeListBegin(apache::thrift::protocol::T_I32, this->values.size());
  for (auto _iter5 = this->values.begin(); _iter5 != this->values.end(); ++_iter5) {
    xfer += prot_->serializedSizeI32((*_iter5));
  }
  xfer += prot_->serializedSizeListEnd();
  xfer += prot_->serializedSizeStop();
  return xfer;
}

template <class Protocol_>
uint32_t ZListItem::serializedSizeZC(Protocol_* prot_) const {
  uint32_t xfer = 0;
  xfer += prot_->serializedStructSize("ZListItem");
  xfer += prot_->serializedFieldSize("count", apache::thrift::protocol::T_I32, 1);
  xfer += prot_->serializedSizeI32(this->count);
  xfer += prot_->serializedFieldSize("values", apache::thrift::protocol::T_LIST, 2);
  xfer += prot_->serializedSizeListBegin(apache::thrift::protocol::T_I32, this->values.size());
  for (auto _iter6 = this->values.begin(); _iter6 != this->values.end(); ++_iter6) {
    xfer += prot_->serializedSizeI32((*_iter6));
  }
  xfer += prot_->serializedSizeListEnd();
  xfer += prot_->serializedSizeStop();
  return xfer;
}

template <class Protocol_>
uint32_t ZListItem::write(Protocol_* prot_) const {
  uint32_t xfer = 0;
  xfer += prot_->writeStructBegin("ZListItem");
  xfer += prot_->writeFieldBegin("count", apache::thrift::protocol::T_I32, 1);
  xfer += prot_->writeI32(this->count);
  xfer += prot_->writeFieldEnd();
  xfer += prot_->writeFieldBegin("values", apache::thrift::protocol::T_LIST, 2);
  xfer += prot_->writeListBegin(apache::thrift::protocol::T_I32, this->values.size());
  for (auto _iter7 = this->values.begin(); _iter7 != this->values.end(); ++_iter7) {
    xfer += prot_->writeI32((*_iter7));
  }
  xfer += prot_->writeListEnd();
  xfer += prot_->writeFieldEnd();
  xfer += prot_->writeFieldStop();
  xfer += prot_->writeStructEnd();
  return xfer;
}

}}}} // zingme::zlist::thrift::cpp2
namespace apache { namespace thrift {

}} // apache::thrift
namespace zingme { namespace zlist { namespace thrift { namespace cpp2 {

template <typename T_ZListResult_data_struct_setter>
std::vector< ::zingme::zlist::thrift::cpp2::ZValue>& ZListResult::set_data(T_ZListResult_data_struct_setter&& data_) {
  data = std::forward<T_ZListResult_data_struct_setter>(data_);
  __isset.data = true;
  return data;
}

template <class Protocol_>
uint32_t ZListResult::read(Protocol_* iprot) {
  uint32_t xfer = 0;
  std::string fname;
  apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using apache::thrift::TProtocolException;


  while (true) {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == apache::thrift::protocol::T_STOP) {
      break;
    }
    if (fid == std::numeric_limits<int16_t>::min()) {
      if (fname == "error") {
        fid = 1;
        ftype = apache::thrift::protocol::T_I32;
      }
      else if (fname == "count") {
        fid = 2;
        ftype = apache::thrift::protocol::T_I32;
      }
      else if (fname == "data") {
        fid = 3;
        ftype = apache::thrift::protocol::T_LIST;
      }
    }
    switch (fid) {
      case 1:
      {
        if (ftype == apache::thrift::protocol::T_I32) {
          xfer += iprot->readI32(this->error);
          this->__isset.error = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      }
      case 2:
      {
        if (ftype == apache::thrift::protocol::T_I32) {
          xfer += iprot->readI32(this->count);
          this->__isset.count = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      }
      case 3:
      {
        if (ftype == apache::thrift::protocol::T_LIST) {
          this->data = std::vector< ::zingme::zlist::thrift::cpp2::ZValue>();
          uint32_t _size8;
          apache::thrift::protocol::TType _etype11;
          xfer += iprot->readListBegin(_etype11, _size8);
          uint32_t _i12;
          if (_size8 == std::numeric_limits<uint32_t>::max()) {
            for (_i12 = 0; iprot->peekList(); _i12++) {
              this->data.resize(_i12 + 1);
              xfer += iprot->readI32(this->data[_i12]);
            }
          }
          else {
            this->data.resize(_size8);
            for (_i12 = 0; _i12 < _size8; ++_i12) {
              xfer += iprot->readI32(this->data[_i12]);
            }
          }
          xfer += iprot->readListEnd();
          this->__isset.data = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      }
      default:
      {
        xfer += iprot->skip(ftype);
        break;
      }
    }
    xfer += iprot->readFieldEnd();
  }
  xfer += iprot->readStructEnd();

  return xfer;
}

template <class Protocol_>
uint32_t ZListResult::serializedSize(Protocol_* prot_) const {
  uint32_t xfer = 0;
  xfer += prot_->serializedStructSize("ZListResult");
  xfer += prot_->serializedFieldSize("error", apache::thrift::protocol::T_I32, 1);
  xfer += prot_->serializedSizeI32(this->error);
  xfer += prot_->serializedFieldSize("count", apache::thrift::protocol::T_I32, 2);
  xfer += prot_->serializedSizeI32(this->count);
  xfer += prot_->serializedFieldSize("data", apache::thrift::protocol::T_LIST, 3);
  xfer += prot_->serializedSizeListBegin(apache::thrift::protocol::T_I32, this->data.size());
  for (auto _iter13 = this->data.begin(); _iter13 != this->data.end(); ++_iter13) {
    xfer += prot_->serializedSizeI32((*_iter13));
  }
  xfer += prot_->serializedSizeListEnd();
  xfer += prot_->serializedSizeStop();
  return xfer;
}

template <class Protocol_>
uint32_t ZListResult::serializedSizeZC(Protocol_* prot_) const {
  uint32_t xfer = 0;
  xfer += prot_->serializedStructSize("ZListResult");
  xfer += prot_->serializedFieldSize("error", apache::thrift::protocol::T_I32, 1);
  xfer += prot_->serializedSizeI32(this->error);
  xfer += prot_->serializedFieldSize("count", apache::thrift::protocol::T_I32, 2);
  xfer += prot_->serializedSizeI32(this->count);
  xfer += prot_->serializedFieldSize("data", apache::thrift::protocol::T_LIST, 3);
  xfer += prot_->serializedSizeListBegin(apache::thrift::protocol::T_I32, this->data.size());
  for (auto _iter14 = this->data.begin(); _iter14 != this->data.end(); ++_iter14) {
    xfer += prot_->serializedSizeI32((*_iter14));
  }
  xfer += prot_->serializedSizeListEnd();
  xfer += prot_->serializedSizeStop();
  return xfer;
}

template <class Protocol_>
uint32_t ZListResult::write(Protocol_* prot_) const {
  uint32_t xfer = 0;
  xfer += prot_->writeStructBegin("ZListResult");
  xfer += prot_->writeFieldBegin("error", apache::thrift::protocol::T_I32, 1);
  xfer += prot_->writeI32(this->error);
  xfer += prot_->writeFieldEnd();
  xfer += prot_->writeFieldBegin("count", apache::thrift::protocol::T_I32, 2);
  xfer += prot_->writeI32(this->count);
  xfer += prot_->writeFieldEnd();
  xfer += prot_->writeFieldBegin("data", apache::thrift::protocol::T_LIST, 3);
  xfer += prot_->writeListBegin(apache::thrift::protocol::T_I32, this->data.size());
  for (auto _iter15 = this->data.begin(); _iter15 != this->data.end(); ++_iter15) {
    xfer += prot_->writeI32((*_iter15));
  }
  xfer += prot_->writeListEnd();
  xfer += prot_->writeFieldEnd();
  xfer += prot_->writeFieldStop();
  xfer += prot_->writeStructEnd();
  return xfer;
}

}}}} // zingme::zlist::thrift::cpp2
namespace apache { namespace thrift {

}} // apache::thrift
namespace zingme { namespace zlist { namespace thrift { namespace cpp2 {

template <class Protocol_>
uint32_t ZCountResult::read(Protocol_* iprot) {
  uint32_t xfer = 0;
  std::string fname;
  apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using apache::thrift::TProtocolException;


  while (true) {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == apache::thrift::protocol::T_STOP) {
      break;
    }
    if (fid == std::numeric_limits<int16_t>::min()) {
      if (fname == "error") {
        fid = 1;
        ftype = apache::thrift::protocol::T_I32;
      }
      else if (fname == "count") {
        fid = 2;
        ftype = apache::thrift::protocol::T_I32;
      }
    }
    switch (fid) {
      case 1:
      {
        if (ftype == apache::thrift::protocol::T_I32) {
          xfer += iprot->readI32(this->error);
          this->__isset.error = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      }
      case 2:
      {
        if (ftype == apache::thrift::protocol::T_I32) {
          xfer += iprot->readI32(this->count);
          this->__isset.count = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      }
      default:
      {
        xfer += iprot->skip(ftype);
        break;
      }
    }
    xfer += iprot->readFieldEnd();
  }
  xfer += iprot->readStructEnd();

  return xfer;
}

template <class Protocol_>
uint32_t ZCountResult::serializedSize(Protocol_* prot_) const {
  uint32_t xfer = 0;
  xfer += prot_->serializedStructSize("ZCountResult");
  xfer += prot_->serializedFieldSize("error", apache::thrift::protocol::T_I32, 1);
  xfer += prot_->serializedSizeI32(this->error);
  xfer += prot_->serializedFieldSize("count", apache::thrift::protocol::T_I32, 2);
  xfer += prot_->serializedSizeI32(this->count);
  xfer += prot_->serializedSizeStop();
  return xfer;
}

template <class Protocol_>
uint32_t ZCountResult::serializedSizeZC(Protocol_* prot_) const {
  uint32_t xfer = 0;
  xfer += prot_->serializedStructSize("ZCountResult");
  xfer += prot_->serializedFieldSize("error", apache::thrift::protocol::T_I32, 1);
  xfer += prot_->serializedSizeI32(this->error);
  xfer += prot_->serializedFieldSize("count", apache::thrift::protocol::T_I32, 2);
  xfer += prot_->serializedSizeI32(this->count);
  xfer += prot_->serializedSizeStop();
  return xfer;
}

template <class Protocol_>
uint32_t ZCountResult::write(Protocol_* prot_) const {
  uint32_t xfer = 0;
  xfer += prot_->writeStructBegin("ZCountResult");
  xfer += prot_->writeFieldBegin("error", apache::thrift::protocol::T_I32, 1);
  xfer += prot_->writeI32(this->error);
  xfer += prot_->writeFieldEnd();
  xfer += prot_->writeFieldBegin("count", apache::thrift::protocol::T_I32, 2);
  xfer += prot_->writeI32(this->count);
  xfer += prot_->writeFieldEnd();
  xfer += prot_->writeFieldStop();
  xfer += prot_->writeStructEnd();
  return xfer;
}

}}}} // zingme::zlist::thrift::cpp2
namespace apache { namespace thrift {

}} // apache::thrift
namespace zingme { namespace zlist { namespace thrift { namespace cpp2 {

}}}} // zingme::zlist::thrift::cpp2