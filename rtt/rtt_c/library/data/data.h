#include "common.h"
#include "content/content.h"
#include "device/device.h"
#include "user/user.h"
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
const static Data create_data(const char *data);
/**
 * @brief
 *
 * @param data_ptr 
 */
static void free_data(DataPtr data_ptr);
static struct _DataManager
{
    Data (*new)(const char *);
    Super super;
};
/**
 * @brief
 *
 */
extern const struct _DataManager DataManager;
#endif