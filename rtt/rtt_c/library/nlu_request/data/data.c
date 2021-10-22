/**
 * @file data.c
 * @author qr-kou (codinlog@foxmail.com)
 * @brief
 * @version 0.1
 * @date 2021-10-22
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "data.h"

static Data
create_data(const char *chs)
{
    char *_data = rt_strdup(chs);
    Data data = {
        .data = _data,
    };
    return data;
}

static cJSON *data_to_cjson(void *data)
{
    const DataPtr data_ptr = (DataPtr)(data);
    cJSON *data_json = cJSON_CreateObject();
    cJSON_AddStringToObject(data_json, DATA_DATA, data_ptr->data);
    return data_json;
}

static void free_data(DataPtr data_ptr)
{
    rt_free(data_ptr->data);
}

const _DataManager DataManager = {
    .new = create_data,
    .base = {
        .json = {
            .to_cjson = data_to_cjson,
        },
        .drop = {
            .drop_memery = free_data,
        }}};
