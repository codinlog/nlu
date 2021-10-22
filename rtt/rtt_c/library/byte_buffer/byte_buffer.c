#include "byte_buffer.h"

static Buffer buffer_default_capacity()
{
    return buffer_with_capacity(DEFAULT_CAPACITY);
}

static Buffer
buffer_with_capacity(const size_t capacity)
{
    int8_t *bucket = (int8_t *)rt_malloc(capacity * sizeof(int8_t));
    Buffer buffer = {
        .buffer = bucket,
        .position = 0,
        .limit = 0,
        .alloc_capacity = capacity,
        .capacity = capacity,
    };
    return buffer;
}

static void buffer_put_byte(const BufferPtr buffer_ptr, const int8_t byte)
{
    buffer_check_resize(buffer_ptr, 1);
    buffer_ptr->buffer[buffer_ptr->limit++] = byte;
}

static void buffer_put_bytes(const BufferPtr buffer_ptr, const int8_t *bytes, const size_t len)
{
    buffer_check_resize(buffer_ptr, len);
    for (size_t i = 0; i < len; i++)
    {
        buffer_put_byte(buffer_ptr, bytes[i]);
    }
}

static int8_t buffer_get_byte(const BufferPtr buffer_ptr)
{
    if (buffer_ptr->position < buffer_ptr->limit)
    {
        return buffer_ptr->buffer[buffer_ptr->position++];
    }
    return RT_NULL;
}

static int8_t buffer_get_position_byte(const BufferPtr buffer_ptr, size_t position)
{
    if (position < buffer_ptr->limit)
    {
        return buffer_ptr->buffer[position];
    }
    return RT_NULL;
}

static int8_t *buffer_get_bytes(const BufferPtr buffer_ptr, const size_t size)
{
    if (buffer_ptr->limit - buffer_ptr->position >= size)
    {
        int8_t *buffer = (int8_t *)rt_malloc(size * sizeof(int8_t));
        for (size_t i = 0; i < size; i++)
        {
            buffer[i] = buffer_get_byte(buffer_ptr);
        }
        return buffer;
    }
    return RT_NULL;
}

static int8_t *buffer_get_range_bytes(const BufferPtr buffer_ptr, const size_t start, const size_t end)
{
    if (start >= end || end >= buffer_ptr->limit)
    {
        return RT_NULL;
    }
    int8_t *buffer = (int8_t *)rt_malloc((end - start + 1) * sizeof(int8_t));
    for (size_t i = start; i <= end; i++)
    {
        buffer[i - start] = buffer_ptr->buffer[i];
    }
    return buffer;
}

static void buffer_check_resize(const BufferPtr buffer_ptr, const size_t put_len)
{
    if (buffer_ptr->alloc_capacity - buffer_ptr->limit < put_len)
    {
        const size_t size = buffer_calculate_resize(buffer_ptr->alloc_capacity, buffer_ptr->limit, put_len);
        buffer_resize(buffer_ptr, size);
    }
}

static size_t buffer_calculate_resize(const size_t now_size, const size_t limit, const size_t put_len)
{
    size_t size = (size_t)(EXPANSION_FACTOR * now_size) + now_size;
    if (size - limit < put_len)
    {
        size = buffer_calculate_resize(size, limit, put_len);
    }
    return size;
}

static void buffer_resize(const BufferPtr buffer_ptr, const size_t size)
{
    buffer_ptr->buffer = (int8_t *)rt_realloc(buffer_ptr->buffer, size * sizeof(int8_t));
    buffer_ptr->alloc_capacity = size;
}

static void buffer_clear(const BufferPtr buffer_ptr)
{
    buffer_ptr->buffer = (int8_t *)rt_memset(buffer_ptr->buffer, 0, buffer_ptr->alloc_capacity * sizeof(int8_t));
    buffer_ptr->limit = 0;
    buffer_ptr->position = 0;
}

static void buffer_reset(const BufferPtr buffer_ptr)
{
    buffer_ptr->alloc_capacity = buffer_ptr->capacity;
    buffer_ptr->buffer = (int8_t *)rt_realloc(buffer_ptr->buffer, buffer_ptr->capacity * sizeof(int8_t));
    buffer_clear(buffer_ptr);
}

static void buffer_drop_memory(const BufferPtr buffer_ptr)
{
    rt_free(buffer_ptr->buffer);
}

static char *buffer_to_string(const BufferPtr buffer_ptr)
{
    char *str = (char *)rt_malloc((buffer_ptr->limit + 1) * sizeof(int8_t));
    rt_memcpy(str, buffer_ptr->buffer, buffer_ptr->limit);
    str[buffer_ptr->limit] = '\0';
    return str;
}

const _ByteBuffer ByteBuffer = {
    .allocate = buffer_with_capacity,
    .allocate_default = buffer_default_capacity,
    .put_byte = buffer_put_byte,
    .put_bytes = buffer_put_bytes,
    .get_byte = buffer_get_byte,
    .get_position_byte = buffer_get_position_byte,
    .get_range_bytes = buffer_get_range_bytes,
    .get_bytes = buffer_get_bytes,
    .clear = buffer_clear,
    .reset = buffer_reset,
    .drop_memery = buffer_drop_memory,
    .to_string = buffer_to_string,
};
