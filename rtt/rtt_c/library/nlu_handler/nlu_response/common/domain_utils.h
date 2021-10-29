

#ifndef __NLU_RESPONSE_COMMON_H__
#define __NLU_RESPONSE_COMMON_H__

#include "domain_consts.h"

typedef enum
{
    MUSIC = 1,
} DomainTypeEnum;

inline static DomainTypeEnum semantic_domain_type(const char *domain)
{
    if (rt_strcmp(domain, DOMAIN_MUSTC) == 0)
    {
        return MUSIC;
    }
}

#endif