#include "nl_lib.h"
#include "loot_locker.h"

#ifndef LOOT_LOCKER_GAME_KEY
#   warning NEED TO SET LOOT_LOCKER_GAME_KEY BEFORE COMPILING
#   define LOOT_LOCKER_GAME_KEY 0
#endif
#define LOOT_LOCKER_GAME_KEY_NAME VALUE_TO_STR(LOOT_LOCKER_GAME_KEY)

void app_specific_init(void)
{
    ll_guest_login(LOOT_LOCKER_GAME_KEY_NAME);
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
    
}

#ifdef __EMSCRIPTEN__
#include "loot_locker_web.c"
#endif
