#include "nl_lib.h"

#include "lua/src/lua.h"
#include "lua/src/lualib.h"
#include "lua/src/lauxlib.h"

#include "string.h"

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

global_variable lua_State* My_L = {0};
global_variable file_contents lua_script = {0};
global_variable char* lua_script_start = {0};
global_variable char* lua_script_current = {0};
global_variable nl_bump_allocator lua_bump_alloc = {0};

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

    // The amount of return variables!
    return 0;
}

static int lua_load_sound(lua_State* L)
{
    int argc = lua_gettop(L);
    if (argc != 1)
    {
        NL_LOG("lua load sound did not have exactly 1 input.  Not loading as sound expected");
        return 0;
    }

    unsigned int new_sound = load_sound_file(lua_tostring(My_L, -1));
    // push value to lua stack
    // keep track here as well

    return 1;
}

void app_specific_init(void)
{
    make_bump_allocator(&lua_bump_alloc, NL_SIZE_IN_MB(3));

    My_L = luaL_newstate(); // lua_newstate(lua Allocator) -> if I need so in the future
    luaL_openlibs(My_L);

    lua_pushcfunction(My_L, lua_load_sound);
    lua_setglobal(My_L, "load_sound");
    
    // Load file, should name it main.lua or something in the future for consistency
    read_entire_file("data/scripts/simple_test.lua", &lua_script, &lua_bump_alloc);

    lua_script_start = (char*)lua_script.content;
    lua_script_current = lua_script_start;
}

void app_specific_update(double dt)
{
    NL_UNUSED(dt);

    // This is garanteed to buffer overflow.  Really bad
    if (key_was_pressed(key_space))
    {
        // Would be good to add some proper file reading error handling!
        if (lua_script_current >= (lua_script.content + lua_script.size))
        {
            NL_LOG("Reached end of file!");
            return;
        }

        char line_to_execute[64] = {0};

        int copies = 0;
        char last_char = 'a';
        while (copies < 63 && last_char != '\n' && last_char != '\0')
        {
            last_char = lua_script_current[copies];
            line_to_execute[copies] = last_char;
            ++copies;

            if ((lua_script_current + copies) >= (lua_script.content + lua_script.size))
            {
                NL_LOG("Reached end of file!");
                break;
            }
        }

        if (luaL_dostring(My_L, line_to_execute) != LUA_OK)
        {
            NL_LOG("Lua Error: %s", lua_tostring(My_L, -1));
        }

        lua_script_current = (lua_script_current + copies);
    }

}

void app_specific_render(void) {}

void app_specific_cleanup(void)
{
    lua_close(My_L);
    My_L = 0;

    free_bump_allocator(&lua_bump_alloc);
}


#undef KB
#include "build_lua.c"
