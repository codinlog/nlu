#include "nlu.h"
#include <finsh.h>
#include <rtthread.h>
void test_request_data()
{
    const User user = UserManager.new("", "");
    const Device device = DeviceManager.new("48d890d762b0", "48d890d762b0", "10f03");
    const Content content = ContentManager.new(user, device, "播放流行音乐");
    const char *req_body = create_request_body(content);
    ContentManager.base.drop.drop_memery(&content);
    printf("req_body:%s\n", req_body);
    create_request(ADDRESS, req_body);
    rt_free(req_body);
}

void test_request_data_100()
{
    for (int i = 0; i < 100; i++)
    {
        test_request_data();
        rt_thread_sleep(100);
    }
}
MSH_CMD_EXPORT(test_request_data, test requrest data);
MSH_CMD_EXPORT(test_request_data_100, test requrest data);
