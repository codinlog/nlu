#include "data.h"

const static Data create_data(const char *chs)
{
    char *_data = strdup(chs);
    Data data = {
        .data = _data,
    };
    return data;
}

const static cJSON *data_to_cjson(void *data)
{
    const DataPtr data_ptr = (DataPtr)(data);
    cJSON *data_json = cJSON_CreateObject();
    cJSON_AddStringToObject(data_json, DATA_DATA, data_ptr->data);
    return data_json;
}

static void free_data(DataPtr data_ptr)
{
    rt_free(data_ptr->data);
}

const struct _DataManager DataManager = {
    .new = create_data,
    .super = {
        .json = {
            .to_cjson = data_to_cjson,
        },
        .drop = {
            .drop_memery = free_data,
        }}};
