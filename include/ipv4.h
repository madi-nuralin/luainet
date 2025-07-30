#pragma once

struct ipv4_t;

char* ipv4_to_str(const ipv4_t* ipv4_p, char* str_p);
ipv6_t* str_to_ipv4(const char* str_p, ipv6_t* ipv6_p);
