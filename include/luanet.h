/* SPDX-License-Identifier: BSD-3-Clause
 * Copyright(c) 2021.
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#define lua_c
#include <lua.h>
#include <lauxlib.h>

#define LIBLUA_INET_NAME   "inet"

LUALIB_API int luaopen_linetlib(lua_State *L);

#ifdef __cplusplus
}
#endif
