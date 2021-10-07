#include "library/data/common.h"
#ifndef __DATA_USER_USER_H__
#define __DATA_USER_USER_H__
const static char USER_MID[] = "mid\0";
const static char USER_UID[] = "uid\0";
typedef struct
{
    const char *mid;
    const char *uid;
} User, *UserPtr;
/**
 * @brief Create a user object
 *
 * @param mid
 * @param uid
 * @return const User
 */
const static User create_user(const char *mid, const char *uid);
/**
 * @brief convert user to cjson object
 *
 * @param user
 * @return const cJSON* const
 */
const static cJSON *const user_to_cjson(void *user);
/**
 * @brief
 *  free user: free mid and uid memery
 * @param user_ptr 
 */
static void free_user(UserPtr user_ptr);
static struct _UserManager
{
    const User (*new)(const char *, const char *);
    Super super;
};
/**
 * @brief
 * Usage:
 *  create new user instance:
 *    const User user = UserManager.new(mid,uid);
 *  convert user to cJson:
 *    const cJson *const json = UserManager.json.to_json(&user);
 */
extern const struct _UserManager UserManager;
#endif