/**
 * @file payload.h
 * @author qr-kou (codinlog@foxmail.com)
 * @brief
 * @version 0.1
 * @date 2021-10-21
 *
 * @copyright Copyright (c) 2021
 *
 */

const char PAYLOAD[] = "payload\0";
const static char PAYLOAD_SERVICE[] = "service\0";
const static char PAYLOAD_ACTION[] = "action\0";

typedef struct
{
    char *service;
    char *action;
} _Payload;