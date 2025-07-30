/* SPDX-License-Identifier: BSD-3-Clause
 * Copyright(c) 2021.
 */

/**
 * @file
 *
 * String-related utility functions for IP addresses
 */

#ifndef __ATOIP_H_
#define __ATOIP_H_

#include <netinet/in.h>

#ifdef __cplusplus
extern "C" {
#endif

#define _IPADDR_V4      0x01
#define _IPADDR_V6      0x02
#define _IPADDR_NETWORK 0x04

#define _INADDRSZ       4
#define _IN6ADDRSZ      16
#define _PREFIXMAX      128
#define _V4PREFIXMAX    32

struct _ipaddr {
	uint8_t family;
	union {
		uint32_t ipv4;
		uint8_t ipv6[_IN6ADDRSZ];
	};
	unsigned int prefixlen;
};

/**
 * Convert an IPv4/v6 address into a binary value.
 *
 * @param buf
 *   Location of string to convert
 * @param flags
 *   Set of flags for converting IPv4/v6 addresses and netmask.
 * @param res
 *   Location to put the results
 * @param ressize
 *   Length of res in bytes.
 * @return
 *   4 or 6 on OK, indicating an IPv4/v6 address, respectively, and -1 on error
 */
int _atoip(const char *buf, int flags, void *res, unsigned ressize);

#ifdef __cplusplus
}
#endif

#endif /* __ATOIP_H_ */
