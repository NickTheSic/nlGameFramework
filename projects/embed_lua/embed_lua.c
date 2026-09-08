#include "nl_lib.h"

#include "lua/src/lua.h"
#include "lua/src/lualib.h"
#include "lua/src/lauxlib.h"


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

static int test_lua_call(lua_State* L)
{
    int argc = lua_gettop(L);
    if (argc == 0)
    {
        NL_LOG("No Arguments Provided");
    }
    else if (argc == 1)
    {
        NL_LOG("One Argument Provided!");
    }
}

void app_specific_init(void)
{
}

void app_specific_update(double dt)
{
    NL_UNUSED(dt);

    if (key_was_pressed(key_r))
    {
        lua_State* L = luaL_newstate(); // lua_newstate(lua Allocator) -> if I need so in the future
        luaL_openlibs(L);

        lua_pushcfunction(L, test_lua_call);
        lua_setglobal(L, "myccall");
        
        // Load file, should name it main.lua or something in the future for consistency
        file_contents lua_script = {0};
        read_entire_file("data/scripts/simple_test.lua", &lua_script, get_temporary_bump_allocator());
        
        luaL_dostring(L, lua_script.content);
        lua_close(L);

        clear_file_read(&lua_script);
        flush_bump_allocator(get_temporary_bump_allocator());
    }
}

void app_specific_render(void)
{

}

void app_specific_cleanup(void)
{

}


#undef KB
#include "build_lua.c"
