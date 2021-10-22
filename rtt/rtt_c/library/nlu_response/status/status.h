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

#include <stdint.h>

const static char STATUS_CODE[] = "code\0";
const static char STATUS_ERRORTYPE[] = "errorType\0";
typedef struct 
{
    int8_t code;
    char* errorType;
} _Status;