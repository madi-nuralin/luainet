/* SPDX-License-Identifier: BSD-3-Clause
 * Copyright(c) 2021.
 */

#ifndef __TO_H_
#define __TO_H_

#include <arpa/inet.h>
#include <stdio.h>
#include <stdint.h>

#include "_atoip.h"

/* Ethernet address structure */
struct _ether_addr {
	uint8_t addr_bytes[6];
};

#ifndef _MASK_SIZE_
#define _MASK_SIZE_
/* mask_size(uint32_t mask) - return the number of bits in mask */
static __inline__ int
mask_size(uint32_t mask) {
	if (mask == 0)
		return 0;
	else if (mask == 0xFF000000)
		return 8;
	else if (mask == 0xFFFF0000)
		return 16;
	else if (mask == 0xFFFFFF00)
		return 24;
	else if (mask == 0xFFFFFFFF)
		return 32;
	else {
		int i;
		for (i = 0; i < 32; i++)
			if ( (mask & (1 << (31 - i))) == 0)
				break;
		return i;
	}
}
#endif

/* size_to_mask( int len ) - return the mask for the mask size */
static __inline__ uint32_t
size_to_mask(int len) {
	uint32_t mask = 0;

	if (len == 0)
		mask = 0x00000000;
	else if (len == 8)
		mask = 0xFF000000;
	else if (len == 16)
		mask = 0xFFFF0000;
	else if (len == 24)
		mask = 0xFFFFFF00;
	else if (len == 32)
		mask = 0xFFFFFFFF;
	else {
		int i;

		for (i = 0; i < len; i++)
			mask |= (1 << (31 - i));
	}
	return mask;
}

#ifndef _NTOP4_
#define _NTOP4_
/* char * inet_ntop4(char * buff, int len, unsigned long ip_addr, unsigned long mask) - Convert IPv4 address to ascii */
static __inline__ char *
inet_ntop4(char *buff, int len, unsigned long ip_addr, unsigned long mask) {
	char lbuf[64];

	inet_ntop(AF_INET, &ip_addr, buff, len);
	if (mask != 0xFFFFFFFF) {
		snprintf(lbuf, sizeof(lbuf), "%s/%d", buff, mask_size(mask));
		snprintf(buff, len, "%s", lbuf);
	}
	return buff;
}
#endif

/* const char * inet_ntop6(char * buff, int len, uint8_t *ip6, unsigned prefixlen) - Convert IPv6 address to ascii */
static __inline__ const char *
inet_ntop6(char *buff, int len, uint8_t *ip6, unsigned prefixlen) {
	char lbuf[64];

	inet_ntop(AF_INET6, ip6, buff, len);

	if (prefixlen != _PREFIXMAX) {
		snprintf(lbuf, sizeof(lbuf), "%s/%d", buff, prefixlen);
		snprintf(buff, len, "%s", lbuf);
	}

	return buff;
}

#ifndef _MTOA_
#define _MTOA_
/* char * inet_mtoa(char * buff, int len, struct pg_ether_addr * eaddr) - Convert MAC address to ascii */
static __inline__ char *
inet_mtoa(char *buff, int len, struct _ether_addr *eaddr) {
	snprintf(buff, len, "%02x:%02x:%02x:%02x:%02x:%02x",
		 eaddr->addr_bytes[0], eaddr->addr_bytes[1],
		 eaddr->addr_bytes[2], eaddr->addr_bytes[3],
		 eaddr->addr_bytes[4], eaddr->addr_bytes[5]);
	return buff;
}
#endif

/* convert a MAC address from network byte order to host 64bit number */
static __inline__ uint64_t
inet_mtoh64(struct _ether_addr *eaddr, uint64_t *value) {
	*value = ((uint64_t)eaddr->addr_bytes[5] << 0)
		+ ((uint64_t)eaddr->addr_bytes[4] << 8)
		+ ((uint64_t)eaddr->addr_bytes[3] << 16)
		+ ((uint64_t)eaddr->addr_bytes[2] << 24)
		+ ((uint64_t)eaddr->addr_bytes[1] << 32)
		+ ((uint64_t)eaddr->addr_bytes[0] << 40);
	return *value;
}

/* convert a host 64bit number to MAC address in network byte order */
static __inline__ struct _ether_addr *
inet_h64tom(uint64_t value, struct _ether_addr *eaddr) {
	eaddr->addr_bytes[5] = ((value >> 0) & 0xFF);
	eaddr->addr_bytes[4] = ((value >> 8) & 0xFF);
	eaddr->addr_bytes[3] = ((value >> 16) & 0xFF);
	eaddr->addr_bytes[2] = ((value >> 24) & 0xFF);
	eaddr->addr_bytes[1] = ((value >> 32) & 0xFF);
	eaddr->addr_bytes[0] = ((value >> 40) & 0xFF);
	return eaddr;
}

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
 *   0 on OK and -1 on error
 */
int _atoip(const char *buf, int flags, void *res, unsigned ressize);


#endif /*__TO_H_*/
