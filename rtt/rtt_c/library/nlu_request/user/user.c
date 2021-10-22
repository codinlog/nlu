#include "user.h"
static cJSON *user_to_cjson(void *user)
{
    const UserPtr user_ptr = (UserPtr)(user);
    const cJSON *user_json = cJSON_CreateObject();
    cJSON_AddStringToObject(user_json, USER_MID, user_ptr->mid);
    cJSON_AddStringToObject(user_json, USER_UID, user_ptr->uid);
    return user_json;
}

static User create_user(const char *mid, const char *uid)
{
    char *_mid = rt_strdup(mid);
    char *_uid = rt_strdup(uid);
    const User user = {
        .mid = _mid,
        .uid = _uid,
    };
    return user;
};
static void free_user(UserPtr user_ptr)
{
    rt_free(user_ptr->mid);
    rt_free(user_ptr->uid);
}
const _UserManager UserManager = {
    .new = create_user,
    .base = {
        .json = {
            .to_cjson = user_to_cjson,
        },
        .drop = {
            .drop_memery = free_user,
        }}};