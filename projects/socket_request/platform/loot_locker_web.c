#include "loot_locker.h"
#include "nl_lib.h"

#include <stdio.h>
#include <string.h>
#include <emscripten/fetch.h>

/*

example login response
{
  "success": true,
  "session_token": "e6fa44946f077dd9fe67311ab3f188c596df9969",
  "player_id": 3,
  "public_uid": "TSEYDXD8",
  "player_identifier": "ec9b35e6-b184-4f34-b49f-980f86b291e2",
  "player_created_at": "2022-05-30T07:56:01+00:00",
  "check_grant_notifications": true,
  "check_deactivation_notifications": false,
  "seen_before": true
}

*/

typedef struct ll_login_response ll_login_response;
struct ll_login_response
{
    char* session_token;
    char* player_identifier;
};
global_variable ll_login_response ll_login = {0};

internal_function void ll_handle_successful_login(const char* const data)
{
    char *input = (char*)memory_allocate(strlen(data) + 1);
    memcpy(input, data, strlen(data));

    char* token = strtok(input, "\"");
    NL_LOG("Token: %s",token);

    do {
        token = strtok(0, "\"");
        NL_LOG("Token: %s",token);
        if (strcmp(token, "session_token") == 0)
        {
            token = strtok(0, "\""); // gets :
            token = strtok(0, "\""); // our session token
            ll_login.session_token = memory_allocate(strlen(token) + 1);
            memcpy(ll_login.session_token, token, strlen(token));
        }
        if (strcmp(token, "player_identifier") == 0)
        {
            token = strtok(0, "\""); // gets :
            token = strtok(0, "\""); // our player id
            ll_login.player_identifier = memory_allocate(strlen(token) + 1);
            memcpy(ll_login.player_identifier, token, strlen(token));
        }
    }while(token);

    NL_LOG("Session: %s", ll_login.session_token);
    NL_LOG("Player ID: %s", ll_login.player_identifier)

    memory_free(input);
}

global_variable char* ll_active_request_data = 0;

internal_function void ll_cleanup_request(emscripten_fetch_t *fetch)
{
    memory_free(ll_active_request_data);
    ll_active_request_data = 0;
    emscripten_fetch_close(fetch);
}

internal_function void ll_request_success(emscripten_fetch_t *fetch) 
{
    NL_LOG("Finished downloading %llu bytes from URL %s.\n", fetch->numBytes, fetch->url);
    NL_LOG("Result Data: %s", fetch->data);

    ll_handle_successful_login(fetch->data);

    ll_cleanup_request(fetch);
}

internal_function void ll_request_failed(emscripten_fetch_t *fetch) 
{
    NL_LOG("Downloading %s failed, HTTP failure status code: %d.\n", fetch->url, fetch->status);
    NL_LOG("Result Data: %s", fetch->data);
    ll_cleanup_request(fetch);
}

void ll_guest_login(const char* const game_key)
{
    if (ll_active_request_data != 0)
    {
        NL_LOG("active_request_data is not null with the value %s", ll_active_request_data);
        NL_LOG("Not completing request at this time to not allocate more memory than I freed");
        return;
    }

    emscripten_fetch_attr_t attr;
    emscripten_fetch_attr_init(&attr);
    strcpy(attr.requestMethod, "POST");

    attr.attributes = EMSCRIPTEN_FETCH_LOAD_TO_MEMORY;
    attr.onsuccess = ll_request_success;
    attr.onerror = ll_request_failed;

    const char * headers[] = {"Content-Type", "application/json", 0};
    attr.requestHeaders = headers;

    const char* pre_key = "{\"game_key\": \"";
    const char* post_key = "\", \"game_version\": \"0.10.0.0\"}\0";
    const size_t pre_key_len = strlen(pre_key);
    const size_t post_key_len = strlen(post_key);
    const size_t game_key_len = strlen(game_key);

    ll_active_request_data = (char*)memory_allocate( pre_key_len + post_key_len + game_key_len+1);

    memcpy((void*)ll_active_request_data, pre_key, pre_key_len);
    memcpy((void*)ll_active_request_data + pre_key_len, game_key, game_key_len);
    memcpy((void*)ll_active_request_data + pre_key_len + game_key_len, post_key, post_key_len);
    
    attr.requestData = ll_active_request_data;
    attr.requestDataSize = strlen(attr.requestData);

    emscripten_fetch(&attr, "https://api.lootlocker.io/game/v2/session/guest");
}

void ll_returning_user(const char* const game_key, const char* const player_id)
{
    if (ll_active_request_data != 0)
    {
        NL_LOG("active_request_data is not null with the value %s", ll_active_request_data);
        NL_LOG("Not completing request at this time to not allocate more memory than I freed");
        return;
    }

    emscripten_fetch_attr_t attr;
    emscripten_fetch_attr_init(&attr);
    strcpy(attr.requestMethod, "POST");

    attr.attributes = EMSCRIPTEN_FETCH_LOAD_TO_MEMORY;
    attr.onsuccess = ll_request_success;
    attr.onerror = ll_request_failed;

    const char * headers[] = {"Content-Type", "application/json", 0};
    attr.requestHeaders = headers;

    const char* pre_key = "{\"game_key\": \"";
    // GAME KEY
    const char* post_key = "\", \"game_version\": \"0.10.0.0\", \"player_identifier\": \"";
    // USER ID
    const char* post_identifier = "\"}\0";

    const size_t pre_key_len = strlen(pre_key);
    const size_t game_key_len = strlen(game_key);
    const size_t post_key_len = strlen(post_key);
    const size_t player_id_len = strlen(player_id);
    const size_t post_identifier_len = strlen(post_identifier);

    ll_active_request_data = (char*)memory_allocate(pre_key_len + game_key_len + post_key_len + player_id_len + post_identifier_len + 1);

    if (ll_active_request_data == 0)
    {
        NL_LOG("Unable to allocate memory for the request data");
        return;
    }

    memcpy((void*)ll_active_request_data, 
            pre_key, 
            pre_key_len);

    memcpy((void*)ll_active_request_data + pre_key_len, 
            game_key, 
            game_key_len);

    memcpy((void*)ll_active_request_data + pre_key_len + game_key_len, 
            post_key, 
            post_key_len);
    
    memcpy((void*)ll_active_request_data + pre_key_len + game_key_len + post_key_len, 
            player_id, 
            player_id_len);

    memcpy((void*)ll_active_request_data + pre_key_len + game_key_len + post_key_len + player_id_len, 
            post_identifier, 
            post_identifier_len);
    
    attr.requestData = ll_active_request_data;
    attr.requestDataSize = strlen(attr.requestData);

    emscripten_fetch(&attr, "https://api.lootlocker.io/game/v2/session/guest");
}
