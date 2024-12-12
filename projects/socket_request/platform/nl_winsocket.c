
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>

int initialize_winsocket_client()
{
    WSADATA wsa_data = {0};

    int i_result = ;

    // Initialize Winsock
    i_result = WSAStartup(MAKEWORD(2,2), &wsa_data);
    if (i_result != 0) 
    {
        NL_LOG("WSAStartup failed: %d", i_result);
        return 0;
    }

    struct addrinfo *result = 0, *ptr = 0, hints;

    ZeroMemory( &hints, sizeof(hints) );
    hints.ai_family   = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

}
