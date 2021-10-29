/**
 * @file poem.h
 * @author qr-kou (codinlog@foxmail.com)
 * @brief 诗
 * @version 0.1
 * @date 2021-10-29
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef __NLU_RESPONSE_LIST_POEM_H__
#define __NLU_RESPONSE_LIST_POEM_H__

typedef struct{

    char *type;
    char *url;
    char *title;
    char *content;
    char *author;
    char *dynasty;
} Poem,*PoemPtr,*const PoemCPtr;

#endif