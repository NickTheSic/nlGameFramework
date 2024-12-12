#include "nl_lib.h"
#include "loot_locker.h"
#include "whalepass_gg.h"
#include "api_key_defines.h"

void app_specific_init(void)
{
    NL_LOG("Pre Call of Fetch");

    //ll_guest_login(LOOT_LOCKER_GAME_KEY_NAME);
    ll_returning_user(LOOT_LOCKER_GAME_KEY_NAME, "4d137d65-c338-40f4-81df-7a30729ac42c");
    //wgg_authenticate(WHALEPASS_SERVER_KEY_NAME, WHALEPASS_GAME_ID_NAME, "abcd-1234-ef56");
    
    NL_LOG("Post Call of Fetch");
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
#include "platform/loot_locker_web.c"
#include "platform/whalepass_gg_web.c"
#elif _WIN32
#include "platform/loot_locker_win.c"
#include "platform/whalepass_gg_win.c"
#endif
