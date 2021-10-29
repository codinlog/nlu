/**
 * @file radio.h
 * @author qr-kou (codinlog@foxmail.com)
 * @brief 电台
 * @version 0.1
 * @date 2021-10-29
 *
 * @copyright Copyright (c) 2021
 *
 */

#ifndef __NLU_RESPONSE__LIST_RADIO_H__
#define __NLU_RESPONSE__LIST_RADIO_H__

typedef struct
{
    char *url;
    char *title;
    char *content;
    char *image;
} Radio, *RadioPtr, *const RadioCPtr;

#endif