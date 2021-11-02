
#include "nlu_handler.h"
#include <finsh.h>
#include <rtthread.h>

void test_nlu_handler()
{

    const User user = UserManager.new("", "");
    const Device device = DeviceManager.new("48d890d762b0", "48d890d762b0", "10f03");
    const Body content = BodyManager.new(user, device, "播放红莲华");
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
            const cJSON *list_cjosn = cJSON_GetObjectItem(cjson_parser, LIST);
            if (!cJSON_IsNull(response_cjson))
            {
                const List list = ListManager.from_cjson(list_cjosn, MUSIC);
                while (ListManager.has_next(&list))
                {
                    MusicPtr music_ptr = (MusicPtr)ListManager.next(&list);
                    printf("music song:%s\n", music_ptr->song);
                    printf("music url:%s\n", music_ptr->url);
                    printf("music id:%s\n", music_ptr->song_id);
                    printf("music singer:%s\n", music_ptr->singer);
                }
                ListManager.drop_memory(&list, MUSIC);
            }
            cJSON_Delete(cjson_parser);
        }
    }
    ByteBuffer.drop_memery(&buffer);
    NluRequest.close(&session);
    BodyManager.base.drop.drop_memery(&content);
}

void test_nlu_handler_ptr()
{

    const User user = UserManager.new("", "");
    const Device device = DeviceManager.new("48d890d762b0", "48d890d762b0", "10f03");
    const Body content = BodyManager.new(user, device, "今天几号");
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
                printf("in status\n");
                const StatusCPtr status_ptr = StatusManager.from_cjson_to_cptr(status_cjson);
                if (status_ptr != RT_NULL)
                {
                    printf("code:%d\n", status_ptr->code);
                    printf("err type:%s\n", status_ptr->error_type);
                }
                else
                {
                    printf("status is null\n");
                }
                StatusManager.drop_memory_and_self(status_ptr);
            }
            const cJSON *semantic_cjson = cJSON_GetObjectItem(cjson_parser, SEMANTIC);
            if (!cJSON_IsNull(semantic_cjson))
            {
                const SemanticCPtr semantic_ptr = SemanticManager.from_cjson_to_cptr(semantic_cjson);
                printf("semantic.domain:%s\n", semantic_ptr->domain);
                printf("semantic.intent:%s\n", semantic_ptr->intent);
                printf("semantic.session_complete:%d\n", semantic_ptr->session_complete);
                printf("semantic.skill:%s\n", semantic_ptr->skill);
                SemanticManager.drop_memory_and_self(semantic_ptr);
            }
            const cJSON *payload_cjson = cJSON_GetObjectItem(cjson_parser, PAYLOAD);
            if (!cJSON_IsNull(payload_cjson))
            {
                const PayloadCPtr payload_ptr = PayloadManager.from_cjson_to_cptr(payload_cjson);
                if (payload_ptr != RT_NULL)
                {
                    printf("payload.service:%s\n", payload_ptr->service);
                    printf("payload.action:%s\n", payload_ptr->action);
                    if (payload_ptr->params != RT_NULL)
                    {
                        printf("payload.params->degree->norm:%s\n", payload_ptr->params->degree->norm);
                        printf("payload.params->degree->orgin:%s\n", payload_ptr->params->degree->orgin);
                        printf("payload.params->degree->code:%d\n", payload_ptr->params->degree->code);
                    }
                    else
                    {
                        printf("payload.params is null\n");
                    }
                }
                PayloadManager.drop_memory_and_self(payload_ptr);
            }
            const cJSON *response_cjson = cJSON_GetObjectItem(cjson_parser, RESPONSE);
            if (!cJSON_IsNull(response_cjson))
            {
                const ResponseCPtr response_ptr = ResponseManager.from_cjson_to_cptr(response_cjson);
                if (response_ptr != RT_NULL)
                {
                    printf("response.text:%s\n", response_ptr->text);
                    printf("response.hint:%s\n", response_ptr->hint);
                }
                ResponseManager.drop_memory_and_self(response_ptr);
            }

            const cJSON *list_cjosn = cJSON_GetObjectItem(cjson_parser, LIST);
            if (!cJSON_IsNull(list_cjosn))
            {
                const ListCPtr list_ptr = ListManager.from_cjson_to_cptr(list_cjosn, MUSIC);
                if (list_ptr != RT_NULL)
                {
                    while (ListManager.has_next(list_ptr))
                    {
                        MusicPtr music_ptr = (MusicPtr)ListManager.next(list_ptr);
                        printf("music song:%s\n", music_ptr->song);
                        printf("music url:%s\n", music_ptr->url);
                        printf("music id:%s\n", music_ptr->song_id);
                        printf("music singer:%s\n", music_ptr->singer);
                    }
                }
                ListManager.drop_memory_and_self(list_ptr, MUSIC);
            }
            cJSON_Delete(cjson_parser);
        }
    }
    ByteBuffer.drop_memery(&buffer);
    NluRequest.close(&session);
    BodyManager.base.drop.drop_memery(&content);
}

MSH_CMD_EXPORT(test_nlu_handler, test nlu handler);
MSH_CMD_EXPORT(test_nlu_handler_ptr, test nlu handler);