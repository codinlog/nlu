#include "data/data.h"
#include "util.h"
#ifndef __NLU_H__
#define __NLU_H__
/**
 * @brief Create a request body object
 *
 * @param content
 * @return char*
 */
char *create_request_body(const Content content);
char *create_request_auth_header(const char *const, const size_t);
#endif
