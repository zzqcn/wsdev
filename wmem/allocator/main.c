#include <glib.h>
#include "epan/epan.h"
#include "epan/wmem/wmem.h"

int main(int argc, char** argv)
{
    wmem_allocator_t* pool;
    char* buf;

    wmem_init();

    pool = wmem_allocator_new(WMEM_ALLOCATOR_SIMPLE);
    if (NULL == pool) {
        g_print("create simple pool failed\n");
        return -1;
    }
    buf = wmem_alloc(pool, 64);
    g_print("buf: %p\n", buf);
    wmem_destroy_allocator(pool);

    // error code below, will cause segment fault
    // buf = wmem_alloc(pool, 64);
    // g_print("buf: %p\n", buf);

    pool = wmem_allocator_new(WMEM_ALLOCATOR_BLOCK);
    if (NULL == pool) {
        g_print("create block pool failed\n");
        return -1;
    }
    buf = wmem_alloc(pool, 64);
    g_print("buf: %p\n", buf);
    wmem_destroy_allocator(pool);

    wmem_cleanup();

    return 0;
}