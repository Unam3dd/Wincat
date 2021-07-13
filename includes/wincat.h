#pragma once
#include <stdint.h>
#include <winsock2.h>
#include <WS2tcpip.h>
#include <windows.h>
#pragma warning(disable : 4047)

typedef struct lookup_table_t lookup_table_t;

struct lookup_table_t
{
    char *message[2];
    uint8_t (*func)(unsigned char *, uint16_t port, void *process);
};

// Stream Socket struct
typedef struct stream
{
    int in;
    SOCKET out;
} stream_t;

// server.c
uint8_t create_server(unsigned char *address, uint16_t port, unsigned char *null_ptr);
uint8_t create_server_execute_process(unsigned char *address, uint16_t port, unsigned char *process);
void wait_client(SOCKET fd);
void wait_client_process(SOCKET fd, unsigned char *process);

// stream.c
void *ThreadStream(void *ptr);
uint8_t HandleConnection(SOCKET fd);

// utils.c
void show_help(void);

// client.c
uint8_t client_connect(unsigned char *address, uint16_t port, unsigned char *null_ptr);
uint8_t client_connect_execute_process(unsigned char *address, uint16_t port, unsigned char *process);

// help.c
extern const lookup_table_t table[6];