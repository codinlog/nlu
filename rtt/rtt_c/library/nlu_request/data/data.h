#include "library/nlu_request/common.h"
#include "library/nlu_request/content/content.h"
#include "library/nlu_request/device/device.h"
#include "library/nlu_request/user/user.h"
#ifndef __DATA_DATA_H__
#define __DATA_DATA_USER_H__
const static char DATA_DATA[] = "data\0";
typedef struct
{
    const char *data;
} Data, *DataPtr;
/**
 * @brief Create a data object
 *
 * @param data
 * @return const Data
 */
static Data create_data(const char *data);
/**
 * @brief
 *
 * @param data
 * @return cJSON*
 */
static cJSON *data_to_cjson(void *data);
/**
 * @brief
 *
 * @param data_ptr
 */
static void free_data(DataPtr data_ptr);
typedef struct
{
    Data (*new)(const char *);
    Base base;
} _DataManager;
/**
 * @brief
 *
 */
extern const _DataManager DataManager;
#endif