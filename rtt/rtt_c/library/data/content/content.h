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
const static cJSON *const content_to_cjson(void *data);
/**
 * @brief Create a content object
 *
 * @param user
 * @param device
 * @param query
 * @return const Content
 */
const static Content create_content(const User user, const Device device, const char *query);
static struct _ContentManager
{
    const Content (*new)(const User, const Device, const char *);
    Super super;
};
/**
 * @brief
 *
 */
extern const struct _ContentManager ContentManager;
#endif