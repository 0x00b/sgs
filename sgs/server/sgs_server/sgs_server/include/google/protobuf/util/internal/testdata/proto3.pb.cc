// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: google/protobuf/util/internal/testdata/proto3.proto

#include <google/protobuf/util/internal/testdata/proto3.pb.h>

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/port.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// This is a temporary google only hack
#ifdef GOOGLE_PROTOBUF_ENFORCE_UNIQUENESS
#include "third_party/protobuf/version.h"
#endif
// @@protoc_insertion_point(includes)
namespace google {
namespace protobuf {
namespace testing {
class Proto3MessageDefaultTypeInternal {
 public:
  ::google::protobuf::internal::ExplicitlyConstructed<Proto3Message>
      _instance;
} _Proto3Message_default_instance_;
}  // namespace testing
}  // namespace protobuf
}  // namespace google
namespace protobuf_google_2fprotobuf_2futil_2finternal_2ftestdata_2fproto3_2eproto {
void InitDefaultsProto3MessageImpl() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

#ifdef GOOGLE_PROTOBUF_ENFORCE_UNIQUENESS
  ::google::protobuf::internal::InitProtobufDefaultsForceUnique();
#else
  ::google::protobuf::internal::InitProtobufDefaults();
#endif  // GOOGLE_PROTOBUF_ENFORCE_UNIQUENESS
  {
    void* ptr = &::google::protobuf::testing::_Proto3Message_default_instance_;
    new (ptr) ::google::protobuf::testing::Proto3Message();
    ::google::protobuf::internal::OnShutdownDestroyMessage(ptr);
  }
  ::google::protobuf::testing::Proto3Message::InitAsDefaultInstance();
}

void InitDefaultsProto3Message() {
  static GOOGLE_PROTOBUF_DECLARE_ONCE(once);
  ::google::protobuf::GoogleOnceInit(&once, &InitDefaultsProto3MessageImpl);
}

::google::protobuf::Metadata file_level_metadata[1];
const ::google::protobuf::EnumDescriptor* file_level_enum_descriptors[1];

const ::google::protobuf::uint32 TableStruct::offsets[] GOOGLE_PROTOBUF_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::google::protobuf::testing::Proto3Message, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::google::protobuf::testing::Proto3Message, enum_value_),
};
static const ::google::protobuf::internal::MigrationSchema schemas[] GOOGLE_PROTOBUF_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, sizeof(::google::protobuf::testing::Proto3Message)},
};

static ::google::protobuf::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::google::protobuf::Message*>(&::google::protobuf::testing::_Proto3Message_default_instance_),
};

void protobuf_AssignDescriptors() {
  AddDescriptors();
  ::google::protobuf::MessageFactory* factory = NULL;
  AssignDescriptors(
      "google/protobuf/util/internal/testdata/proto3.proto", schemas, file_default_instances, TableStruct::offsets, factory,
      file_level_metadata, file_level_enum_descriptors, NULL);
}

void protobuf_AssignDescriptorsOnce() {
  static GOOGLE_PROTOBUF_DECLARE_ONCE(once);
  ::google::protobuf::GoogleOnceInit(&once, &protobuf_AssignDescriptors);
}

void protobuf_RegisterTypes(const ::std::string&) GOOGLE_PROTOBUF_ATTRIBUTE_COLD;
void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::internal::RegisterAllTypes(file_level_metadata, 1);
}

void AddDescriptorsImpl() {
  InitDefaults();
  static const char descriptor[] GOOGLE_PROTOBUF_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
      "\n3google/protobuf/util/internal/testdata"
      "/proto3.proto\022\027google.protobuf.testing\"\177"
      "\n\rProto3Message\022E\n\nenum_value\030\001 \001(\01621.go"
      "ogle.protobuf.testing.Proto3Message.Nest"
      "edEnum\"\'\n\nNestedEnum\022\007\n\003FOO\020\000\022\007\n\003BAR\020\001\022\007"
      "\n\003BAZ\020\002b\006proto3"
  };
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
      descriptor, 215);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "google/protobuf/util/internal/testdata/proto3.proto", &protobuf_RegisterTypes);
}

void AddDescriptors() {
  static GOOGLE_PROTOBUF_DECLARE_ONCE(once);
  ::google::protobuf::GoogleOnceInit(&once, &AddDescriptorsImpl);
}
// Force AddDescriptors() to be called at dynamic initialization time.
struct StaticDescriptorInitializer {
  StaticDescriptorInitializer() {
    AddDescriptors();
  }
} static_descriptor_initializer;
}  // namespace protobuf_google_2fprotobuf_2futil_2finternal_2ftestdata_2fproto3_2eproto
namespace google {
namespace protobuf {
namespace testing {
const ::google::protobuf::EnumDescriptor* Proto3Message_NestedEnum_descriptor() {
  protobuf_google_2fprotobuf_2futil_2finternal_2ftestdata_2fproto3_2eproto::protobuf_AssignDescriptorsOnce();
  return protobuf_google_2fprotobuf_2futil_2finternal_2ftestdata_2fproto3_2eproto::file_level_enum_descriptors[0];
}
bool Proto3Message_NestedEnum_IsValid(int value) {
  switch (value) {
    case 0:
    case 1:
    case 2:
      return true;
    default:
      return false;
  }
}

#if !defined(_MSC_VER) || _MSC_VER >= 1900
const Proto3Message_NestedEnum Proto3Message::FOO;
const Proto3Message_NestedEnum Proto3Message::BAR;
const Proto3Message_NestedEnum Proto3Message::BAZ;
const Proto3Message_NestedEnum Proto3Message::NestedEnum_MIN;
const Proto3Message_NestedEnum Proto3Message::NestedEnum_MAX;
const int Proto3Message::NestedEnum_ARRAYSIZE;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

// ===================================================================

void Proto3Message::InitAsDefaultInstance() {
}
#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int Proto3Message::kEnumValueFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

Proto3Message::Proto3Message()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  if (GOOGLE_PREDICT_TRUE(this != internal_default_instance())) {
    ::protobuf_google_2fprotobuf_2futil_2finternal_2ftestdata_2fproto3_2eproto::InitDefaultsProto3Message();
  }
  SharedCtor();
  // @@protoc_insertion_point(constructor:google.protobuf.testing.Proto3Message)
}
Proto3Message::Proto3Message(const Proto3Message& from)
  : ::google::protobuf::Message(),
      _internal_metadata_(NULL),
      _cached_size_(0) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  enum_value_ = from.enum_value_;
  // @@protoc_insertion_point(copy_constructor:google.protobuf.testing.Proto3Message)
}

void Proto3Message::SharedCtor() {
  enum_value_ = 0;
  _cached_size_ = 0;
}

Proto3Message::~Proto3Message() {
  // @@protoc_insertion_point(destructor:google.protobuf.testing.Proto3Message)
  SharedDtor();
}

void Proto3Message::SharedDtor() {
}

void Proto3Message::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Proto3Message::descriptor() {
  ::protobuf_google_2fprotobuf_2futil_2finternal_2ftestdata_2fproto3_2eproto::protobuf_AssignDescriptorsOnce();
  return ::protobuf_google_2fprotobuf_2futil_2finternal_2ftestdata_2fproto3_2eproto::file_level_metadata[kIndexInFileMessages].descriptor;
}

const Proto3Message& Proto3Message::default_instance() {
  ::protobuf_google_2fprotobuf_2futil_2finternal_2ftestdata_2fproto3_2eproto::InitDefaultsProto3Message();
  return *internal_default_instance();
}


void Proto3Message::Clear() {
// @@protoc_insertion_point(message_clear_start:google.protobuf.testing.Proto3Message)
  ::google::protobuf::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  enum_value_ = 0;
  _internal_metadata_.Clear();
}

bool Proto3Message::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:google.protobuf.testing.Proto3Message)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // .google.protobuf.testing.Proto3Message.NestedEnum enum_value = 1;
      case 1: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(8u /* 8 & 0xFF */)) {
          int value;
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   int, ::google::protobuf::internal::WireFormatLite::TYPE_ENUM>(
                 input, &value)));
          set_enum_value(static_cast< ::google::protobuf::testing::Proto3Message_NestedEnum >(value));
        } else {
          goto handle_unusual;
        }
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, _internal_metadata_.mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:google.protobuf.testing.Proto3Message)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:google.protobuf.testing.Proto3Message)
  return false;
#undef DO_
}

void Proto3Message::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:google.protobuf.testing.Proto3Message)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // .google.protobuf.testing.Proto3Message.NestedEnum enum_value = 1;
  if (this->enum_value() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteEnum(
      1, this->enum_value(), output);
  }

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()), output);
  }
  // @@protoc_insertion_point(serialize_end:google.protobuf.testing.Proto3Message)
}

::google::protobuf::uint8* Proto3Message::InternalSerializeWithCachedSizesToArray(
    bool deterministic, ::google::protobuf::uint8* target) const {
  (void)deterministic; // Unused
  // @@protoc_insertion_point(serialize_to_array_start:google.protobuf.testing.Proto3Message)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // .google.protobuf.testing.Proto3Message.NestedEnum enum_value = 1;
  if (this->enum_value() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteEnumToArray(
      1, this->enum_value(), target);
  }

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:google.protobuf.testing.Proto3Message)
  return target;
}

size_t Proto3Message::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:google.protobuf.testing.Proto3Message)
  size_t total_size = 0;

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()));
  }
  // .google.protobuf.testing.Proto3Message.NestedEnum enum_value = 1;
  if (this->enum_value() != 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::EnumSize(this->enum_value());
  }

  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = cached_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void Proto3Message::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:google.protobuf.testing.Proto3Message)
  GOOGLE_DCHECK_NE(&from, this);
  const Proto3Message* source =
      ::google::protobuf::internal::DynamicCastToGenerated<const Proto3Message>(
          &from);
  if (source == NULL) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:google.protobuf.testing.Proto3Message)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:google.protobuf.testing.Proto3Message)
    MergeFrom(*source);
  }
}

void Proto3Message::MergeFrom(const Proto3Message& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:google.protobuf.testing.Proto3Message)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from.enum_value() != 0) {
    set_enum_value(from.enum_value());
  }
}

void Proto3Message::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:google.protobuf.testing.Proto3Message)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Proto3Message::CopyFrom(const Proto3Message& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:google.protobuf.testing.Proto3Message)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Proto3Message::IsInitialized() const {
  return true;
}

void Proto3Message::Swap(Proto3Message* other) {
  if (other == this) return;
  InternalSwap(other);
}
void Proto3Message::InternalSwap(Proto3Message* other) {
  using std::swap;
  swap(enum_value_, other->enum_value_);
  _internal_metadata_.Swap(&other->_internal_metadata_);
  swap(_cached_size_, other->_cached_size_);
}

::google::protobuf::Metadata Proto3Message::GetMetadata() const {
  protobuf_google_2fprotobuf_2futil_2finternal_2ftestdata_2fproto3_2eproto::protobuf_AssignDescriptorsOnce();
  return ::protobuf_google_2fprotobuf_2futil_2finternal_2ftestdata_2fproto3_2eproto::file_level_metadata[kIndexInFileMessages];
}


// @@protoc_insertion_point(namespace_scope)
}  // namespace testing
}  // namespace protobuf
}  // namespace google
namespace google {
namespace protobuf {
template<> GOOGLE_PROTOBUF_ATTRIBUTE_NOINLINE ::google::protobuf::testing::Proto3Message* Arena::Create< ::google::protobuf::testing::Proto3Message >(Arena* arena) {
  return Arena::CreateInternal< ::google::protobuf::testing::Proto3Message >(arena);
}
}  // namespace protobuf
}  // namespace google

// @@protoc_insertion_point(global_scope)
