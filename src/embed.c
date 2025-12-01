#include <stdio.h>
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

int main(void) {
    lua_State *L = luaL_newstate();
    if (!L) {
        fprintf(stderr, "Failed to create Lua state\n");
        return 1;
    }
    luaL_openlibs(L);

    /* 在 Lua 中定义一个函数并打印 */
    if (luaL_dostring(L, "function add(a,b) return a+b end\nprint('Lua: add(2,3)=', add(2,3))")) {
        fprintf(stderr, "Lua error: %s\n", lua_tostring(L, -1));
        lua_pop(L, 1);
    }

    /* 从 C 调用 Lua 的 add 函数 */
    lua_getglobal(L, "add");
    if (lua_isfunction(L, -1)) {
        lua_pushnumber(L, 10);
        lua_pushnumber(L, 20);
        if (lua_pcall(L, 2, 1, 0) != LUA_OK) {
            fprintf(stderr, "Call failed: %s\n", lua_tostring(L, -1));
            lua_pop(L, 1);
        } else {
            double res = lua_tonumber(L, -1);
            printf("C: add(10,20) = %g\n", res);
            lua_pop(L, 1);
        }
    } else {
        fprintf(stderr, "'add' is not a function\n");
        lua_pop(L, 1);
    }

    lua_close(L);
    return 0;
}
