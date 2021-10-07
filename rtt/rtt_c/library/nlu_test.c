#include "nlu.h"
#include <finsh.h>
#include <rtthread.h>
void test_request_data()
{
    const User user = UserManager.new("", "");
    const Device device = DeviceManager.new("48d890d762b0", "48d890d762b0", "10f03");
    const Content content = ContentManager.new(user, device, "上一首");
    char *req_body = create_request_body(content);
    ContentManager.super.drop.drop_memery(&content);
    printf("req_body:%s\n", req_body);
    const char *const auth = create_request_auth_header(req_body, strlen(req_body));
    printf("auth:%s\n", auth);
    rt_free(req_body);
    rt_free(auth);
}
MSH_CMD_EXPORT(test_request_data,test requrest data);
