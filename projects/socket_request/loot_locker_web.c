#include "loot_locker.h"
#include "nl_lib.h"

#include <stdio.h>
#include <string.h>
#include <emscripten/fetch.h>

// Must not free the data while the request is in progress
global_variable char* active_request_data = 0;

internal_function void cleanup_request(emscripten_fetch_t *fetch)
{
    memory_free(active_request_data);
    active_request_data = 0;
    emscripten_fetch_close(fetch);
}

internal_function void request_success(emscripten_fetch_t *fetch) 
{
    NL_LOG("Finished downloading %llu bytes from URL %s.\n", fetch->numBytes, fetch->url);
    NL_LOG("Result Data: %s", fetch->data);
    cleanup_request(fetch);
}

internal_function void request_failed(emscripten_fetch_t *fetch) 
{
    NL_LOG("Downloading %s failed, HTTP failure status code: %d.\n", fetch->url, fetch->status);
    NL_LOG("Result Data: %s", fetch->data);
    cleanup_request(fetch);
}

void ll_guest_login(const char* const game_key)
{
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

