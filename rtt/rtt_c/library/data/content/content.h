// #include "data/common.h"
#include "library/data/device/device.h"
#include "library/data/user/user.h"
#ifndef __DATA_CONTENT_CONTENT_H__
#define __DATA_CONTENT_CONTENT_H__
const static char CONTENT_USER[] = "user\0";
const static char CONTENT_DEVICE[] = "device\0";
const static char CONTENT_QUERY[] = "query\0";
typedef struct
{
    const User user;
    const Device device;
    const char *query;
} Content, *ContentPtr;
/**
 * @brief convert content to cjson object
 * @param data
 * @return const cJSON* const 
 */
static cJSON *content_to_cjson(void *data);
/**
 * @brief Create a content object
 *
 * @param user
 * @param device
 * @param query
 * @return const Content
 */
static Content create_content(const User user, const Device device, const char *query);
typedef struct
{
    const Content (*new)(const User, const Device, const char *);
    Base base;
} _ContentManager;
/**
 * @brief
 *
 */
extern const _ContentManager ContentManager;
#endif