#include <stdint.h>

#ifndef __CONSTS_H__
#define __CONSTS_H__
//加密密钥
const static uint8_t KEY[] = {"0123456789abcdef\0"};
//初始化向量
const static uint8_t IV[] = {"0123456789abcdef\0"};
//十六进制
const static char HEX[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};

#endif // __CONSTS_H__