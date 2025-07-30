#include "str_to_ipv4.h"

ipv4_t* str_to_ipv4(const char* str_p, ipv4_t* ipv4_p)
{
    assert(str_p);

    if (!ipv4_p) ipv4_p = (ipv4_t*)malloc(sizeof(ipv4_t));

    return ipv4_p;
}
