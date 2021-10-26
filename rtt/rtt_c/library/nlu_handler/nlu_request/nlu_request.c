/**
 * @file nlu_request.c
 * @author qr-kou (codinlog@foxmail.com)
 * @brief
 * @version 0.1
 * @date 2021-10-22
 *
 * @copyright Copyright (c) 2021
 *
 */
#include "nlu_request.h"

inline static char *request_new_auth(const char *body)
{
    char *auth_data = (char *)rt_malloc((rt_strlen(body) + 40) * sizeof(char));
    const time_t timestamp = now_sec_from_unix_epoch();
    sprintf(auth_data, "%s%d", body, timestamp);
    const char *signature = hmac_sha256_encrypt(auth_data, strlen(auth_data));
    rt_free(auth_data);
    // Appkey={},Timestamp={},Signature={}
    // Appkey长度:(len(Appkey=)+(len(Appkey))) <= 20 < 30
    // Timestamp长度: <= 20 + len(Timestamp=)  < 40
    // Signature长度: == 32 + len(Signature=) < 50
    // time_t 为无符号长整型，最大2^64 - 1,长度20位
    char auth_header[120];
    sprintf(auth_header, "Appkey=%s,Timestamp=%ld,Signature=%s", APP_KEY, timestamp, signature);
    rt_free(signature);
    return rt_strdup(auth_header);
}

inline static char *request_new_body(const BodyPtr content_ptr)
{
    const cJSON *content_cjson = BodyManager.base.json.to_cjson(content_ptr);
    const char *content_json = cJSON_PrintUnformatted(content_cjson);
    cJSON_Delete(content_cjson);
    const char *encrypt = aes_128_cbc_encrypt(content_json, strlen(content_json));
    rt_free(content_json);
    const char *base64 = base64_en(encrypt, strlen(encrypt));
    rt_free(encrypt);
    const Data data = DataManager.new(base64);
    rt_free(base64);
    const cJSON *data_cjson = DataManager.base.json.to_cjson(&data);
    DataManager.base.drop.drop_memery(&data);
    const char *data_json = cJSON_PrintUnformatted(data_cjson);
    cJSON_Delete(data_cjson);
    return data_json;
}

static Session request_new_session(const BodyPtr content_ptr)
{
    struct webclient_session *client = webclient_session_create(1024);
    char *body = RT_NULL;
    if (client != RT_NULL)
    {
        body = request_new_body(content_ptr);
        const char *auth = request_new_auth(body);
        webclient_header_fields_add(client, "Authorization: %s\r\n", auth);
        rt_free(auth);
        webclient_header_fields_add(client, "Content-Length: %d\r\n", strlen(body));
        webclient_header_fields_add(client, "Cache-Control: no-cache\r\n");
        webclient_header_fields_add(client, "Host: nlu.gree.com\r\n");
        webclient_header_fields_add(client, "Body-Type: application/json;charset=UTF-8\r\n");
    }
    Session session = {
        .client = client,
        .body = body,
    };
    return session;
}

static int request_finish_post(const SessionPtr session_ptr, const BufferPtr buffer_ptr)
{
    int resp_status = webclient_post(session_ptr->client, ADDRESS, session_ptr->body);
    char *buffer = (char *)rt_malloc(1024);
    do
    {
        int bytes_read = webclient_read(session_ptr->client, buffer, 1024);
        if (bytes_read <= 0)
        {
            break;
        }
        ByteBuffer.put_bytes(buffer_ptr, buffer, bytes_read);
    } while (1);
    rt_free(buffer);
    return resp_status;
}

static void request_close(const SessionPtr session_ptr)
{
    if (session_ptr->client)
    {
        webclient_close(session_ptr->client);
    }
    rt_free(session_ptr->body);
}

const _NluRequest NluRequest = {
    .new = request_new_session,
    .post = request_finish_post,
    .close = request_close,
};