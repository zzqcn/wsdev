#include <glib.h>
#include "epan/tvbuff.h"
#include "epan/tvbuff-int.h"

static void chain(void)
{
    guint8* data;
    tvbuff_t *a, *b, *c, *tmp;

    data = g_malloc(32);

    a = tvb_new_real_data(data, 32, 32);
    b = tvb_new_real_data(data + 8, 32 - 8, 32 - 8);
    c = tvb_new_real_data(data + 16, 32 - 16, 32 - 16);
    g_print("data: %p, a: %p, b: %p, c: %p\n", data, a, b, c);

    tvb_add_to_chain(b, c);
    // b -> c
    for(tmp=b; tmp!=NULL; tmp=tmp->next) {
        g_print("%p -> ", tmp);
    }

    tvb_add_to_chain(a, b);
    // a -> c -> b
    g_print("null\n");
    for(tmp=a; tmp!=NULL; tmp=tmp->next) {
        g_print("%p -> ", tmp);
    }
    g_print("null\n");

    tvb_free_chain(a);
    g_free(data);
}

int main(int argc, char** argv)
{
    chain();

    return 0;
}