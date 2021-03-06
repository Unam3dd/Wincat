#include "wincat.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{

    if (argc < 2) {
        fprintf(stderr,"usage : %s -h/--help\n", argv[0]);
        return (1);
    }

    WSADATA wsa = {0};
    SetConsoleCP(CP_UTF8); // set UTF-8 in Console
    SetConsoleOutputCP(CP_UTF8); // set UTF-8 in Console output

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN); // Set console color

    // Initialize Winsock 2.2
    if (WSAStartup(MAKEWORD(2,2), &wsa)) {
        fprintf(stderr,"[-] Error in WSAStartup()");
        return (1);
    }

    if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)
        show_help();

    if (strcmp(argv[1], "-l") == 0) {

        if (create_server(argv[2], to_int(argv[3]))) {
            fprintf(stderr, "[-] Error create server !");
            return (1);
        }

    }

    if (strcmp(argv[1], "-c") == 0) {

        if (client_connect(argv[2], to_int(argv[3]))) {
            fprintf(stderr, "[-] Error connect to the remote host !");
            return (1);
        }

    }

    if (strcmp(argv[1], "-cp") == 0) {

        if (client_connect_execute_process(argv[2], to_int(argv[3]), argv[4])) {
            fprintf(stderr, "[-] Error connect to the remote host !");
            return (1);
        }

    }

    if (strcmp(argv[1], "-sp") == 0) {

        if (create_server_execute_process(argv[2], to_int(argv[3]), argv[4])) {
            fprintf(stderr, "[-] Error create server !\n");
            return (1);
        }

    }

    if (strcmp(argv[1], "-a") == 0)
        printf("[+] Address : %s | Network byte order : %#x\n", argv[2], inet_addr(argv[2]));
    
    if (strcmp(argv[1], "-p") == 0)
        printf("[+] Port : %s | Network byte order : %#x\n", argv[2], htons(to_int(argv[2])));

    WSACleanup();

    return (0);
}