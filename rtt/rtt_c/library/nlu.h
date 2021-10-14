#include "data/data.h"
#include "util.h"
#include <webclient.h>
#include "consts.h"
#ifndef __NLU_H__
#define __NLU_H__

const static int POST_RESP_BUFSZ = 1024;
const static int POST_HEADER_BUFSZ = 1024;
/**
 * @brief Create a request body object
 *
 * @param content
 * @return char*
 */
    char *
    create_request_body(const Content content);
char *create_request_auth_header(const char *const, const size_t);
void create_request(const char *url, const char *data);
#endif
