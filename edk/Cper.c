/**
 * Extern definitions for EFI GUIDs relating to notification types and error section types.
 * 
 * Author: Lawrence.Tang@arm.com
 **/
#include "Cper.h"

//Event notification type GUIDs.
EFI_GUID gEfiEventNotificationTypeCmcGuid   = { 0x2DCE8BB1, 0xBDD7, 0x450e, { 0xB9, 0xAD, 0x9C, 0xF4, 0xEB, 0xD4, 0xF8, 0x90 }};
EFI_GUID gEfiEventNotificationTypeCpeGuid   = { 0x4E292F96, 0xD843, 0x4a55, { 0xA8, 0xC2, 0xD4, 0x81, 0xF2, 0x7E, 0xBE, 0xEE }};
EFI_GUID gEfiEventNotificationTypeMceGuid   = { 0xE8F56FFE, 0x919C, 0x4cc5, { 0xBA, 0x88, 0x65, 0xAB, 0xE1, 0x49, 0x13, 0xBB }};
EFI_GUID gEfiEventNotificationTypePcieGuid  = { 0xCF93C01F, 0x1A16, 0x4dfc, { 0xB8, 0xBC, 0x9C, 0x4D, 0xAF, 0x67, 0xC1, 0x04 }};
EFI_GUID gEfiEventNotificationTypeInitGuid  = { 0xCC5263E8, 0x9308, 0x454a, { 0x89, 0xD0, 0x34, 0x0B, 0xD3, 0x9B, 0xC9, 0x8E }};
EFI_GUID gEfiEventNotificationTypeNmiGuid   = { 0x5BAD89FF, 0xB7E6, 0x42c9, { 0x81, 0x4A, 0xCF, 0x24, 0x85, 0xD6, 0xE9, 0x8A }};
EFI_GUID gEfiEventNotificationTypeBootGuid  = { 0x3D61A466, 0xAB40, 0x409a, { 0xA6, 0x98, 0xF3, 0x62, 0xD4, 0x64, 0xB3, 0x8F }};
EFI_GUID gEfiEventNotificationTypeDmarGuid  = { 0x667DD791, 0xC6B3, 0x4c27, { 0x8A, 0x6B, 0x0F, 0x8E, 0x72, 0x2D, 0xEB, 0x41 }};
EFI_GUID gEfiEventNotificationTypeSeaGuid   = { 0x9A78788A, 0xBBE8, 0x11E4, { 0x80, 0x9E, 0x67, 0x61, 0x1E, 0x5D, 0x46, 0xB0 }};
EFI_GUID gEfiEventNotificationTypeSeiGuid   = { 0x5C284C81, 0xB0AE, 0x4E87, { 0xA3, 0x22, 0xB0, 0x4C, 0x85, 0x62, 0x43, 0x23 }};
EFI_GUID gEfiEventNotificationTypePeiGuid   = { 0x09A9D5AC, 0x5204, 0x4214, { 0x96, 0xE5, 0x94, 0x99, 0x2E, 0x75, 0x2B, 0xCD }};
EFI_GUID gEfiEventNotificationTypeCxlGuid   = { 0x69293BC9, 0x41DF, 0x49A3, { 0xB4, 0xBD, 0x4F, 0xB0, 0xDB, 0x30, 0x41, 0xF6 }};

//Error section GUIDs.
EFI_GUID gEfiProcessorGenericErrorSectionGuid  = { 0x9876ccad, 0x47b4, 0x4bdb, { 0xb6, 0x5e, 0x16, 0xf1, 0x93, 0xc4, 0xf3, 0xdb }};
EFI_GUID gEfiProcessorSpecificErrorSectionGuid = { 0xdc3ea0b0, 0xa144, 0x4797, { 0xb9, 0x5b, 0x53, 0xfa, 0x24, 0x2b, 0x6e, 0x1d }};
EFI_GUID gEfiIa32X64ProcessorErrorSectionGuid  = { 0xdc3ea0b0, 0xa144, 0x4797, { 0xb9, 0x5b, 0x53, 0xfa, 0x24, 0x2b, 0x6e, 0x1d }};
//todo: Why does IPF GUID have an excess of elements?
//EFI_GUID gEfiIpfProcessorErrorSectionGuid  = { 0xe429faf1, 0x3cb7, 0x11d4, { 0xb, 0xca, 0x7, 0x00, 0x80, 0xc7, 0x3c, 0x88, 0x81 }};
EFI_GUID gEfiArmProcessorErrorSectionGuid  = { 0xe19e3d16, 0xbc11, 0x11e4, { 0x9c, 0xaa, 0xc2, 0x05, 0x1d, 0x5d, 0x46, 0xb0 }};
EFI_GUID gEfiPlatformMemoryErrorSectionGuid = { 0xa5bc1114, 0x6f64, 0x4ede, { 0xb8, 0x63, 0x3e, 0x83, 0xed, 0x7c, 0x83, 0xb1 }};
EFI_GUID gEfiPlatformMemoryError2SectionGuid = { 0x61EC04FC, 0x48E6, 0xD813, { 0x25, 0xC9, 0x8D, 0xAA, 0x44, 0x75, 0x0B, 0x12 }};
EFI_GUID gEfiPcieErrorSectionGuid           = { 0xd995e954, 0xbbc1, 0x430f, { 0xad, 0x91, 0xb4, 0x4d, 0xcb, 0x3c, 0x6f, 0x35 }};
EFI_GUID gEfiFirmwareErrorSectionGuid       = { 0x81212a96, 0x09ed, 0x4996, { 0x94, 0x71, 0x8d, 0x72, 0x9c, 0x8e, 0x69, 0xed }};
EFI_GUID gEfiPciBusErrorSectionGuid         = { 0xc5753963, 0x3b84, 0x4095, { 0xbf, 0x78, 0xed, 0xda, 0xd3, 0xf9, 0xc9, 0xdd }};
EFI_GUID gEfiPciDevErrorSectionGuid         = { 0xeb5e4685, 0xca66, 0x4769, { 0xb6, 0xa2, 0x26, 0x06, 0x8b, 0x00, 0x13, 0x26 }};
EFI_GUID gEfiDMArGenericErrorSectionGuid    = { 0x5b51fef7, 0xc79d, 0x4434, { 0x8f, 0x1b, 0xaa, 0x62, 0xde, 0x3e, 0x2c, 0x64 }};
EFI_GUID gEfiDirectedIoDMArErrorSectionGuid = { 0x71761d37, 0x32b2, 0x45cd, { 0xa7, 0xd0, 0xb0, 0xfe, 0xdd, 0x93, 0xe8, 0xcf }};
EFI_GUID gEfiIommuDMArErrorSectionGuid      = { 0x036f84e1, 0x7f37, 0x428c, { 0xa7, 0x9e, 0x57, 0x5f, 0xdf, 0xaa, 0x84, 0xec }};
EFI_GUID gEfiCcixPerLogErrorSectionGuid     = { 0x91335EF6, 0xEBFB, 0x4478, {0xA6, 0xA6, 0x88, 0xB7, 0x28, 0xCF, 0x75, 0xD7 }};
EFI_GUID gEfiCxlProtocolErrorSectionGuid    = { 0x80B9EFB4, 0x52B5, 0x4DE3, { 0xA7, 0x77, 0x68, 0x78, 0x4B, 0x77, 0x10, 0x48 }};

//IA32/x64 error segment GUIDs.
EFI_GUID gEfiIa32x64ErrorTypeCacheCheckGuid = { 0xA55701F5, 0xE3EF, 0x43de, {0xAC, 0x72, 0x24, 0x9B, 0x57, 0x3F, 0xAD, 0x2C } };
EFI_GUID gEfiIa32x64ErrorTypeTlbCheckGuid = { 0xFC06B535, 0x5E1F, 0x4562, {0x9F, 0x25, 0x0A, 0x3B, 0x9A, 0xDB, 0x63, 0xC3 } };
EFI_GUID gEfiIa32x64ErrorTypeBusCheckGuid = { 0x1CF3F8B3, 0xC5B1, 0x49a2, {0xAA, 0x59, 0x5E, 0xEF, 0x92, 0xFF, 0xA6, 0x3C } };
EFI_GUID gEfiIa32x64ErrorTypeMsCheckGuid = { 0x48AB7F57, 0xDC34, 0x4f6c, {0xA7, 0xD3, 0xB0, 0xB5, 0xB0, 0xA7, 0x43, 0x14 } };