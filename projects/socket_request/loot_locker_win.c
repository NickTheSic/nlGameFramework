#include "loot_locker.h"
#include "nl_lib.h"

#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>

global_variable char* ll_win_active_request_data = 0;

void ll_guest_login(const char* const game_key)
{
    NL_UNUSED(game_key);
}

