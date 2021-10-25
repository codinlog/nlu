/**
 * @file device.h
 * @author qr-kou (codinlog@foxmail.com)
 * @brief
 * @version 0.1
 * @date 2021-10-22
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "library/nlu_request/common.h"

#ifndef __DATA_DEVICE_DEVICE_H__
#define __DATA_DEVICE_DEVICE_H__

const static char DEVICE_MAC_WIFI[] = "macWifi\0";
const static char DEVICE_MAC_VOICE[] = "macVoice\0";
const static char DEVICE_MID[] = "mid\0";

typedef struct
{
    const char *mac_wifi;
    const char *mac_voice;
    const char *mid;
} Device, *DevicePtr,*const CDevicePtr;

/**
 * @brief Create a device object
 *
 * @param mac_wifi
 * @param mac_voice
 * @param mid
 * @return const Device
 */
static Device device_new(const char *mac_wifi, const char *mac_voice, const char *mid);

/**
 * @brief convert device  to cjson object
 *
 * @param device
 * @return const cJSON* const
 */
static cJSON *device_to_cjson(void *device);

/**
 * @brief drop device memery
 */
static void device_drop_memory(const DevicePtr device_ptr);

typedef struct
{
    const Device (*new)(const char *mac_wifi, const char *mac_voice, const char *mid);
    Base base;
} _DeviceManager;

/**
 * @brief
 *    Usage:
 *      create device instance:
 *         const Device device  = DeviceManager.new(mac_wifi,mac_voice,mid);
 *      free device instance:
 *         DeviceManager.base.drop.drop_memery(&device);
 *      convert device to cjson:
 *          DeviceManager.base.json.to_json(&device);
 */
extern const _DeviceManager DeviceManager;
#endif