/**
 * @file semantic.h
 * @author qr-kou (codinlog@foxmail.com)
 * @brief
 * @version 0.1
 * @date 2021-10-20
 *
 * @copyright Copyright (c) 2021
 *
 */

#ifndef __NLU_RESPONSE__SEMANTIC_H__
#define __NLU_RESPONSE__SEMANTIC_H__

#include <cJSON.h>
#include <rtthread.h>

extern const char SEMANTIC[] ;

typedef struct
{
    const char *domain;
    const char *intent;
    const rt_bool_t session_complete;
    const char *skill;
} Semantic, *SemanticPtr, *const CSemanticPtr;

/**
 * @brief
 *
 * @param cjson
 * @return Semantic
 */
static Semantic semantic_from_cjson(const cJSON *cjson);

/**
 * @brief
 *
 * @param semantic_ptr
 */
static void semantic_drop_memory(const SemanticPtr semantic_ptr);

typedef struct
{
    Semantic (*from_cjson)(const cJSON *cjson);
    void (*drop_memory)(const SemanticPtr semantic_ptr);
} _SemanticManager;
extern const _SemanticManager SemanticManager;
#endif //
