#include <glib.h>
#include "epan/epan.h"

int main(int argc, char** argv)
{
    g_print("hello wireshark %s\n", epan_get_version());
    return 0;
}