
#include "nlu_handler.h"
#include <finsh.h>
#include <rtthread.h>

void test_nlu_handler()
{

    const User user = UserManager.new("", "");
    const Device device = DeviceManager.new("48d890d762b0", "48d890d762b0", "10f03");
    const Body content = BodyManager.new(user, device, "18度");
    Session session = NluRequest.new(&content);
    Buffer buffer = ByteBuffer.allocate(1024 * 8);
    if (session.client != RT_NULL)
    {
        int res = NluRequest.post(&session, &buffer);
        if (res == 200)
        {
            rt_kprintf("Request Success\n");
            const char *data = ByteBuffer.ref_string(&buffer);
            const cJSON *cjson_parser = cJSON_Parse(data);
            const cJSON *status_cjson = cJSON_GetObjectItem(cjson_parser, STATUS);
            if (!cJSON_IsNull(status_cjson))
            {
                const Status status = StatusManager.from_cjson(status_cjson);
                printf("code:%d\n", status.code);
                printf("err type:%s\n", status.error_type);
                StatusManager.drop_memory(&status);
            }
            const cJSON *semantic_cjson = cJSON_GetObjectItem(cjson_parser, SEMANTIC);
            if (!cJSON_IsNull(semantic_cjson))
            {
                const Semantic semantic = SemanticManager.from_cjson(semantic_cjson);
                printf("semantic.domain:%s\n", semantic.domain);
                printf("semantic.intent:%s\n", semantic.intent);
                printf("semantic.session_complete:%d\n", semantic.session_complete);
                printf("semantic.skill:%s\n", semantic.skill);
                SemanticManager.drop_memory(&semantic);
            }
            const cJSON *payload_cjson = cJSON_GetObjectItem(cjson_parser, PAYLOAD);
            if (!cJSON_IsNull(payload_cjson))
            {
                const Payload payload = PayloadManager.from_cjson(payload_cjson);
                printf("payload.service:%s\n", payload.service);
                printf("payload.action:%s\n", payload.action);
                if (payload.params != RT_NULL)
                {
                    printf("payload.params->degree->norm:%s\n", payload.params->degree->norm);
                    printf("payload.params->degree->orgin:%s\n", payload.params->degree->orgin);
                    printf("payload.params->degree->code:%d\n", payload.params->degree->code);
                }
                else
                {
                    printf("payload.params is null\n");
                }
                PayloadManager.drop_memory(&payload);
            }
            const cJSON *response_cjson = cJSON_GetObjectItem(cjson_parser, RESPONSE);
            if (!cJSON_IsNull(response_cjson))
            {
                const Response response = ResponseManager.from_cjson(response_cjson);
                printf("response.text:%s\n", response.text);
                printf("response.hint:%s\n", response.hint);
                ResponseManager.drop_memory(&response);
            }
            cJSON_Delete(cjson_parser);
        }
    }
    ByteBuffer.drop_memery(&buffer);
    NluRequest.close(&session);
    BodyManager.base.drop.drop_memery(&content);
}

MSH_CMD_EXPORT(test_nlu_handler, test nlu handler);