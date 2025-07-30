#include "ipv6.h"

#include <stdint.h>

typedef struct ipv6_s
{
  uint8_t value[16];
} ipv6_t;

char* ipv6_to_str(ipv6_t* ipv6_p, char* str_p)
{
    assert(ipv6_p);

    if (!str_p) str_p = (char*)malloc();

    return str_p;
}

ipv6_t* str_to_ipv6(const char* str_p, ipv6_t* ipv6_p)
{
    assert(str_p);

    if (!ipv6_p) ipv6_p = (ipv6_t*)malloc(sizeof(ipv6_t));

    return ipv6_p;
}
