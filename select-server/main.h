#ifndef _MAIN_H
#define _MAIN_H

#define TIMEOUT 2
#define UTIMEOUT 0

int service(int sock_fd, struct sockaddr_in *server_addr, fd_set read_set);

#endif
