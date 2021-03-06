#include <dlfcn.h>
#include "RESPECTRAL.h"
#include "Injector.h"

__attribute__((constructor)) static void _init() { count = 0; }

// We override the behavior of connect from <sys/socket.h> by PRE_LOADing
int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen)
{
    // Only inject when far enough into the process
    if (count >= 0 && count <= 17) count++;
    if (count > 17) Injector::Initialize();

    real_connect = reinterpret_cast<connect_type>( dlsym(RTLD_NEXT, "connect") );
    return real_connect(sockfd, addr, addrlen);    
}


