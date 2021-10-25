
#include "nlu_handler.h"
#include <finsh.h>
#include <rtthread.h>

void test_nlu_handler()
{

    const User user = UserManager.new("", "");
    const Device device = DeviceManager.new("48d890d762b0", "48d890d762b0", "10f03");
    const Content content = ContentManager.new(user, device, "播放红莲华");
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
            if (status_cjson != RT_NULL)
            {
                const Status status = StatusManager.from_cjson(status_cjson);
                printf("code:%d\n", status.code);
                printf("err type:%s\n", status.error_type);
                StatusManager.drop_memory(&status);
            }
            const cJSON *semantic_cjson = cJSON_GetObjectItem(cjson_parser, SEMANTIC);
            if (semantic_cjson != RT_NULL)
            {
                const Semantic semantic = SemanticManager.from_cjson(semantic_cjson);
                printf("semantic.domain:%s\n", semantic.domain);
                printf("semantic.intent:%s\n", semantic.intent);
                printf("semantic.session_complete:%d\n", semantic.session_complete);
                printf("semantic.skill:%s\n", semantic.skill);
                SemanticManager.drop_memory(&semantic);
            }
            cJSON_Delete(cjson_parser);
        }
    }
    ByteBuffer.drop_memery(&buffer);
    NluRequest.close(&session);
    ContentManager.base.drop.drop_memery(&content);
}

MSH_CMD_EXPORT(test_nlu_handler, test nlu handler);