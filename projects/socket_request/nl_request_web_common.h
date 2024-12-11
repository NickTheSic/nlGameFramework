#ifndef __NL_REQUEST_WEB_COMMON_H__
#define __NL_REQUEST_WEB_COMMON_H__

#include <stdio.h>
#include <string.h>
#include <emscripten/fetch.h>

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

#endif//__NL_REQUEST_WEB_COMMON_H__