#include <lua.h>
#include <lauxlib.h>

static int l_hello(lua_State *L) {
    const char *name = luaL_optstring(L, 1, "world");
    lua_pushfstring(L, "Hello, %s from C!", name);
    return 1;
}

static const luaL_Reg mylib[] = {
    {"hello", l_hello},
    {NULL, NULL}
};

int luaopen_mylib(lua_State *L) {
#if LUA_VERSION_NUM >= 502
    luaL_newlib(L, mylib);
#else
    luaL_register(L, "mylib", mylib);
#endif
    return 1;
}
