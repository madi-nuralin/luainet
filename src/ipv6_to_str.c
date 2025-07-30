#include "ipv6_to_str.h"

ipv6_t* str_to_ipv6(const char* str_p, ipv6_t* ipv6_p)
{
    assert(str_p);

    if (!ipv6_p) ipv6_p = (ipv6_t*)malloc(sizeof(ipv6_t));

    return ipv6_p;
}
