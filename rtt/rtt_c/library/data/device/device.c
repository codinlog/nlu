#include "device.h"

const static cJSON *const device_to_cjson(void *device)
{
    const DevicePtr device_ptr = (DevicePtr)(device);
    const cJSON *device_json = cJSON_CreateObject();
    cJSON_AddStringToObject(device_json, DEVICE_MAC_WIFI, device_ptr->mac_wifi);
    cJSON_AddStringToObject(device_json, DEVICE_MAC_VOICE, device_ptr->mac_voice);
    cJSON_AddStringToObject(device_json, DEVICE_MID, device_ptr->mid);
    return device_json;
}

const static Device create_device(const char *mac_wifi, const char *mac_voice, const char *mid)
{
    char *_mac_wifi = strdup(mac_wifi);
    char *_mac_voice = strdup(mac_voice);
    char *_mid = strdup(mid);
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

const struct _DeviceManager DeviceManager = {
    .new = create_device,
    .super = {
        .json = {
            .to_cjson = device_to_cjson,
        },
        .drop = {
            .drop_memery = free_device,
        }}};