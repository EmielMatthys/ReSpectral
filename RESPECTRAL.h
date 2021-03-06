//
// Created by emiel on 6/03/21.
//

#ifndef RESPECTRAL_RESPECTRAL_H
#define RESPECTRAL_RESPECTRAL_H

#include <sys/socket.h>

typedef int (*connect_type)(int sockfd, const struct sockaddr *addrm, socklen_t addrlen);
static connect_type real_connect = nullptr;

static int count;


#endif //RESPECTRAL_RESPECTRAL_H
