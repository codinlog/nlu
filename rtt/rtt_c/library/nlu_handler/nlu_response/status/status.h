/**
 * @file status.h
 * @author qr-kou (codinlog@foxmail.com)
 * @brief
 * @version 0.1
 * @date 2021-10-20
 *
 * @copyright Copyright (c) 2021
 *
 */
#ifndef __NLU_RESPONSE_STATUS_H__
#define __NLU_RESPONSE_STATUS_H__
#include <CJSON.h>
#include <rtthread.h>
#include <stdint.h>

const static char STATUS[] = "status\0";
const static int ERR_STATUS_FROM_CJSON = -100;
const static char STATUS_CODE[] = "code\0";
const static char STATUS_ERRORTYPE[] = "errorType\0";

typedef struct
{
    const int code;
    const char *error_type;
} Status, *StatusPtr, *const CStatusPtr;

/**
 * @brief 从cjson中返回Status
 *
 * @param cjson
 * @return Status
 */
static Status status_from_cjson(const cJSON *cjson);
/**
 * @brief 释放内存
 *
 * @param status_ptr
 */
static void status_drop_memory(const StatusPtr status_ptr);
typedef struct
{
    Status (*from_cjson)(const cJSON *cjosn);
    void (*drop_memory)(const StatusPtr status_ptr);
} _StatusManager;

extern const _StatusManager StatusManager;
#endif //