#include "library/data/common.h"

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
} Device, *DevicePtr;
/**
 * @brief convert device  to cjson object
 *
 * @param device
 * @return const cJSON* const 
 */
static cJSON *device_to_cjson(void *device);
/**
 * @brief Create a device object
 *
 * @param mac_wifi
 * @param mac_voice
 * @param mid
 * @return const Device
 */
static Device create_device(const char *mac_wifi, const char *mac_voice, const char *mid);
/**
 * @brief drop device memery
 */
static void free_device(DevicePtr device_ptr);
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