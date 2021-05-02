#include <dlfcn.h>
#include "RESPECTRAL.h"
#include "Injector.h"
#include <iostream>

__attribute__((constructor)) static void _init() { count = 0; exit(1); }

// We override the behavior of connect from <sys/socket.h> by PRE_LOADing
int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen)
{
    // Only inject when far enough into the process
    if (count >= 0 && count <= 17) { printf("COUNT %d\n", count); count++;  }
    if (count > 17) { Injector::instance(); count = -1;}

    real_connect = reinterpret_cast<connect_type>( dlsym(RTLD_NEXT, "connect") );
    return real_connect(sockfd, addr, addrlen);
}


