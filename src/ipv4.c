#include "ipv4.h"

#include <stdint.h>

typedef struct ipv4_s
{
  uint32_t value;
} ipv4_t;

char* ipv4_to_str(const ipv4_t* ipv4_p, char* str_p)
{
    assert(ipv4_p);

    if (!str_p) str_p = (char*)malloc();

    return str_p;
}

ipv4_t* str_to_ipv4(const char* str_p, ipv4_t* ipv4_p)
{
    assert(str_p);

    if (!ipv4_p) ipv4_p = (ipv4_t*)malloc(sizeof(ipv4_t));

    return ipv4_p;
}
