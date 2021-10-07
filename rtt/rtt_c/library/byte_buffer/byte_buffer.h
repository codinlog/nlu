#include <stdint.h>
#ifndef __BYTE_BUFFER_H__
#define __BYTE_BUFFER_H__

typedef struct
{
    int8_t *buffer;
    size_t capacity;
    size_t position;
} Buffer, *BufferPtr;

/**
 * @brief
 * 
 * @param capacity 
 * @return Buffer 
 */
static Buffer buffer_with_capacity(size_t capacity);
/**
 * @brief
 *
 * @param buffer_ptr
 * @param byte
 */
static void buffer_put_byte(BufferPtr buffer_ptr, uint8_t byte);
/**
 * @brief
 *
 * @param buffer_ptr
 * @param byte
 * @param len
 */
static void buffer_put_bytes(BufferPtr buffer_ptr, uint8_t *bytes, size_t len);
/**
 * @brief
 *
 * @param buffer_ptr
 * @return uint8_t
 */
static uint8_t buffer_get_byte(BufferPtr *buffer_ptr);
static struct _ByteBuffer
{
    Buffer (*with_capacity)(size_t capacity);
    void (*put_byte)(BufferPtr buffer_ptr, uint8_t byte);
    uint8_t (*get_byte)(BufferPtr *buffer_ptr);
};

extern const struct _ByteBuffer ByteBuffer;

#endif