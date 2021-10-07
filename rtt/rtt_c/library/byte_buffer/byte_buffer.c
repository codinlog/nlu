#include "byte_buffer.h"

static Buffer buffer_with_capacity(size_t capacity)
{
    uint8_t *bucket = (uint8_t)(rt_malloc(capacity * sizeof(uint8_t)));
    Buffer buffer = {
        .capacity = capacity,
        .buffer = bucket,
        .position = 0,
    };
    return buffer;
}