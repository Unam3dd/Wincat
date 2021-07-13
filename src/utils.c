#include "wincat.h"
#include <stdio.h>

void show_help(void)
{
    printf("usage :\n-h show this main page\n-l <ip> <port> listen on port\n-c <ip> <port> connect to the remote host\n-cp <ip> <port> <process> connect to the remote host and execute process\n-sp <ip> <port> <process> create simple server and execute process for each client\n-a <address> convert your ip to network byte order\n-p <port> convert your port in to network byte order\n");
}