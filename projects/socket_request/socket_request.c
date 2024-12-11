#include "nl_lib.h"
#include "loot_locker.h"
#include "whalepass_gg.h"
#include "api_key_defines.h"

void app_specific_init(void)
{
    ll_guest_login(LOOT_LOCKER_GAME_KEY_NAME);
    //wgg_authenticate(WHALEPASS_SERVER_KEY_NAME, WHALEPASS_GAME_ID_NAME, WHALEPASS_PLAYER_ID_NAME);
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
#include "whalepass_gg_web.c"
#elif _WIN32
#include "loot_locker_win.c"
#include "whalepass_gg_win.c"
#endif
