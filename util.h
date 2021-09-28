#include "base64/base64.h"
#include "consts.h"
#include "hmac_sha256/hmac_sha256.h"
#include "tiny_aes/aes.h"
#include <time.h>
#ifndef __UTIL_H__
#define __UTIL_H__
//aes *************************************************************************************************************
void aes_128_cbc_init();
char *aes_128_cbc_encrypt(const uint8_t *, const size_t);
//hmac256*************************************************************************************************************
char *hmac_sha256_encrypt(const uint8_t *, const size_t);
//base64 *************************************************************************************************************
char *base64_en(const char *, const size_t);
//tohex*************************************************************************************************************
char *to_hex(const char *, const size_t);
uint32_t now_sec_from_unix_epoch();
#endif // __UTIL_H__