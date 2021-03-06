#pragma once
#include <stdint.h>
#include <winsock2.h>
#include <WS2tcpip.h>
#include <windows.h>
#pragma warning(disable : 4047)

// Stream Socket struct
typedef struct stream
{
    int in;
    SOCKET out;
} stream_t;

// server.c
uint8_t create_server(unsigned char *address, uint64_t port);
uint8_t create_server_execute_process(unsigned char *address, uint64_t port, unsigned char *process);
void wait_client(SOCKET fd);
void wait_client_process(SOCKET fd, unsigned char *process);

// stream.c
void *ThreadStream(void *ptr);
uint8_t HandleConnection(SOCKET fd);

// utils.c
int to_int(char *str);
void show_help(void);

// client.c
uint8_t client_connect(unsigned char *address, uint64_t port);
uint8_t client_connect_execute_process(unsigned char *address, uint64_t port, unsigned char *process);