/**
 * @file data.h
 * @author qr-kou (codinlog@foxmail.com)
 * @brief
 * @version 0.1
 * @date 2021-10-22
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "library/nlu_handler/common/common.h"
#include "library/nlu_handler/nlu_request/body/body.h"
#include "library/nlu_handler/nlu_request/device/device.h"
#include "library/nlu_handler/nlu_request/user/user.h"

#ifndef __DATA_DATA_H__
#define __DATA_DATA_USER_H__

typedef struct
{
    char *data;
} Data, *DataPtr, *const CDataPtr;

typedef struct
{
     Data (*new)(const char *);
    Base base;
} _DataManager;

/**
 * @brief
 *
 */
extern const _DataManager DataManager;
#endif