/**
 * @file byte_buffer.h
 * @author qr-kou (codinlog@foxmail.com)
 * @brief
 * @version 0.1
 * @date 2021-10-22
 *
 * @copyright Copyright (c) 2021
 *
 */
#include <rtthread.h>
#include <stdint.h>
#ifndef __BYTE_BUFFER_H__
#define __BYTE_BUFFER_H__
//扩容因子
const static float EXPANSION_FACTOR = 0.75f;
const static size_t DEFAULT_CAPACITY = 16;
typedef struct
{
    /**
     * @brief 字节缓存
     *
     */
    int8_t *buffer;
    /**
     * @brief 当前位置
     *
     */
    size_t position;
    size_t limit;
    /**
     * @brief 自动扩容后的大小
     *
     */
    size_t alloc_capacity;
    /**
     * @brief 初始化容量
     *
     */
    const size_t capacity;
} Buffer, *BufferPtr;

static Buffer buffer_default_capacity();
/**
 * @brief
 *
 * @param capacity
 * @return Buffer
 */
static Buffer buffer_with_capacity(const size_t capacity);
/**
 * @brief
 *
 * @param buffer_ptr
 * @param byte
 */
static void buffer_put_byte(const BufferPtr buffer_ptr, const int8_t byte);
/**
 * @brief
 *
 * @param buffer_ptr
 * @param byte
 * @param len
 */
static void buffer_put_bytes(const BufferPtr buffer_ptr, const int8_t *bytes, const size_t len);
/**
 * @brief 获取单个字节，不安全不会检查溢出
 *
 * @param buffer_ptr
 * @return int8_t
 */
static int8_t buffer_get_byte(const BufferPtr buffer_ptr);
static int8_t buffer_get_position_byte(const BufferPtr buffer_ptr, size_t position);

/**
 * @brief 获取指定位置长度bytes，不安全不会检查溢出
 *
 * @param buffer_ptr
 * @param start
 * @param size
 * @return int8_t*
 */
static int8_t *buffer_get_bytes(const BufferPtr buffer_ptr, const size_t size);
/**
 * @brief 返回start ~ end 范围内byte数组，闭区间
 *
 * @param buffer_ptr
 * @param start
 * @param end
 * @return int8_t*
 */
static int8_t *buffer_get_range_bytes(const BufferPtr buffer_ptr, const size_t start, const size_t end);
/**
 * @brief 检查是否需要resize
 *
 * @param buffer_ptr
 * @param put_len
 */
static void buffer_check_resize(const BufferPtr buffer_ptr, const size_t put_len);
/**
 * @brief 计算扩容大小 alloc_capacity = alloc_capacity * (EXPANSION_FACTOR + 1);
 *
 * @param now_size
 * @param position
 * @param put_len
 * @return size_t
 */
static size_t buffer_calculate_resize(const size_t now_size, const size_t position, const size_t put_len);
/**
 * @brief 当position >= new_capacity时，扩容buffer,仅内部使用
 *
 * @param buffer_ptr
 */
static void buffer_resize(const BufferPtr buffer_ptr, const size_t size);
/**
 * @brief 将buffer内容置为 0
 *
 * @param buffer_ptr
 */
static void buffer_clear(const BufferPtr buffer_ptr);
/**
 * @brief 将buffer内容清除，同时buffer恢复初始大小
 *
 * @param buffer_ptr
 */
static void buffer_reset(const BufferPtr buffer_ptr);
/**
 * @brief 释放buffer
 *
 * @param buffer_ptr
 */
static void buffer_free_memory(const BufferPtr buffer_ptr);
/**
 * @brief 获取以'\0'结尾的字符串应用，所有权仍属于BufferPtr,请勿释放
 *
 * @param buffer_ptr
 * @return char*
 */
static char *buffer_ref_string(const BufferPtr buffer_ptr);
typedef struct
{
    Buffer (*allocate)(const size_t capacity);
    Buffer (*allocate_default)();
    void (*put_byte)(const BufferPtr buffer_ptr, const int8_t byte);
    int8_t (*get_byte)(const BufferPtr buffer_ptr);
    int8_t (*get_position_byte)(const BufferPtr buffer_ptr, size_t position);
    void (*put_bytes)(const BufferPtr buffer_ptr, const int8_t *bytes, const size_t len);
    int8_t *(*get_bytes)(const BufferPtr buffer_ptr, const size_t size);
    int8_t *(*get_range_bytes)(const BufferPtr buffer_ptr, const size_t start, const size_t end);
    void (*clear)(const BufferPtr buffer_ptr);
    void (*reset)(const BufferPtr buffer_ptr);
    void (*drop_memery)(const BufferPtr buffer_ptr);
    char *(*ref_string)(const BufferPtr buffer);
} _ByteBuffer;

extern const _ByteBuffer ByteBuffer;

#endif