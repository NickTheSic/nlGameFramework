#include "loot_locker.h"
#include "nl_lib.h"
#include "nl_request_web_common.h"

void ll_guest_login(const char* const game_key)
{
    if (active_request_data != 0)
    {
        NL_LOG("active_request_data is not null with the value %s", active_request_data);
        NL_LOG("Not completing request at this time to not allocate more memory than I freed");
        return;
    }

    emscripten_fetch_attr_t attr;
    emscripten_fetch_attr_init(&attr);
    strcpy(attr.requestMethod, "POST");

    attr.attributes = EMSCRIPTEN_FETCH_LOAD_TO_MEMORY;
    attr.onsuccess = request_success;
    attr.onerror = request_failed;

    const char * headers[] = {"Content-Type", "application/json", 0};
    attr.requestHeaders = headers;

    const char* pre_key = "{\"game_key\": \"";
    const char* post_key = "\", \"game_version\": \"0.10.0.0\"}\0";
    const size_t pre_key_len = strlen(pre_key);
    const size_t post_key_len = strlen(post_key);
    const size_t game_key_len = strlen(game_key);

    active_request_data = (char*)memory_allocate( pre_key_len + post_key_len + game_key_len+1);

    memcpy((void*)active_request_data, pre_key, pre_key_len);
    memcpy((void*)active_request_data + pre_key_len, game_key, game_key_len);
    memcpy((void*)active_request_data + pre_key_len + game_key_len, post_key, post_key_len);
    
    attr.requestData = active_request_data;
    attr.requestDataSize = strlen(attr.requestData);

    emscripten_fetch(&attr, "https://api.lootlocker.io/game/v2/session/guest");
}

void ll_returning_user(const char* const game_key, const char* const player_id)
{
    if (active_request_data != 0)
    {
        NL_LOG("active_request_data is not null with the value %s", active_request_data);
        NL_LOG("Not completing request at this time to not allocate more memory than I freed");
        return;
    }

    emscripten_fetch_attr_t attr;
    emscripten_fetch_attr_init(&attr);
    strcpy(attr.requestMethod, "POST");

    attr.attributes = EMSCRIPTEN_FETCH_LOAD_TO_MEMORY;
    attr.onsuccess = request_success;
    attr.onerror = request_failed;

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

    active_request_data = (char*)memory_allocate(pre_key_len + game_key_len + post_key_len + player_id_len + post_identifier_len + 1);
    
    NL_LOG("Allocated Memory");

    if (active_request_data == 0)
    {
        NL_LOG("Unable to allocate memory for the request data");
        return;
    }

    memcpy((void*)active_request_data, 
            pre_key, 
            pre_key_len);

            NL_LOG("memcpy 1");

    memcpy((void*)active_request_data + pre_key_len, 
            game_key, 
            game_key_len);
            NL_LOG("memcpy2");

    memcpy((void*)active_request_data + pre_key_len + game_key_len, 
            post_key, 
            post_key_len);
            NL_LOG("memcpy3");
    
    memcpy((void*)active_request_data + pre_key_len + game_key_len + post_key_len, 
            player_id, 
            player_id_len);

    memcpy((void*)active_request_data + pre_key_len + game_key_len + post_key_len + player_id_len, 
            post_identifier, 
            post_identifier_len);
    
    attr.requestData = active_request_data;
    attr.requestDataSize = strlen(attr.requestData);

    emscripten_fetch(&attr, "https://api.lootlocker.io/game/v2/session/guest");
}
