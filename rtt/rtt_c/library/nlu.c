#include "nlu.h"

char *create_request_body(const Content content)
{
    aes_128_cbc_init();
    //declare content_cjson type cJSON
    const cJSON *const content_cjson = ContentManager.super.json.to_cjson(&content);
    //declare content_json type char *
    const char *const content_json = cJSON_PrintUnformatted(content_cjson);
    // free content_cjson type cJSON
    cJSON_Delete(content_cjson);
    //declare encrypt type char *
    const char *const encrypt = aes_128_cbc_encrypt(content_json, strlen(content_json));
    //free content_json type char *
    rt_free(content_json);
    //declare base64 type char *
    const char *const base64 = base64_en(encrypt, strlen(encrypt));
    //free encrypt type char *
    rt_free(encrypt);
    printf("base64:%s\n", base64);
    const Data data = DataManager.new(base64);
    //free base64 type char *
    rt_free(base64);
    const cJSON *const data_cjson = DataManager.super.json.to_cjson(&data);
    const char *const data_json = cJSON_PrintUnformatted(data_cjson);
    cJSON_Delete(data_cjson);
    printf("data_json:%s\n", data_json);
    return data_json;
}
char *create_request_auth_header(const char *const data, const size_t len)
{
    //Appkey={},Timestamp={},Signature={}
    //Appkey长度:(len(Appkey=)+(len(Appkey))) <= 20 < 30
    //Timestamp长度: <= 20 + len(Timestamp=)  < 40
    //Signature长度: == 32 + len(Signature=) < 50
    char auth_header[120];
    // time_t 为无符号长整型，最大2^64 - 1,长度20位
    char *auth_data = (char *)rt_malloc((len + 40) * sizeof(char));
    const time_t timestamp = now_sec_from_unix_epoch();
    sprintf(auth_data, "%s%d", data, timestamp);
    printf("create_request_auth_header:%s\n", auth_data);
    const char *const signature = hmac_sha256_encrypt(auth_data, strlen(auth_data));
    sprintf(auth_header, "Appkey=%s,Timestamp=%d,Signature=%s", APP_KEY, timestamp, signature);
    const char *const auth = strdup(auth_header);
    rt_free(auth_data);
    return auth;
}
