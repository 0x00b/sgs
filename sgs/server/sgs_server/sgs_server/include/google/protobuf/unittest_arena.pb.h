// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: google/protobuf/unittest_arena.proto

#ifndef PROTOBUF_google_2fprotobuf_2funittest_5farena_2eproto_INCLUDED
#define PROTOBUF_google_2fprotobuf_2funittest_5farena_2eproto_INCLUDED

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
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
#include <google/protobuf/unittest_no_arena_import.pb.h>
// @@protoc_insertion_point(includes)

namespace protobuf_google_2fprotobuf_2funittest_5farena_2eproto {
// Internal implementation detail -- do not use these members.
struct TableStruct {
  static const ::google::protobuf::internal::ParseTableField entries[];
  static const ::google::protobuf::internal::AuxillaryParseTableField aux[];
  static const ::google::protobuf::internal::ParseTable schema[2];
  static const ::google::protobuf::internal::FieldMetadata field_metadata[];
  static const ::google::protobuf::internal::SerializationTable serialization_table[];
  static const ::google::protobuf::uint32 offsets[];
};
void AddDescriptors();
void InitDefaultsNestedMessageImpl();
void InitDefaultsNestedMessage();
void InitDefaultsArenaMessageImpl();
void InitDefaultsArenaMessage();
inline void InitDefaults() {
  InitDefaultsNestedMessage();
  InitDefaultsArenaMessage();
}
}  // namespace protobuf_google_2fprotobuf_2funittest_5farena_2eproto
namespace proto2_arena_unittest {
class ArenaMessage;
class ArenaMessageDefaultTypeInternal;
extern ArenaMessageDefaultTypeInternal _ArenaMessage_default_instance_;
class NestedMessage;
class NestedMessageDefaultTypeInternal;
extern NestedMessageDefaultTypeInternal _NestedMessage_default_instance_;
}  // namespace proto2_arena_unittest
namespace google {
namespace protobuf {
template<> ::proto2_arena_unittest::ArenaMessage* Arena::CreateMessage< ::proto2_arena_unittest::ArenaMessage>(Arena*);
template<> ::proto2_arena_unittest::NestedMessage* Arena::CreateMessage< ::proto2_arena_unittest::NestedMessage>(Arena*);
}  // namespace protobuf
}  // namespace google
namespace proto2_arena_unittest {

// ===================================================================

class NestedMessage : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:proto2_arena_unittest.NestedMessage) */ {
 public:
  NestedMessage();
  virtual ~NestedMessage();

  NestedMessage(const NestedMessage& from);

  inline NestedMessage& operator=(const NestedMessage& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  NestedMessage(NestedMessage&& from) noexcept
    : NestedMessage() {
    *this = ::std::move(from);
  }

  inline NestedMessage& operator=(NestedMessage&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields();
  }
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields();
  }

  inline ::google::protobuf::Arena* GetArena() const PROTOBUF_FINAL {
    return GetArenaNoVirtual();
  }
  inline void* GetMaybeArenaPointer() const PROTOBUF_FINAL {
    return MaybeArenaPtr();
  }
  static const ::google::protobuf::Descriptor* descriptor();
  static const NestedMessage& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const NestedMessage* internal_default_instance() {
    return reinterpret_cast<const NestedMessage*>(
               &_NestedMessage_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    0;

  void UnsafeArenaSwap(NestedMessage* other);
  void Swap(NestedMessage* other);
  friend void swap(NestedMessage& a, NestedMessage& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline NestedMessage* New() const PROTOBUF_FINAL {
    return ::google::protobuf::Arena::CreateMessage<NestedMessage>(NULL);
  }

  NestedMessage* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL {
    return ::google::protobuf::Arena::CreateMessage<NestedMessage>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const NestedMessage& from);
  void MergeFrom(const NestedMessage& from);
  void Clear() PROTOBUF_FINAL;
  bool IsInitialized() const PROTOBUF_FINAL;

  size_t ByteSizeLong() const PROTOBUF_FINAL;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) PROTOBUF_FINAL;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const PROTOBUF_FINAL;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const PROTOBUF_FINAL;
  int GetCachedSize() const PROTOBUF_FINAL { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const PROTOBUF_FINAL;
  void InternalSwap(NestedMessage* other);
  protected:
  explicit NestedMessage(::google::protobuf::Arena* arena);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::google::protobuf::Arena* arena);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return _internal_metadata_.arena();
  }
  inline void* MaybeArenaPtr() const {
    return _internal_metadata_.raw_arena_ptr();
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const PROTOBUF_FINAL;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // optional int32 d = 1;
  bool has_d() const;
  void clear_d();
  static const int kDFieldNumber = 1;
  ::google::protobuf::int32 d() const;
  void set_d(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:proto2_arena_unittest.NestedMessage)
 private:
  void set_has_d();
  void clear_has_d();

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  template <typename T> friend class ::google::protobuf::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::google::protobuf::internal::HasBits<1> _has_bits_;
  mutable int _cached_size_;
  ::google::protobuf::int32 d_;
  friend struct ::protobuf_google_2fprotobuf_2funittest_5farena_2eproto::TableStruct;
  friend void ::protobuf_google_2fprotobuf_2funittest_5farena_2eproto::InitDefaultsNestedMessageImpl();
};
// -------------------------------------------------------------------

class ArenaMessage : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:proto2_arena_unittest.ArenaMessage) */ {
 public:
  ArenaMessage();
  virtual ~ArenaMessage();

  ArenaMessage(const ArenaMessage& from);

  inline ArenaMessage& operator=(const ArenaMessage& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  ArenaMessage(ArenaMessage&& from) noexcept
    : ArenaMessage() {
    *this = ::std::move(from);
  }

  inline ArenaMessage& operator=(ArenaMessage&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields();
  }
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields();
  }

  inline ::google::protobuf::Arena* GetArena() const PROTOBUF_FINAL {
    return GetArenaNoVirtual();
  }
  inline void* GetMaybeArenaPointer() const PROTOBUF_FINAL {
    return MaybeArenaPtr();
  }
  static const ::google::protobuf::Descriptor* descriptor();
  static const ArenaMessage& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const ArenaMessage* internal_default_instance() {
    return reinterpret_cast<const ArenaMessage*>(
               &_ArenaMessage_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    1;

  void UnsafeArenaSwap(ArenaMessage* other);
  void Swap(ArenaMessage* other);
  friend void swap(ArenaMessage& a, ArenaMessage& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline ArenaMessage* New() const PROTOBUF_FINAL {
    return ::google::protobuf::Arena::CreateMessage<ArenaMessage>(NULL);
  }

  ArenaMessage* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL {
    return ::google::protobuf::Arena::CreateMessage<ArenaMessage>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const ArenaMessage& from);
  void MergeFrom(const ArenaMessage& from);
  void Clear() PROTOBUF_FINAL;
  bool IsInitialized() const PROTOBUF_FINAL;

  size_t ByteSizeLong() const PROTOBUF_FINAL;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) PROTOBUF_FINAL;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const PROTOBUF_FINAL;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const PROTOBUF_FINAL;
  int GetCachedSize() const PROTOBUF_FINAL { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const PROTOBUF_FINAL;
  void InternalSwap(ArenaMessage* other);
  protected:
  explicit ArenaMessage(::google::protobuf::Arena* arena);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::google::protobuf::Arena* arena);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return _internal_metadata_.arena();
  }
  inline void* MaybeArenaPtr() const {
    return _internal_metadata_.raw_arena_ptr();
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const PROTOBUF_FINAL;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // repeated .proto2_arena_unittest.NestedMessage repeated_nested_message = 1;
  int repeated_nested_message_size() const;
  void clear_repeated_nested_message();
  static const int kRepeatedNestedMessageFieldNumber = 1;
  ::proto2_arena_unittest::NestedMessage* mutable_repeated_nested_message(int index);
  ::google::protobuf::RepeatedPtrField< ::proto2_arena_unittest::NestedMessage >*
      mutable_repeated_nested_message();
  const ::proto2_arena_unittest::NestedMessage& repeated_nested_message(int index) const;
  ::proto2_arena_unittest::NestedMessage* add_repeated_nested_message();
  const ::google::protobuf::RepeatedPtrField< ::proto2_arena_unittest::NestedMessage >&
      repeated_nested_message() const;

  // repeated .proto2_arena_unittest.ImportNoArenaNestedMessage repeated_import_no_arena_message = 2;
  int repeated_import_no_arena_message_size() const;
  void clear_repeated_import_no_arena_message();
  static const int kRepeatedImportNoArenaMessageFieldNumber = 2;
  ::proto2_arena_unittest::ImportNoArenaNestedMessage* mutable_repeated_import_no_arena_message(int index);
  ::google::protobuf::RepeatedPtrField< ::proto2_arena_unittest::ImportNoArenaNestedMessage >*
      mutable_repeated_import_no_arena_message();
  const ::proto2_arena_unittest::ImportNoArenaNestedMessage& repeated_import_no_arena_message(int index) const;
  ::proto2_arena_unittest::ImportNoArenaNestedMessage* add_repeated_import_no_arena_message();
  const ::google::protobuf::RepeatedPtrField< ::proto2_arena_unittest::ImportNoArenaNestedMessage >&
      repeated_import_no_arena_message() const;

  // @@protoc_insertion_point(class_scope:proto2_arena_unittest.ArenaMessage)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  template <typename T> friend class ::google::protobuf::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::google::protobuf::internal::HasBits<1> _has_bits_;
  mutable int _cached_size_;
  ::google::protobuf::RepeatedPtrField< ::proto2_arena_unittest::NestedMessage > repeated_nested_message_;
  ::google::protobuf::RepeatedPtrField< ::proto2_arena_unittest::ImportNoArenaNestedMessage > repeated_import_no_arena_message_;
  friend struct ::protobuf_google_2fprotobuf_2funittest_5farena_2eproto::TableStruct;
  friend void ::protobuf_google_2fprotobuf_2funittest_5farena_2eproto::InitDefaultsArenaMessageImpl();
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// NestedMessage

// optional int32 d = 1;
inline bool NestedMessage::has_d() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void NestedMessage::set_has_d() {
  _has_bits_[0] |= 0x00000001u;
}
inline void NestedMessage::clear_has_d() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void NestedMessage::clear_d() {
  d_ = 0;
  clear_has_d();
}
inline ::google::protobuf::int32 NestedMessage::d() const {
  // @@protoc_insertion_point(field_get:proto2_arena_unittest.NestedMessage.d)
  return d_;
}
inline void NestedMessage::set_d(::google::protobuf::int32 value) {
  set_has_d();
  d_ = value;
  // @@protoc_insertion_point(field_set:proto2_arena_unittest.NestedMessage.d)
}

// -------------------------------------------------------------------

// ArenaMessage

// repeated .proto2_arena_unittest.NestedMessage repeated_nested_message = 1;
inline int ArenaMessage::repeated_nested_message_size() const {
  return repeated_nested_message_.size();
}
inline void ArenaMessage::clear_repeated_nested_message() {
  repeated_nested_message_.Clear();
}
inline ::proto2_arena_unittest::NestedMessage* ArenaMessage::mutable_repeated_nested_message(int index) {
  // @@protoc_insertion_point(field_mutable:proto2_arena_unittest.ArenaMessage.repeated_nested_message)
  return repeated_nested_message_.Mutable(index);
}
inline ::google::protobuf::RepeatedPtrField< ::proto2_arena_unittest::NestedMessage >*
ArenaMessage::mutable_repeated_nested_message() {
  // @@protoc_insertion_point(field_mutable_list:proto2_arena_unittest.ArenaMessage.repeated_nested_message)
  return &repeated_nested_message_;
}
inline const ::proto2_arena_unittest::NestedMessage& ArenaMessage::repeated_nested_message(int index) const {
  // @@protoc_insertion_point(field_get:proto2_arena_unittest.ArenaMessage.repeated_nested_message)
  return repeated_nested_message_.Get(index);
}
inline ::proto2_arena_unittest::NestedMessage* ArenaMessage::add_repeated_nested_message() {
  // @@protoc_insertion_point(field_add:proto2_arena_unittest.ArenaMessage.repeated_nested_message)
  return repeated_nested_message_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::proto2_arena_unittest::NestedMessage >&
ArenaMessage::repeated_nested_message() const {
  // @@protoc_insertion_point(field_list:proto2_arena_unittest.ArenaMessage.repeated_nested_message)
  return repeated_nested_message_;
}

// repeated .proto2_arena_unittest.ImportNoArenaNestedMessage repeated_import_no_arena_message = 2;
inline int ArenaMessage::repeated_import_no_arena_message_size() const {
  return repeated_import_no_arena_message_.size();
}
inline ::proto2_arena_unittest::ImportNoArenaNestedMessage* ArenaMessage::mutable_repeated_import_no_arena_message(int index) {
  // @@protoc_insertion_point(field_mutable:proto2_arena_unittest.ArenaMessage.repeated_import_no_arena_message)
  return repeated_import_no_arena_message_.Mutable(index);
}
inline ::google::protobuf::RepeatedPtrField< ::proto2_arena_unittest::ImportNoArenaNestedMessage >*
ArenaMessage::mutable_repeated_import_no_arena_message() {
  // @@protoc_insertion_point(field_mutable_list:proto2_arena_unittest.ArenaMessage.repeated_import_no_arena_message)
  return &repeated_import_no_arena_message_;
}
inline const ::proto2_arena_unittest::ImportNoArenaNestedMessage& ArenaMessage::repeated_import_no_arena_message(int index) const {
  // @@protoc_insertion_point(field_get:proto2_arena_unittest.ArenaMessage.repeated_import_no_arena_message)
  return repeated_import_no_arena_message_.Get(index);
}
inline ::proto2_arena_unittest::ImportNoArenaNestedMessage* ArenaMessage::add_repeated_import_no_arena_message() {
  // @@protoc_insertion_point(field_add:proto2_arena_unittest.ArenaMessage.repeated_import_no_arena_message)
  return repeated_import_no_arena_message_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::proto2_arena_unittest::ImportNoArenaNestedMessage >&
ArenaMessage::repeated_import_no_arena_message() const {
  // @@protoc_insertion_point(field_list:proto2_arena_unittest.ArenaMessage.repeated_import_no_arena_message)
  return repeated_import_no_arena_message_;
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace proto2_arena_unittest

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_google_2fprotobuf_2funittest_5farena_2eproto_INCLUDED
