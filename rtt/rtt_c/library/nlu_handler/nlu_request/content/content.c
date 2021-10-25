/**
 * @file content.c
 * @author qr-kou (codinlog@foxmail.com)
 * @brief
 * @version 0.1
 * @date 2021-10-22
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "content.h"

static Content content_new(const User user, const Device device, const char *query)
{
    char *_query = rt_strdup(query);
    const Content content = {
        .user = user,
        .device = device,
        .query = _query,
    };
    return content;
}

static cJSON *content_to_cjson(void *data)
{
    const ContentPtr content_ptr = (ContentPtr)(data);
    const cJSON *content_json = cJSON_CreateObject();
    cJSON_AddItemToObject(content_json, CONTENT_USER, UserManager.base.json.to_cjson(&content_ptr->user));
    cJSON_AddItemToObject(content_json, CONTENT_DEVICE, DeviceManager.base.json.to_cjson(&content_ptr->device));
    cJSON_AddStringToObject(content_json, CONTENT_QUERY, content_ptr->query);
    return content_json;
}

static void content_drop_memory(const ContentPtr content_ptr)
{
    UserManager.base.drop.drop_memery((void *)(&content_ptr->user));
    DeviceManager.base.drop.drop_memery((void *)(&content_ptr->device));
    rt_free(content_ptr->query);
}

const _ContentManager ContentManager = {
    .new = content_new,
    .base = {
        .json = {
            .to_cjson = content_to_cjson},
        .drop = {
            .drop_memery = content_drop_memory,
        }}};