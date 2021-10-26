/**
 * @file nlu_response.h
 * @author qr-kou (codinlog@foxmail.com)
 * @brief
 * @version 0.1
 * @date 2021-10-22
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "payload/payload.h"
#include "semantic/semantic.h"
#include "status/status.h"
#include "response/response.h"

typedef struct
{
    StatusPtr status;
    SemanticPtr semantic;
} Result, *ResultPtr, *const ResultCPtr;

typedef struct
{
    Result (*from_cjson)(const cJSON *cjson);
    Result (*from_string)(const char *str);
    void (*drop_memory)(const ResultPtr result_ptr);
} _NluResponse;