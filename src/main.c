/* SPDX-License-Identifier: BSD-3-Clause
 * Copyright(c) 2021.
 */

#include <string.h>

#include "_to.h"
#include "_atoip.h"
#include "luanet.h"

/**
 * An htonl wrapper for Lua
 *
 * Lua prototype: integer htonl(h)
 * @param h
 *   Host byte order
 * @return
 *   Network byte order
 */

static int
_htonl(lua_State *L)
{
	switch (lua_gettop(L)) {
	default: return luaL_error(L, "htonl, wrong number of arguments");
	case 1:
		break;
	}

	lua_pushinteger(L, htonl(luaL_checkinteger(L, 1)));

	return 1;
}

/**
 * An inet_ntop wrapper for Lua
 *
 * Lua prototype: string ntop(ip, prefix)
 * @param iP
 *   An IPv4/v6 addresses
 * @param prefix (can be omitted)
 *   A prefixlen of netmask. 
 * @return
 *   Presentation format
 */

static int
_ntop(lua_State *L)
{
	struct _ipaddr ipaddr = {
		.family=0,
		.prefixlen=_PREFIXMAX+1
	};
	char buff[INET6_ADDRSTRLEN+4];

	switch (lua_gettop(L)) {
	default: return luaL_error(L, "ntop, wrong number of arguments");
	case 2:
		ipaddr.prefixlen = luaL_checkinteger(L, 2);
		break;
	case 1:
		break;
	}

	/* Since IPv4 address is presented as an 32 bit integer 
	 * and v6 address as a table data type,
         * so differentiate them by data type
	 */
	if (lua_isnumber(L, 1)) {
		ipaddr.ipv4 = luaL_checkinteger(L, 1);
		inet_ntop4(buff, sizeof(buff), ipaddr.ipv4,
			ipaddr.prefixlen > _V4PREFIXMAX ?
				0xFFFFFFFF : size_to_mask(ipaddr.prefixlen));
	} else if (lua_istable(L, 1)) {
		if (lua_rawlen(L, 1) != _IN6ADDRSZ)
			return luaL_error(L, "ntop, wrong table size");

		for (int i = 0; i < _IN6ADDRSZ; ++i) {
			lua_rawgeti(L, 1, i+1);
			ipaddr.ipv6[i] = lua_tointeger(L, -1);
			lua_pop(L, 1);
		}

		inet_ntop6(buff, sizeof(buff), ipaddr.ipv6,
			ipaddr.prefixlen > _PREFIXMAX ?
				_PREFIXMAX : ipaddr.prefixlen);
	} else
		return luaL_error(L, "ntop, wrong argument");

	lua_pushstring(L, buff);
	return 1;
}

/**
 * An inet_pton wrapper for Lua
 *
 * Lua prototype: string pton(ip_str)
 * @param ip_str
 *   An IPv4/v6 string
 * @return
 *   Numeric format
 */

static int
_pton(lua_State *L)
{
	int ip_ver;
	struct _ipaddr ipaddr;
	char buff[INET6_ADDRSTRLEN+4];

	switch (lua_gettop(L)) {
	default: return luaL_error(L, "pton, wrong number of arguments");
	case 1:
		break;
	}

	strcpy(buff, luaL_checkstring(L, 1));
	ip_ver = _atoip(buff, 0, &ipaddr, sizeof(ipaddr));

	if (ip_ver == 4) {
		inet_pton(AF_INET, buff, &ipaddr.ipv4);
		lua_pushinteger(L, 1);
	} else if (ip_ver == 6) {
		inet_pton(AF_INET6, buff, ipaddr.ipv6);
		lua_createtable(L, _IN6ADDRSZ, 0);
		for (int i = 0; i < _IN6ADDRSZ; i++) {
			lua_pushinteger(L, ipaddr.ipv6[i]);
			lua_rawseti(L, -2, i+1);
		}
	} else
		lua_pushnil(L);

	return 1;
}

/**
 * A mtoa wrapper for Lua
 *
 * Lua prototype: string mtoa(mac_addr)
 * @param mac_addr
 *   Mac address bytes
 * @return
 *   Presentation format
 */

static int
_mtoa(lua_State *L)
{
	char buff[INET6_ADDRSTRLEN+4];
	struct _ether_addr ether_addr;

	switch (lua_gettop(L)) {
	default: return luaL_error(L, "mtoa, wrong number of arguments");
	case 1:
		break;
	}

	/* MAC address should presented by 6 byte table */
	if (!lua_istable(L, 1))
		return  luaL_error(L, "mtoa, wrong argument");

	if (lua_rawlen(L, 1) != 6)
		return luaL_error(L, "mtoa, wrong table size");

	for (int i = 0; i < 6; ++i) {
		lua_rawgeti(L, 1, i+1);
		ether_addr.addr_bytes[i] = lua_tointeger(L, -1);
		lua_pop(L, 1);
	}

	inet_mtoa(buff, sizeof(buff), &ether_addr);
	lua_pushstring(L, buff);

	return 1;
}
/**
static const luaL_Reg inetlib[] = {
	{"", },
	{NULL, NULL}
};
*/
LUALIB_API int
luaopen_linetlib(lua_State *L)
{
	lua_newtable(L);
	lua_pushcfunction(L, _htonl);
	lua_setfield(L, -2, "htonl");
	lua_pushcfunction(L, _ntop);
	lua_setfield(L, -2, "ntop");
	lua_pushcfunction(L, _pton);
	lua_setfield(L, -2, "pton");
	lua_pushcfunction(L, _mtoa);
	lua_setfield(L, -2, "mtoa");
	return 1;
}
