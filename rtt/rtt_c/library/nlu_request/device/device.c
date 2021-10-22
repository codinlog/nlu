/**
 * @file device.c
 * @author qr-kou (codinlog@foxmail.com)
 * @brief
 * @version 0.1
 * @date 2021-10-22
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "device.h"

static cJSON *device_to_cjson(void *device)
{
    const DevicePtr device_ptr = (DevicePtr)(device);
    const cJSON *device_json = cJSON_CreateObject();
    cJSON_AddStringToObject(device_json, DEVICE_MAC_WIFI, device_ptr->mac_wifi);
    cJSON_AddStringToObject(device_json, DEVICE_MAC_VOICE, device_ptr->mac_voice);
    cJSON_AddStringToObject(device_json, DEVICE_MID, device_ptr->mid);
    return device_json;
}

static Device create_device(const char *mac_wifi, const char *mac_voice, const char *mid)
{
    char *_mac_wifi = rt_strdup(mac_wifi);
    char *_mac_voice = rt_strdup(mac_voice);
    char *_mid = rt_strdup(mid);
    const Device device = {
        .mac_wifi = _mac_wifi,
        .mac_voice = _mac_voice,
        .mid = _mid,
    };
    return device;
}
static void free_device(DevicePtr device_ptr)
{
    rt_free(device_ptr->mac_wifi);
    rt_free(device_ptr->mac_voice);
    rt_free(device_ptr->mid);
}

const _DeviceManager DeviceManager = {
    .new = create_device,
    .base = {
        .json = {
            .to_cjson = device_to_cjson,
        },
        .drop = {
            .drop_memery = free_device,
        }}};