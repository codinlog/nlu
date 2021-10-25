/**
 * @file status.c
 * @author qr-kou (codinlog@foxmail.com)
 * @brief
 * @version 0.1
 * @date 2021-10-20
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "status.h"

const char STATUS[] = "status\0";
const static int ERR_STATUS_FROM_CJSON = -100;
const static char STATUS_CODE[] = "code\0";
const static char STATUS_ERRORTYPE[] = "errorType\0";

static Status status_from_cjson(const cJSON *cjson)
{
    const cJSON *code_cjson = cJSON_GetObjectItem(cjson, STATUS_CODE);
    const cJSON *error_type_cjson = cJSON_GetObjectItem(cjson, STATUS_ERRORTYPE);

    int code = ERR_STATUS_FROM_CJSON;
    if (code_cjson != RT_NULL)
    {
        code = code_cjson->valueint;
    }
    char *error_type = RT_NULL;
    if (error_type_cjson != RT_NULL)
    {
        if (error_type_cjson->valuestring != RT_NULL)
        {
            error_type = rt_strdup(error_type_cjson->valuestring);
        }
    }
    Status status = {
        .code = code,
        .error_type = error_type,
    };
    return status;
}

static void status_drop_memory(const StatusPtr status_ptr)
{
    rt_free(status_ptr->error_type);
}

const _StatusManager StatusManager = {
    .from_cjson = status_from_cjson,
    .drop_memory = status_drop_memory,
};