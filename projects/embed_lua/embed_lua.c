#include "nl_lib.h"
#include "build_lua.c"

/*
LUA TYPES:
    nil
    boolean
    light userdata (* A C pointer)
    number (a 64 bit number)
    string (garbage collected)
    table (complex type) { "foo", "bar" }
    function (like lambdas)
    userdata (your own type)
    thread
*/

global_variable lua_State* L = 0;

void app_specific_init(void)
{
    L = luaL_newstate(); // lua_newstate(lua Allocator) -> if I need so in the future
    luaL_openlibs(L);
    luaL_dostring(L, "print('Hello from Lua!')");
}

void app_specific_update(double dt)
{
    NL_UNUSED(dt);
}

void app_specific_render(void)
{

}

void app_specific_cleanup(void)
{
    lua_close(L);
}