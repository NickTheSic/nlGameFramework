#include "loot_locker.h"
#include "nl_lib.h"

#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>

global_variable char* ll_win_active_request_data = 0;

void ll_guest_login(const char* const game_key)
{
WSADATA wsa_data = {0};

    int i_result = 0;

    // Initialize Winsock
    i_result = WSAStartup(MAKEWORD(2,2), &wsa_data);
    if (i_result != 0) 
    {
        NL_LOG("WSAStartup failed: %d", i_result);
        return;
    }

    struct addrinfo *result = 0, *ptr = 0, hints;

    ZeroMemory( &hints, sizeof(hints) );
    hints.ai_family   = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    i_result = getaddrinfo("https://api.lootlocker.io/game/v2/session/guest", "443", &hints, &result);
    if (i_result != 0) 
    {
        NL_LOG("getaddrinfo failed: %d", i_result);
        WSACleanup();
        return;
    }

    SOCKET sock = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

    if (sock == INVALID_SOCKET)
    {
        NL_LOG("Socket is invalid");
        return;
    }
    
    NL_UNUSED(game_key);
}

void ll_returning_user(const char* const game_key, const char* const player_id)
{
    WSADATA wsa_data = {0};

    int i_result = 0;

    // Initialize Winsock
    i_result = WSAStartup(MAKEWORD(2,2), &wsa_data);
    if (i_result != 0) 
    {
        NL_LOG("WSAStartup failed: %d", i_result);
        return;
    }

    struct addrinfo *result = 0, *ptr = 0, hints;

    ZeroMemory( &hints, sizeof(hints) );
    hints.ai_family   = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    i_result = getaddrinfo("https://api.lootlocker.io/game/v2/session/guest", "443", &hints, &result);
    if (i_result != 0) 
    {
        NL_LOG("getaddrinfo failed: %d", i_result);
        WSACleanup();
        return;
    }

    SOCKET sock = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

    if (sock == INVALID_SOCKET)
    {
        NL_LOG("Socket is invalid");
        return;
    }

    
    NL_UNUSED(game_key); NL_UNUSED(player_id);
}
