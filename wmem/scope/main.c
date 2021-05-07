#include <glib.h>
#include "epan/epan.h"
#include "epan/wmem/wmem.h"

int main(int argc, char **argv)
{
    wmem_allocator_t *epan_pool;
    wmem_allocator_t *file_pool;
    wmem_allocator_t *packet_pool;
    char *epan_buf, *file_buf, *packet_buf;
    int i;

    // error code below, will cause assertion failed,
    // must call wmem_init() first
    // epan_pool = wmem_epan_scope();

    wmem_init();

    epan_pool = wmem_epan_scope();
    if (NULL == epan_pool) {
        g_print("epan_pool is NOT inited\n");
        return -1;
    }
    file_pool = wmem_file_scope();
    packet_pool = wmem_packet_scope();

    epan_buf = wmem_alloc(epan_pool, 64);
    if (NULL == epan_buf) {
        g_print("alloc in epan pool failed\n");
        goto end;
    }
    g_snprintf(epan_buf, 64, "epan string");
    g_print("epan_buf: %s\n", epan_buf);

    wmem_enter_file_scope();

    file_buf = wmem_alloc(file_pool, 64);
    if (NULL == file_buf) {
        g_print("alloc in file pool failed\n");
        goto end;
    }
    g_snprintf(file_buf, 64, "file string");
    g_print("file_buf: %s\n", file_buf);

    for (i = 0; i < 5; i++) {
        wmem_enter_packet_scope();
        packet_buf = wmem_alloc(packet_pool, 32);
        g_snprintf(packet_buf, 16, "packet string %d", i + 1);
        g_print("packet_buf: %s\n", packet_buf);
        wmem_leave_packet_scope();
        g_print("packet_buf: %s\n", packet_buf);
    }

    wmem_leave_file_scope();

    // error code below, will cause segment fault,
    // because we have leave file scope
    // g_print("file_buf: %s\n", file_buf);

    g_print("epan_buf: %s\n", epan_buf);
    // no wmem_leave_epan_scope() API,
    // it will auto-destroyed when wmem_cleanup() is called

end:
    wmem_cleanup();

    return 0;
}