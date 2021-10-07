#include <stdint.h>

#ifndef __CONSTS_H__
#define __CONSTS_H__
//十六进制
const static char HEX[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
/**
 * @brief 请求地址
 *
 */
const static char ADDRESS[] = "https://nlu.gree.com/api/t2c/prod/ap/query\0";
/**
 * @brief https 请求类型
 *
 */
const static char CONTENT_TYPE[] = "application/json;charset=UTF-8\0";
/**
 * @brief 密钥
 *
 */
const static char KEY[] = "df8daf7e2a81ded2\0";
/**
 * @brief 初始化向量
 *
 */
const static char IV[] = "df8daf7e2a81ded2\0";
/**
 * @brief 程序认证密钥
 *
 */
const static char APP_KEY[] = "3bf10e1a800051d\0";

#endif // __CONSTS_H__