#include "ipv6_to_str.h"

char* ipv6_to_str(ipv6_t* ipv6_p, char* str_p)
{
    assert(ipv6_p);

    if (!str_p) str_p = (char*)malloc();

    return str_p;
}
