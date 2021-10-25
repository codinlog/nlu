/**
 * @file nlu_request.h
 * @author qr-kou(codinlog@foxmail.com)
 * @brief
 * @version 0.1
 * @date 2021-10-22
 *
 * @copyright Copyright (c) 2021
 *
 */
#ifndef __NLU_REQUEST_H__
#define __NLU_REQUEST_H__

#include "consts.h"
#include "content/content.h"
#include "data/data.h"
#include "device/device.h"
#include "user/user.h"

#include "library/byte_buffer/byte_buffer.h"
#include <webclient.h>

typedef struct
{
    const struct webclient_session *client;
    const char *body;
} Session, *SessionPtr, *const CSessionPtr;

/**
 * @brief 创建webclient session实例，并添加响应请求头
 *
 * @param content_ptr
 * @return Session
 */
static Session request_new_session(const CContentPtr content_ptr);

/**
 * @brief 完成post请求
 *
 * @param session_ptr
 * @param buffer
 * @param body
 */
static int request_finish_post(const SessionPtr session_ptr, const BufferPtr buffer_ptr);

/**
 * @brief
 *
 * @param content_ptr
 * @return char*
 */
static char *request_new_body(const CContentPtr content_ptr);

/**
 * @brief
 *
 * @param body
 * @return char*
 */
static char *request_new_auth(const char *body);

/**
 * @brief 释放申请空间
 *
 * @param session_ptr
 */
static void request_close(const SessionPtr session_ptr);

typedef struct
{
    Session (*new)(const CContentPtr content_ptr);
    int (*post)(const SessionPtr session_ptr, const BufferPtr buffer_ptr);
    void (*close)(const SessionPtr session_ptr);
} _NluRequest;

extern const _NluRequest NluRequest;
#endif //