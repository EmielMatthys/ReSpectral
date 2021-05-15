#include <dlfcn.h>
#include "Injector.h"
#include <iostream>
#include <sys/socket.h>

typedef int (*connect_type)(int sockfd, const struct sockaddr *addrm, socklen_t addrlen);
static connect_type real_connect = nullptr;

static int count;

__attribute__((constructor)) static void _init() { count = 0; }

// We override the behavior of connect from <sys/socket.h> by PRE_LOADing
int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen)
{
    // Only inject when far enough into the process
    if (count >= 0 && count <= 17) { printf("COUNT %d\n", count); count++;  }
    if (count >= 9) { Injector::inject(); count = -1;}

    real_connect = reinterpret_cast<connect_type>( dlsym(RTLD_NEXT, "connect") );
    return real_connect(sockfd, addr, addrlen);
}

__attribute__((destructor)) static void _exit() { printf("EXIT"); }


