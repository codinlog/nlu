/**
 * @file joke.h
 * @author qr-kou (codinlog@foxmail.com)
 * @brief 笑话
 * @version 0.1
 * @date 2021-10-29
 *
 * @copyright Copyright (c) 2021
 *
 */

#ifndef __NLU_RESPONSE_LIST_JOKE_H__
#define __NLU_RESPONSE_LIST_JOKE_H__

typedef struct
{
    char *url;
    char *content;
} Joke, *JokePtr, *const JokeCPtr;

typedef struct
{

} _JokeManager;

extern const _JokeManager JokeManager;

#endif