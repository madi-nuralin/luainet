#pragma once

struct ipv6_t;

char* ipv6_to_str(const ipv6_t* ipv6_p, char* str_p);
ipv6_t* str_to_ipv6(const char* str_p, ipv6_t* ipv6_p);
