/**
 * @file list.h
 * @author qr-kou (codinlog@foxmail.com)
 * @brief
 * @version 0.1
 * @date 2021-10-26
 *
 * @copyright Copyright (c) 2021
 *
 */

#ifndef __NLU_RESPONSE_LIST_H__
#define __NLU_RESPONSE_LIST_H__

typedef void *AnyPtr;

#include "library/nlu_handler/nlu_response/util.h"
#include "music/music.h"
#include "library/nlu_handler/nlu_response/common/domain_utils.h"

extern const char LIST[];



typedef struct
{
    /**
     * @brief list大小，不推荐直接访问
     *
     */
    size_t _size;
    /**
     * @brief 访问游标
     *
     */
    size_t _cursor;
    /**
     * @brief 列表,不推荐直接访问
     *
     */
    AnyPtr *_item;
} List, *ListPtr, *const ListCPtr;

typedef struct
{
    List (*from_cjson)(const cJSON *cjson, DomainTypeEnum type);
    ListPtr (*from_cjson_to_cptr)(const cJSON *cjson, DomainTypeEnum type);
    rt_bool_t (*has_next)(const ListPtr list_ptr);
    AnyPtr (*next)(const ListPtr list_ptr);
    AnyPtr (*at)(const ListPtr list_ptr, const size_t position);
    void (*foreach)(const ListPtr list_ptr, void (*callback)(AnyPtr item));
    void (*drop_memory)(const ListPtr list_ptr, DomainTypeEnum type);
    void (*drop_memory_and_self)(const ListPtr list_ptr, DomainTypeEnum type);
} _ListManager;

extern const _ListManager ListManager;

#endif /* __NLU_RESPONSE_LIST*/