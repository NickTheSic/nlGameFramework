#include "whalepass_gg.h"
#include "nl_lib.h"

#include <stdio.h>
#include <string.h>
#include <emscripten/fetch.h>

global_variable char* wgg_active_request_data = 0;

internal_function void wgg_cleanup_request(emscripten_fetch_t *fetch)
{
    memory_free(wgg_active_request_data);
    wgg_active_request_data = 0;
    emscripten_fetch_close(fetch);
}

internal_function void wgg_request_success(emscripten_fetch_t *fetch) 
{
    NL_LOG("Finished downloading %llu bytes from URL %s.\n", fetch->numBytes, fetch->url);
    NL_LOG("Result Data: %s", fetch->data);

    // Whoops! This was supposed to be common but now it is specific
    ll_handle_successful_login(fetch->data);

    wgg_cleanup_request(fetch);
}

internal_function void wgg_request_failed(emscripten_fetch_t *fetch) 
{
    NL_LOG("Downloading %s failed, HTTP failure status code: %d.\n", fetch->url, fetch->status);
    NL_LOG("Result Data: %s", fetch->data);
    wgg_cleanup_request(fetch);
}

void wgg_authenticate(const char* publish_key, const char* game_id, const char* player_id)
{
    if (wgg_active_request_data != 0)
    {
        NL_LOG("active_request_data is not null with the value %s", wgg_active_request_data);
        NL_LOG("Not completing request at this time to not allocate more memory than I freed");
        return;
    }

    emscripten_fetch_attr_t attr;
    emscripten_fetch_attr_init(&attr);
    strcpy(attr.requestMethod, "POST");

    attr.attributes = EMSCRIPTEN_FETCH_LOAD_TO_MEMORY;
    attr.onsuccess = wgg_request_success;
    attr.onerror = wgg_request_failed;

    const char * headers[] = {"Content-Type", "application/json", "X-API-KEY", publish_key, 0};
    attr.requestHeaders = headers;

    const char* pre_game_id = "{\"gameId\":\"";
    const char* post_game_pre_player = "\",\"playerId\":\"";
    const char* post_player_id = "\"}\0";

    const size_t pre_game_id_len = strlen(pre_game_id);
    const size_t game_id_len = strlen(game_id);
    const size_t post_game_pre_player_len = strlen(post_game_pre_player);
    const size_t player_id_len = strlen(player_id);
    const size_t post_player_id_len = strlen(post_player_id);
    const size_t total_length = pre_game_id_len + game_id_len + post_game_pre_player_len + player_id_len + post_player_id_len;

    wgg_active_request_data = (char*)memory_allocate(total_length);
    memcpy((void*)wgg_active_request_data, 
            pre_game_id, 
            pre_game_id_len);

    memcpy((void*)wgg_active_request_data + pre_game_id_len, 
            game_id, 
            game_id_len);

    memcpy((void*)wgg_active_request_data + pre_game_id_len + game_id_len, 
            post_game_pre_player, 
            post_game_pre_player_len);

    memcpy((void*)wgg_active_request_data + pre_game_id_len + game_id_len + post_game_pre_player_len, 
            player_id, 
            player_id_len);

    memcpy((void*)wgg_active_request_data + pre_game_id_len + game_id_len + post_game_pre_player_len + player_id_len, 
            post_player_id, 
            post_player_id_len);

    attr.requestData = wgg_active_request_data;
    attr.requestDataSize = strlen(attr.requestData);

    emscripten_fetch(&attr, "https://api.whalepass.gg/enrollments");
}
