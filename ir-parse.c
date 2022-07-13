/**
 * Describes functions for parsing JSON IR CPER data into binary CPER format.
 * 
 * Author: Lawrence.Tang@arm.com
 **/

#include <stdio.h>
#include <string.h>
#include "json.h"
#include "b64.h"
#include "edk/Cper.h"
#include "cper-parse.h"
#include "cper-utils.h"
#include "sections/cper-section-generic.h"
#include "sections/cper-section-ia32x64.h"
#include "sections/cper-section-arm.h"
#include "sections/cper-section-memory.h"
#include "sections/cper-section-pcie.h"
#include "sections/cper-section-pci-bus.h"
#include "sections/cper-section-pci-dev.h"
#include "sections/cper-section-firmware.h"
#include "sections/cper-section-dmar-generic.h"
#include "sections/cper-section-dmar-vtd.h"
#include "sections/cper-section-dmar-iommu.h"
#include "sections/cper-section-ccix-per.h"
#include "sections/cper-section-cxl-protocol.h"
#include "sections/cper-section-ipf.h"
#include "sections/cper-section-cxl-component.h"

//Private pre-declarations.
void ir_header_to_cper(json_object* header_ir, EFI_COMMON_ERROR_RECORD_HEADER* header);
void ir_section_descriptor_to_cper(json_object* section_descriptor_ir, EFI_ERROR_SECTION_DESCRIPTOR* descriptor);

//Converts the given JSON IR CPER representation into CPER binary format, piped to the provided file stream.
//This function performs no validation of the IR against the CPER-JSON specification. To ensure a safe call,
//use validate_schema() from json-schema.h before attempting to call this function. 
void ir_to_cper(json_object* ir, FILE* out)
{
    //Create the CPER header.
    EFI_COMMON_ERROR_RECORD_HEADER* header = (EFI_COMMON_ERROR_RECORD_HEADER*)calloc(1, sizeof(EFI_COMMON_ERROR_RECORD_HEADER));
    ir_header_to_cper(json_object_object_get(ir, "header"), header);
    fwrite(header, sizeof(EFI_COMMON_ERROR_RECORD_HEADER), 1, out);
    fflush(out);

    //Create the CPER section descriptors.
    json_object* section_descriptors = json_object_object_get(ir, "sectionDescriptors");
    int amt_descriptors = json_object_array_length(section_descriptors);
    EFI_ERROR_SECTION_DESCRIPTOR* descriptors[amt_descriptors];
    for (int i=0; i<amt_descriptors; i++)
    {
        descriptors[i] = (EFI_ERROR_SECTION_DESCRIPTOR*)calloc(1, sizeof(EFI_ERROR_SECTION_DESCRIPTOR));
        ir_section_descriptor_to_cper(json_object_array_get_idx(section_descriptors, i), descriptors[i]);
        fwrite(descriptors[i], sizeof(EFI_ERROR_SECTION_DESCRIPTOR), 1, out);
        fflush(out);
    }
    
    //Run through each section in turn.
    json_object* sections = json_object_object_get(ir, "sections");
    int amt_sections = json_object_array_length(sections);
    for (int i=0; i<amt_sections; i++)
    {
        //Get the section itself from the IR.
        json_object* section = json_object_array_get_idx(sections, i);

        //Find the correct section type, and parse.
        if (guid_equal(&descriptors[i]->SectionType, &gEfiProcessorGenericErrorSectionGuid))
            ir_section_generic_to_cper(section, out);
        else if (guid_equal(&descriptors[i]->SectionType, &gEfiIa32X64ProcessorErrorSectionGuid))
            ir_section_ia32x64_to_cper(section, out);
        // else if (guid_equal(&descriptors[i]->SectionType, &gEfiIpfProcessorErrorSectionGuid))
        //     ir_section_ipf_to_cper(section, out);
        // else if (guid_equal(&descriptors[i]->SectionType, &gEfiArmProcessorErrorSectionGuid))
        //     ir_section_arm_to_cper(section, out);
        // else if (guid_equal(&descriptors[i]->SectionType, &gEfiPlatformMemoryErrorSectionGuid))
        //     ir_section_platform_memory_to_cper(section, out);
        // else if (guid_equal(&descriptors[i]->SectionType, &gEfiPlatformMemoryError2SectionGuid))
        //     ir_section_platform_memory2_to_cper(section, out);
        // else if (guid_equal(&descriptors[i]->SectionType, &gEfiPcieErrorSectionGuid))
        //     ir_section_pcie_to_cper(section, out);
        // else if (guid_equal(&descriptors[i]->SectionType, &gEfiFirmwareErrorSectionGuid))
        //     ir_section_firmware_to_cper(section, out);
        // else if (guid_equal(&descriptors[i]->SectionType, &gEfiPciBusErrorSectionGuid))
        //     ir_section_pci_bus_to_cper(section, out);
        // else if (guid_equal(&descriptors[i]->SectionType, &gEfiPciDevErrorSectionGuid))
        //     ir_section_pci_dev_to_cper(section, out);
        // else if (guid_equal(&descriptors[i]->SectionType, &gEfiDMArGenericErrorSectionGuid))
        //     ir_section_dmar_generic_to_cper(section, out);
        // else if (guid_equal(&descriptors[i]->SectionType, &gEfiDirectedIoDMArErrorSectionGuid))
        //     ir_section_dmar_vtd_to_cper(section, out);
        // else if (guid_equal(&descriptors[i]->SectionType, &gEfiIommuDMArErrorSectionGuid))
        //     ir_section_dmar_iommu_to_cper(section, out);
        // else if (guid_equal(&descriptors[i]->SectionType, &gEfiCcixPerLogErrorSectionGuid))
        //     ir_section_ccix_per_to_cper(section, out);
        // else if (guid_equal(&descriptors[i]->SectionType, &gEfiCxlProtocolErrorSectionGuid))
        //     ir_section_cxl_protocol_to_cper(section, out);
        // else if (guid_equal(&descriptors[i]->SectionType, &gEfiCxlGeneralMediaErrorSectionGuid)
        //     || guid_equal(&descriptors[i]->SectionType, &gEfiCxlDramEventErrorSectionGuid)
        //     || guid_equal(&descriptors[i]->SectionType, &gEfiCxlPhysicalSwitchErrorSectionGuid)
        //     || guid_equal(&descriptors[i]->SectionType, &gEfiCxlVirtualSwitchErrorSectionGuid)
        //     || guid_equal(&descriptors[i]->SectionType, &gEfiCxlMldPortErrorSectionGuid))
        // {
        //     ir_section_cxl_component_to_cper(section, out);
        // }
        else
        {
            //Unknown GUID, so read as a base64 unknown section.
            json_object* encoded = json_object_object_get(section, "data");
            UINT8* decoded = b64_decode(json_object_get_string(encoded), json_object_get_string_len(encoded));
            fwrite(decoded, descriptors[i]->SectionLength, 1, out);
            fflush(out);
            free(decoded);
        }
    }

    //Free all remaining resources.
    free(header);
    for (int i=0; i<amt_descriptors; i++)
        free(descriptors[i]);
}

//Converts a CPER-JSON IR header to a CPER header structure.
void ir_header_to_cper(json_object* header_ir, EFI_COMMON_ERROR_RECORD_HEADER* header)
{
    header->SignatureStart = 0x52455043; //CPER

    //Revision.
    json_object* revision = json_object_object_get(header_ir, "revision");
    int minor = json_object_get_int(json_object_object_get(revision, "minor"));
    int major = json_object_get_int(json_object_object_get(revision, "major"));
    header->Revision = minor + (major << 8);

    header->SignatureEnd = 0xFFFFFFFF;

    //Section count.
    int section_count = json_object_get_int(json_object_object_get(header_ir, "sectionCount"));
    header->SectionCount = (UINT16)section_count;

    //Error severity.
    json_object* severity = json_object_object_get(header_ir, "severity");
    header->ErrorSeverity = (UINT32)json_object_get_uint64(json_object_object_get(severity, "code"));

    //Validation bits.
    header->ValidationBits = ir_to_bitfield(json_object_object_get(header_ir, "validationBits"), 
        3, CPER_HEADER_VALID_BITFIELD_NAMES);

    //Record length.
    header->RecordLength = (UINT32)json_object_get_uint64(json_object_object_get(header_ir, "recordLength"));

    //Timestamp, if present.
    json_object* timestamp = json_object_object_get(header_ir, "timestamp");
    if (timestamp != NULL) 
    {
        string_to_timestamp(&header->TimeStamp, json_object_get_string(timestamp));
        header->TimeStamp.Flag = json_object_get_boolean(json_object_object_get(header_ir, "timestampIsPrecise"));
    }

    //Various GUIDs.
    json_object* platform_id = json_object_object_get(header_ir, "platformID");
    json_object* partition_id = json_object_object_get(header_ir, "partitionID");
    if (platform_id != NULL)
        string_to_guid(&header->PlatformID, json_object_get_string(platform_id));
    if (partition_id != NULL)
        string_to_guid(&header->PartitionID, json_object_get_string(partition_id));
    string_to_guid(&header->CreatorID, json_object_get_string(json_object_object_get(header_ir, "creatorID")));

    //Notification type.
    json_object* notification_type = json_object_object_get(header_ir, "notificationType");
    string_to_guid(&header->NotificationType, json_object_get_string(json_object_object_get(notification_type, "guid")));

    //Record ID, persistence info.
    header->RecordID = json_object_get_uint64(json_object_object_get(header_ir, "recordID"));
    header->PersistenceInfo = json_object_get_uint64(json_object_object_get(header_ir, "persistenceInfo"));

    //Flags.
    json_object* flags = json_object_object_get(header_ir, "flags");
    header->Flags = (UINT32)json_object_get_uint64(json_object_object_get(flags, "value"));
}

//Converts a single CPER-JSON IR section descriptor into a CPER structure.
void ir_section_descriptor_to_cper(json_object* section_descriptor_ir, EFI_ERROR_SECTION_DESCRIPTOR* descriptor)
{
    //Section offset, length.
    descriptor->SectionOffset = (UINT32)json_object_get_uint64(json_object_object_get(section_descriptor_ir, "sectionOffset"));
    descriptor->SectionLength = (UINT32)json_object_get_uint64(json_object_object_get(section_descriptor_ir, "sectionLength"));

    //Revision.
    json_object* revision = json_object_object_get(section_descriptor_ir, "revision");
    int minor = json_object_get_int(json_object_object_get(revision, "minor"));
    int major = json_object_get_int(json_object_object_get(revision, "major"));
    descriptor->Revision = minor + (major << 8);

    //Validation bits, flags.
    descriptor->SecValidMask = ir_to_bitfield(json_object_object_get(section_descriptor_ir, "validationBits"), 
        2, CPER_SECTION_DESCRIPTOR_VALID_BITFIELD_NAMES);
    descriptor->SectionFlags = ir_to_bitfield(json_object_object_get(section_descriptor_ir, "flags"), 
        8, CPER_SECTION_DESCRIPTOR_FLAGS_BITFIELD_NAMES);

    //Section type.
    json_object* section_type = json_object_object_get(section_descriptor_ir, "sectionType");
    string_to_guid(&descriptor->SectionType, json_object_get_string(json_object_object_get(section_type, "data")));

    //FRU ID, if present.
    json_object* fru_id = json_object_object_get(section_descriptor_ir, "fruID");
    if (fru_id != NULL)
        string_to_guid(&descriptor->FruId, json_object_get_string(fru_id));

    //Severity code.
    json_object* severity = json_object_object_get(section_descriptor_ir, "severity");
    descriptor->Severity = (UINT32)json_object_get_uint64(json_object_object_get(severity, "code"));

    //FRU text, if present.
    json_object* fru_text = json_object_object_get(section_descriptor_ir, "fruText");
    if (fru_text != NULL)
        strncpy(descriptor->FruString, json_object_get_string(fru_text), 20);
}