/**
 * @file user.h
 * @author qr-kou (codinlog@foxmail.com)
 * @brief
 * @version 0.1
 * @date 2021-10-22
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "library/nlu_handler/common/common.h"
#ifndef __DATA_USER_USER_H__
#define __DATA_USER_USER_H__

typedef struct
{
    const char *mid;
    const char *uid;
} User, *UserPtr, *const CUserPtr;

/**
 * @brief Create a user object
 *
 * @param mid
 * @param uid
 * @return const User
 */
static User user_new(const char *mid, const char *uid);

/**
 * @brief convert user to cjson object
 *
 * @param user
 * @return const cJSON* const
 */
static cJSON *user_to_cjson(void *user);

/**
 * @brief
 *  free user: free mid and uid memery
 * @param user_ptr
 */
static void user_drop_memory(UserPtr user_ptr);

typedef struct
{
    const User (*new)(const char *, const char *);
    Base base;
} _UserManager;

/**
 * @brief
 * Usage:
 *  create new user instance:
 *    const User user = UserManager.new(mid,uid);
 *  convert user to cJson:
 *    const cJson *const json = UserManager.json.to_json(&user);
 */
extern const _UserManager UserManager;
#endif