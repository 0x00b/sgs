// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: google/protobuf/unittest_lite_imports_nonlite.proto

#ifndef PROTOBUF_google_2fprotobuf_2funittest_5flite_5fimports_5fnonlite_2eproto_INCLUDED
#define PROTOBUF_google_2fprotobuf_2funittest_5flite_5fimports_5fnonlite_2eproto_INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3005000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3005001 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata_lite.h>
#include <google/protobuf/message_lite.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unittest.pb.h>
// @@protoc_insertion_point(includes)

namespace protobuf_google_2fprotobuf_2funittest_5flite_5fimports_5fnonlite_2eproto {
// Internal implementation detail -- do not use these members.
struct TableStruct {
  static const ::google::protobuf::internal::ParseTableField entries[];
  static const ::google::protobuf::internal::AuxillaryParseTableField aux[];
  static const ::google::protobuf::internal::ParseTable schema[1];
  static const ::google::protobuf::internal::FieldMetadata field_metadata[];
  static const ::google::protobuf::internal::SerializationTable serialization_table[];
  static const ::google::protobuf::uint32 offsets[];
};
void InitDefaultsTestLiteImportsNonliteImpl();
void InitDefaultsTestLiteImportsNonlite();
inline void InitDefaults() {
  InitDefaultsTestLiteImportsNonlite();
}
}  // namespace protobuf_google_2fprotobuf_2funittest_5flite_5fimports_5fnonlite_2eproto
namespace protobuf_unittest {
class TestLiteImportsNonlite;
class TestLiteImportsNonliteDefaultTypeInternal;
extern TestLiteImportsNonliteDefaultTypeInternal _TestLiteImportsNonlite_default_instance_;
}  // namespace protobuf_unittest
namespace google {
namespace protobuf {
template<> ::protobuf_unittest::TestLiteImportsNonlite* Arena::Create< ::protobuf_unittest::TestLiteImportsNonlite>(Arena*);
}  // namespace protobuf
}  // namespace google
namespace protobuf_unittest {

// ===================================================================

class TestLiteImportsNonlite : public ::google::protobuf::MessageLite /* @@protoc_insertion_point(class_definition:protobuf_unittest.TestLiteImportsNonlite) */ {
 public:
  TestLiteImportsNonlite();
  virtual ~TestLiteImportsNonlite();

  TestLiteImportsNonlite(const TestLiteImportsNonlite& from);

  inline TestLiteImportsNonlite& operator=(const TestLiteImportsNonlite& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  TestLiteImportsNonlite(TestLiteImportsNonlite&& from) noexcept
    : TestLiteImportsNonlite() {
    *this = ::std::move(from);
  }

  inline TestLiteImportsNonlite& operator=(TestLiteImportsNonlite&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  inline const ::std::string& unknown_fields() const {
    return _internal_metadata_.unknown_fields();
  }
  inline ::std::string* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields();
  }

  static const TestLiteImportsNonlite& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const TestLiteImportsNonlite* internal_default_instance() {
    return reinterpret_cast<const TestLiteImportsNonlite*>(
               &_TestLiteImportsNonlite_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    0;

  void Swap(TestLiteImportsNonlite* other);
  friend void swap(TestLiteImportsNonlite& a, TestLiteImportsNonlite& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline TestLiteImportsNonlite* New() const PROTOBUF_FINAL {
    return ::google::protobuf::Arena::Create<TestLiteImportsNonlite>(NULL);
  }

  TestLiteImportsNonlite* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL {
    return ::google::protobuf::Arena::Create<TestLiteImportsNonlite>(arena);
  }
  void CheckTypeAndMergeFrom(const ::google::protobuf::MessageLite& from)
    PROTOBUF_FINAL;
  void CopyFrom(const TestLiteImportsNonlite& from);
  void MergeFrom(const TestLiteImportsNonlite& from);
  void Clear() PROTOBUF_FINAL;
  bool IsInitialized() const PROTOBUF_FINAL;

  size_t ByteSizeLong() const PROTOBUF_FINAL;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) PROTOBUF_FINAL;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const PROTOBUF_FINAL;
  void DiscardUnknownFields();
  int GetCachedSize() const PROTOBUF_FINAL { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  void InternalSwap(TestLiteImportsNonlite* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::std::string GetTypeName() const PROTOBUF_FINAL;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // optional .protobuf_unittest.TestAllTypes message = 1;
  bool has_message() const;
  void clear_message();
  static const int kMessageFieldNumber = 1;
  const ::protobuf_unittest::TestAllTypes& message() const;
  ::protobuf_unittest::TestAllTypes* release_message();
  ::protobuf_unittest::TestAllTypes* mutable_message();
  void set_allocated_message(::protobuf_unittest::TestAllTypes* message);

  // optional .protobuf_unittest.TestRequired message_with_required = 2;
  bool has_message_with_required() const;
  void clear_message_with_required();
  static const int kMessageWithRequiredFieldNumber = 2;
  const ::protobuf_unittest::TestRequired& message_with_required() const;
  ::protobuf_unittest::TestRequired* release_message_with_required();
  ::protobuf_unittest::TestRequired* mutable_message_with_required();
  void set_allocated_message_with_required(::protobuf_unittest::TestRequired* message_with_required);

  // @@protoc_insertion_point(class_scope:protobuf_unittest.TestLiteImportsNonlite)
 private:
  void set_has_message();
  void clear_has_message();
  void set_has_message_with_required();
  void clear_has_message_with_required();

  ::google::protobuf::internal::InternalMetadataWithArenaLite _internal_metadata_;
  ::google::protobuf::internal::HasBits<1> _has_bits_;
  mutable int _cached_size_;
  ::protobuf_unittest::TestAllTypes* message_;
  ::protobuf_unittest::TestRequired* message_with_required_;
  friend struct ::protobuf_google_2fprotobuf_2funittest_5flite_5fimports_5fnonlite_2eproto::TableStruct;
  friend void ::protobuf_google_2fprotobuf_2funittest_5flite_5fimports_5fnonlite_2eproto::InitDefaultsTestLiteImportsNonliteImpl();
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// TestLiteImportsNonlite

// optional .protobuf_unittest.TestAllTypes message = 1;
inline bool TestLiteImportsNonlite::has_message() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void TestLiteImportsNonlite::set_has_message() {
  _has_bits_[0] |= 0x00000001u;
}
inline void TestLiteImportsNonlite::clear_has_message() {
  _has_bits_[0] &= ~0x00000001u;
}
inline const ::protobuf_unittest::TestAllTypes& TestLiteImportsNonlite::message() const {
  const ::protobuf_unittest::TestAllTypes* p = message_;
  // @@protoc_insertion_point(field_get:protobuf_unittest.TestLiteImportsNonlite.message)
  return p != NULL ? *p : *reinterpret_cast<const ::protobuf_unittest::TestAllTypes*>(
      &::protobuf_unittest::_TestAllTypes_default_instance_);
}
inline ::protobuf_unittest::TestAllTypes* TestLiteImportsNonlite::release_message() {
  // @@protoc_insertion_point(field_release:protobuf_unittest.TestLiteImportsNonlite.message)
  clear_has_message();
  ::protobuf_unittest::TestAllTypes* temp = message_;
  message_ = NULL;
  return temp;
}
inline ::protobuf_unittest::TestAllTypes* TestLiteImportsNonlite::mutable_message() {
  set_has_message();
  if (message_ == NULL) {
    message_ = ::google::protobuf::Arena::CreateMessage< ::protobuf_unittest::TestAllTypes >(
        GetArenaNoVirtual());
  }
  // @@protoc_insertion_point(field_mutable:protobuf_unittest.TestLiteImportsNonlite.message)
  return message_;
}
inline void TestLiteImportsNonlite::set_allocated_message(::protobuf_unittest::TestAllTypes* message) {
  ::google::protobuf::Arena* message_arena = GetArenaNoVirtual();
  if (message_arena == NULL) {
    delete reinterpret_cast< ::google::protobuf::MessageLite*>(message_);
  }
  if (message) {
    ::google::protobuf::Arena* submessage_arena =
      reinterpret_cast< ::google::protobuf::MessageLite*>(message)->GetArena();
    if (message_arena != submessage_arena) {
      message = ::google::protobuf::internal::GetOwnedMessage(
          message_arena, message, submessage_arena);
    }
    set_has_message();
  } else {
    clear_has_message();
  }
  message_ = message;
  // @@protoc_insertion_point(field_set_allocated:protobuf_unittest.TestLiteImportsNonlite.message)
}

// optional .protobuf_unittest.TestRequired message_with_required = 2;
inline bool TestLiteImportsNonlite::has_message_with_required() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void TestLiteImportsNonlite::set_has_message_with_required() {
  _has_bits_[0] |= 0x00000002u;
}
inline void TestLiteImportsNonlite::clear_has_message_with_required() {
  _has_bits_[0] &= ~0x00000002u;
}
inline const ::protobuf_unittest::TestRequired& TestLiteImportsNonlite::message_with_required() const {
  const ::protobuf_unittest::TestRequired* p = message_with_required_;
  // @@protoc_insertion_point(field_get:protobuf_unittest.TestLiteImportsNonlite.message_with_required)
  return p != NULL ? *p : *reinterpret_cast<const ::protobuf_unittest::TestRequired*>(
      &::protobuf_unittest::_TestRequired_default_instance_);
}
inline ::protobuf_unittest::TestRequired* TestLiteImportsNonlite::release_message_with_required() {
  // @@protoc_insertion_point(field_release:protobuf_unittest.TestLiteImportsNonlite.message_with_required)
  clear_has_message_with_required();
  ::protobuf_unittest::TestRequired* temp = message_with_required_;
  message_with_required_ = NULL;
  return temp;
}
inline ::protobuf_unittest::TestRequired* TestLiteImportsNonlite::mutable_message_with_required() {
  set_has_message_with_required();
  if (message_with_required_ == NULL) {
    message_with_required_ = ::google::protobuf::Arena::CreateMessage< ::protobuf_unittest::TestRequired >(
        GetArenaNoVirtual());
  }
  // @@protoc_insertion_point(field_mutable:protobuf_unittest.TestLiteImportsNonlite.message_with_required)
  return message_with_required_;
}
inline void TestLiteImportsNonlite::set_allocated_message_with_required(::protobuf_unittest::TestRequired* message_with_required) {
  ::google::protobuf::Arena* message_arena = GetArenaNoVirtual();
  if (message_arena == NULL) {
    delete reinterpret_cast< ::google::protobuf::MessageLite*>(message_with_required_);
  }
  if (message_with_required) {
    ::google::protobuf::Arena* submessage_arena =
      reinterpret_cast< ::google::protobuf::MessageLite*>(message_with_required)->GetArena();
    if (message_arena != submessage_arena) {
      message_with_required = ::google::protobuf::internal::GetOwnedMessage(
          message_arena, message_with_required, submessage_arena);
    }
    set_has_message_with_required();
  } else {
    clear_has_message_with_required();
  }
  message_with_required_ = message_with_required;
  // @@protoc_insertion_point(field_set_allocated:protobuf_unittest.TestLiteImportsNonlite.message_with_required)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace protobuf_unittest

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_google_2fprotobuf_2funittest_5flite_5fimports_5fnonlite_2eproto_INCLUDED
