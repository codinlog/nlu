/**
 * @file content.h
 * @author qr-kou (codinlog@foxmail.com)
 * @brief
 * @version 0.1
 * @date 2021-10-22
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "library/nlu_handler/nlu_request/device/device.h"
#include "library/nlu_handler/nlu_request/user/user.h"

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
} Content, *ContentPtr, *const CContentPtr;

/**
 * @brief Create a content object
 *
 * @param user
 * @param device
 * @param query
 * @return const Content
 */
static Content content_new(const User user, const Device device, const char *query);

/**
 * @brief convert content to cjson object
 * @param data
 * @return const cJSON* const
 */
static cJSON *content_to_cjson(void *data);

/**
 * @brief 释放申请的堆空间
 *
 * @param content_ptr
 */
static void content_drop_memory(const ContentPtr content_ptr);

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