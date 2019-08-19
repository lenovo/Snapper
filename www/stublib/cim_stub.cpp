#include <cmr/common/cim_api.h>

int cmr_api_initialize() {return -1; }
int cmr_api_uninitialize() {return -1; }
int cmr_get_bios_collections( CMR_COLLECTION* pcoll[], unsigned int* pcount) {return -1; }
int cmr_get_bios_attributes( CMR_COLLECTION coll, CMR_ATTRIBUTE* pattr[], unsigned int* pcount ) {return -1; } 
int cmr_get_bios_attributes_lite( CMR_COLLECTION coll, CMR_ATTRIBUTE* pattr[], unsigned int* pcount ) {return -1; } 
int cmr_get_bios_attribute_names( CMR_COLLECTION coll, CMR_ATTRNAME* pattr[], unsigned int* pcount ) {return -1; } 
int cmr_get_bios_attribute( CMR_ATTRNAME attr, CMR_ATTRIBUTE** pattr) {return -1; } 
int cmr_get_bios_attribute_value( CMR_TRANSACTION ptrans[], unsigned int count, int current ) {return -1; }
int cmr_set_bios_attribute_value( CMR_TRANSACTION ptrans[], unsigned int count ) {return -1; }
int cmr_bios_reset_to_defaults( CMR_COLLECTION coll ) {return -1; }
int cmr_bios_need_reinit( CMR_COLLECTION coll ) {return -1; }
int cmr_free_bios_attributes( CMR_COLLECTION coll, CMR_ATTRIBUTE* pattr, CMR_ATTRNAME* pattrnames ) { return -1; }
