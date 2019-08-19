#ifndef _CIM_API_H
#define _CIM_API_H

/// \ingroup setting
/// \brief Interface to setting information used by CIM provider

#ifdef __cplusplus
extern "C" {
#endif

#define CMR_NAME_LEN 256
#define TYPE_LEN 256


/// \brief Attribute information for each setting.
struct cmr_attribute
{
    const char* ID;             ///< Setting ID 
    const char* suppress_if;            ///< Setting if-condition type: "suppress-if"
    const char* gray_if;         ///< Setting if-condition type: "gray_if"
    const char* config;         ///< Setting config section (collection) 
    const char* config_name;	///< Config name
    const char* cfgset_name;	///< Configset name
    const char* cfgset_id;   	///< Configset ID
};

typedef struct cmr_attribute CMR_ATTRIBUTE;
typedef const char* CMR_COLLECTION;
typedef const char* CMR_ATTRNAME;

#define CMR_MAX_SETTING_VALUE_OUT 256



/// \brief cmr_transaction structure used for get/set operations
struct cmr_transaction
{
    unsigned     status;                 ///< return status for the setting transaction
    unsigned     opcode;                 ///< cmr_operation to perform 
    CMR_ATTRNAME setting_instance;       ///< fully qualified setting name - config.ID[.instance]
    const char*  setting_value_in;       ///< on set command, value to set

    char         setting_value_out[CMR_MAX_SETTING_VALUE_OUT+1];  
};

typedef struct cmr_transaction CMR_TRANSACTION;


int cmr_api_initialize();

int cmr_api_uninitialize();

int cmr_get_bios_collections( CMR_COLLECTION* pcoll[], unsigned int* pcount);

int cmr_get_bios_attributes( CMR_COLLECTION coll, CMR_ATTRIBUTE* pattr[], unsigned int* pcount); 

int cmr_get_bios_attributes_lite( CMR_COLLECTION coll, CMR_ATTRIBUTE* pattr[], unsigned int* pcount);

int cmr_free_bios_attributes( CMR_COLLECTION coll, CMR_ATTRIBUTE* pattr, CMR_ATTRNAME* pattrnames ); 

int cmr_get_bios_attribute_names( CMR_COLLECTION coll, CMR_ATTRNAME* pattr[], unsigned int* pcount ); 

int cmr_get_bios_attribute( CMR_ATTRNAME attr, CMR_ATTRIBUTE** pattr); 

int cmr_get_bios_attribute_value( CMR_TRANSACTION ptrans[], unsigned int count, int current );

int cmr_set_bios_attribute_value( CMR_TRANSACTION ptrans[], unsigned int count );

int cmr_bios_reset_to_defaults( CMR_COLLECTION coll );

int cmr_bios_need_reinit( CMR_COLLECTION coll );



#ifdef __cplusplus
}
#endif

#endif
