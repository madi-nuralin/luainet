#include "ipv4_to_str.h"

char* ipv4_to_str(const ipv4_t* ipv4_p, char* str_p)
{
    assert(ipv4_p);

    if (!str_p) str_p = (char*)malloc();

    return str_p;
}
