#ifndef CPER_SECTION_CXL_COMPONENT_H
#define CPER_SECTION_CXL_COMPONENT_H

#include "json.h"
#include "../edk/Cper.h"

///
/// CXL Generic Component Error Section
///
typedef struct {
  UINT64 VendorId : 16;
  UINT64 DeviceId : 16;
  UINT64 FunctionNumber : 8;
  UINT64 DeviceNumber : 8;
  UINT64 BusNumber : 8;
  UINT64 SegmentNumber : 16;
  UINT64 Resv1 : 3;
  UINT64 SlotNumber : 13;
  UINT64 Resv2 : 8;
} EFI_CXL_DEVICE_ID_INFO;

typedef struct {
    UINT32 Length;
    UINT64 ValidBits;
    EFI_CXL_DEVICE_ID_INFO DeviceId;
    UINT64 DeviceSerial;
} EFI_CXL_COMPONENT_EVENT_HEADER;

typedef struct {
    //todo: What is the structure for this? The UEFI spec is a bit vague.
} EFI_CXL_COMPONENT_COMMON_RECORD_HEAD;

json_object* cper_section_cxl_component_to_ir(void* section, EFI_ERROR_SECTION_DESCRIPTOR* descriptor);

#endif