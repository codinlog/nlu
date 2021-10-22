#include "nlu.h"

char *create_request_body(const Content content)
{
    const cJSON *const content_cjson = ContentManager.base.json.to_cjson(&content);
    const char *const content_json = cJSON_PrintUnformatted(content_cjson);
    cJSON_Delete(content_cjson);
    const char *const encrypt = aes_128_cbc_encrypt(content_json, strlen(content_json));
    rt_free(content_json);
    const char *const base64 = base64_en(encrypt, strlen(encrypt));
    rt_free(encrypt);
    const Data data = DataManager.new(base64);
    rt_free(base64);
    const cJSON *const data_cjson = DataManager.base.json.to_cjson(&data);
    DataManager.base.drop.drop_memery(&data);
    const char *const data_json = cJSON_PrintUnformatted(data_cjson);
    cJSON_Delete(data_cjson);
    return data_json;
}
char *create_request_auth_header(const char *const data, const size_t len)
{
    char *auth_data = (char *)rt_malloc((len + 40) * sizeof(char));
    const time_t timestamp = now_sec_from_unix_epoch();
    sprintf(auth_data, "%s%d", data, timestamp);
    const char *signature = hmac_sha256_encrypt(auth_data, strlen(auth_data));
    rt_free(auth_data);
    // Appkey={},Timestamp={},Signature={}
    // Appkey长度:(len(Appkey=)+(len(Appkey))) <= 20 < 30
    // Timestamp长度: <= 20 + len(Timestamp=)  < 40
    // Signature长度: == 32 + len(Signature=) < 50
    // time_t 为无符号长整型，最大2^64 - 1,长度20位
    char auth_header[120];
    sprintf(auth_header, "Appkey=%s,Timestamp=%ld,Signature=%s", APP_KEY, timestamp, signature);
    const char *const auth = strdup(auth_header);
    rt_free(signature);
    return auth;
}

void create_request(const char *url, const char *data)
{
    unsigned char *buffer = RT_NULL;
    struct webclient_session *session = RT_NULL;
    buffer = (unsigned char *)web_malloc(2048);
    if (buffer == RT_NULL)
    {
        rt_kprintf("no memory for receive response buffer.\n");
        goto __exit;
    }
    /* create webclient session and set header response size */
    session = webclient_session_create(1024 * 20);
    if (session == RT_NULL)
    {
        goto __exit;
    }

    /* build header for upload */
    const char *auth_header = create_request_auth_header(data, strlen(data));
    printf("auth_header:%s\n", auth_header);
    webclient_header_fields_add(session, "Cache-Control: no-cache\r\n");
    webclient_header_fields_add(session, "Host: nlu.gree.com\r\n");
    webclient_header_fields_add(session, "Content-Type: application/json;charset=UTF-8\r\n");
    webclient_header_fields_add(session, "Authorization: %s\r\n", auth_header);
    webclient_header_fields_add(session, "Content-Length: %d\r\n", strlen(data));
    rt_free(auth_header);
    /* send POST request by default header */
    int resp_status = webclient_post(session, url, data);
    // if (resp_status != 200)
    // {
    //     rt_kprintf("webclient POST request failed, response(%d) error.\n", resp_status);
    //     goto __exit;
    // }
    rt_kprintf("webclient post response data: \n");
    do
    {
        int bytes_read = webclient_read(session, buffer, POST_RESP_BUFSZ);
        if (bytes_read <= 0)
        {
            break;
        }

        for (int index = 0; index < bytes_read; index++)
        {
            rt_kprintf("%c", buffer[index]);
        }
    } while (1);

    rt_kprintf("\n");

__exit:
    if (session)
    {
        webclient_close(session);
    }

    if (buffer)
    {
        web_free(buffer);
    }
}