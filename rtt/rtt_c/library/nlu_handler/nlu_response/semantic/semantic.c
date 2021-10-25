/**
 * @file semantic.c
 * @author qr-kou (codinlog@foxmail.com)
 * @brief
 * @version 0.1
 * @date 2021-10-20
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "semantic.h"

const char SEMANTIC[] = "semantic\0";
const static char SEMANTIC_DOMAIN[] = "domain\0";
const static char SEMANTIC_INTENT[] = "intent\0";
const static char SEMANTIC_SESSION_COMPLETE[] = "sessionComplete\0";
const static char SEMANTIC_SKILL[] = "skill\0";

static Semantic semantic_from_cjson(const cJSON *cjson)
{
    const cJSON *domain_cjson = cJSON_GetObjectItem(cjson, SEMANTIC_DOMAIN);
    const cJSON *intent_cjson = cJSON_GetObjectItem(cjson, SEMANTIC_INTENT);
    const cJSON *session_complete_cjson = cJSON_GetObjectItem(cjson, SEMANTIC_SESSION_COMPLETE);
    const cJSON *skill_cjson = cJSON_GetObjectItem(cjson, SEMANTIC_SKILL);

    char *domain = RT_NULL;
    if (domain_cjson != RT_NULL)
    {
        if (domain_cjson->valuestring != RT_NULL)
        {
            domain = rt_strdup(domain_cjson->valuestring);
        }
    }
    char *intent = RT_NULL;
    if (intent_cjson != RT_NULL)
    {
        if (intent_cjson->valuestring != RT_NULL)
        {
            intent = rt_strdup(intent_cjson->valuestring);
        }
    }
    rt_bool_t session_complete = RT_FALSE;
    if (session_complete_cjson != RT_NULL)
    {
        session_complete = session_complete_cjson->valueint;
    }
    char *skill = RT_NULL;
    if (skill_cjson != RT_NULL)
    {
        if (skill_cjson->valuestring != RT_NULL)
        {
            skill = rt_strdup(skill_cjson->valuestring);
        }
    }
    Semantic semantic = {
        .domain = domain,
        .intent = intent,
        .session_complete = session_complete,
        .skill = skill,
    };
    return semantic;
}

static void semantic_drop_memory(const SemanticPtr semantic_ptr)
{
    rt_free(semantic_ptr->domain);
    rt_free(semantic_ptr->intent);
    rt_free(semantic_ptr->skill);
}

const _SemanticManager SemanticManager = {
    .from_cjson = semantic_from_cjson,
    .drop_memory = semantic_drop_memory,
};