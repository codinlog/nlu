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

const static char SEMANTIC_DOMAIN[] = "domain\0";
const static char SEMANTIC_SESSIONCOMPLETE[] = "sessionComplete\0";
const static char SEMANTIC_DOMAIN[] = "domain\0";
const static char SEMANTIC_SKILL[] = "skill\0";
typedef struct {
    const char *domain;
    const char *intent;
    const bool sessionComplete;
    const char *skill;
} _Semantic;