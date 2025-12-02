#include <stdio.h>
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

/* 打印 Lua 栈的结构 */
void print_stack(lua_State *L) {
    int top = lua_gettop(L);
    printf("=== Lua Stack (depth: %d) ===\n", top);
    
    for (int i = 1; i <= top; i++) {
        int type = lua_type(L, i);
        const char *type_name = lua_typename(L, type);
        
        printf("[%d] %s: ", i, type_name);
        
        switch (type) {
            case LUA_TNUMBER:
                printf("%g\n", lua_tonumber(L, i));
                break;
            case LUA_TSTRING:
                printf("\"%s\"\n", lua_tostring(L, i));
                break;
            case LUA_TBOOLEAN:
                printf("%s\n", lua_toboolean(L, i) ? "true" : "false");
                break;
            case LUA_TTABLE:
                printf("<table>\n");
                break;
            case LUA_TFUNCTION:
                printf("<function>\n");
                break;
            case LUA_TUSERDATA:
                printf("<userdata>\n");
                break;
            case LUA_TNIL:
                printf("nil\n");
                break;
            default:
                printf("<other>\n");
                break;
        }
    }
    printf("=======================\n\n");
}

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
    print_stack(L);
    
    if (lua_isfunction(L, -1)) {
        lua_pushnumber(L, 10);
        lua_pushnumber(L, 20);
        print_stack(L);
        
        if (lua_pcall(L, 2, 1, 0) != LUA_OK) {
            fprintf(stderr, "Call failed: %s\n", lua_tostring(L, -1));
             print_stack(L);
            lua_pop(L, 1);
        } else {
            print_stack(L);
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
