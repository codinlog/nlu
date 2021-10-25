/**
 * @file response.h
 * @author qr-kou (codinlog@foxmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-10-21
 * 
 * @copyright Copyright (c) 2021
 * 
 */
const char RESPONSE[] = "response\0";
const static char RESPONSE_TEXT[] = "text\0";
const static char RESPONSE_HINT[] = "hint\0";

typedef struct {
    const char * text;
    const char * hint;
} _Response;